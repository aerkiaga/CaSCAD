#include "backend.h"
#include "gui.h"
#include <opencascade/AIS_InteractiveContext.hxx>
#include <opencascade/AIS_Shape.hxx>
#include <opencascade/AIS_ViewController.hxx>
#include <opencascade/Aspect_DisplayConnection.hxx>
#include <opencascade/Aspect_NeutralWindow.hxx>
#include <opencascade/OpenGl_Context.hxx>
#include <opencascade/OpenGl_FrameBuffer.hxx>
#include <opencascade/OpenGl_GraphicDriver.hxx>
#include <opencascade/V3d_View.hxx>
#include <opencascade/V3d_Viewer.hxx>
#include <opencascade/Xw_Window.hxx>

class OcctCaWindow : public Aspect_NeutralWindow {
public:
    //! Constructor.
    OcctCaWindow() {}

    //! Return device pixel ratio (logical to backing store scale factor).
    virtual Standard_Real DevicePixelRatio() const override {
        return m_pixel_ratio;
    }

    //! Set pixel ratio.
    void SetDevicePixelRatio(Standard_Real pixel_ratio) {
        m_pixel_ratio = pixel_ratio;
    }

private:
    double m_pixel_ratio = 1.0;
};

opencascade::handle<Aspect_DisplayConnection> display_connection;
opencascade::handle<OpenGl_GraphicDriver> viewer_driver;
opencascade::handle<V3d_Viewer> viewer;
opencascade::handle<V3d_View> view;
opencascade::handle<AIS_InteractiveContext> ais_context;
AIS_ViewController *ais_controller;

Graphic3d_Vec2i view_size;

class CustomAISController : public AIS_ViewController {
protected:
    //! Handle view redraw.
    virtual void handleViewRedraw(
        const Handle(AIS_InteractiveContext)& ais_context,
        const Handle(V3d_View)& view
    ) override {
        AIS_ViewController::handleViewRedraw(ais_context, view);
        gui_redraw_viewer();
    }
};

void backend_init_graphics(void *display) {
    if(display)
        display_connection = new Aspect_DisplayConnection((Aspect_XDisplay *) display);
    else
        display_connection = new Aspect_DisplayConnection();
    viewer_driver = new OpenGl_GraphicDriver(display_connection, false);
    viewer_driver->ChangeOptions().buffersNoSwap = true;
    viewer_driver->ChangeOptions().buffersOpaqueAlpha = true;
    viewer_driver->ChangeOptions().useSystemBuffer = false;
    
    viewer = new V3d_Viewer(viewer_driver);
    viewer->SetDefaultBackgroundColor(Quantity_Color(Quantity_NOC_WHEAT));
    viewer->SetDefaultLights();
    viewer->SetLightOn();
    viewer->ActivateGrid(Aspect_GT_Rectangular, Aspect_GDM_Lines);
    
    ais_context = new AIS_InteractiveContext(viewer);
    ais_controller = new CustomAISController();
    
    view = viewer->CreateView();
    view->SetImmediateUpdate(false);
}

void backend_realize_graphics(
    int width, int height, int scale_factor,
    void *context, void *display, void *config
) {
    Graphic3d_Vec2i logical_size(width, height);
    view_size = logical_size * scale_factor;
    opencascade::handle<OpenGl_Context> gl_context = new OpenGl_Context();
    opencascade::handle<OcctCaWindow> custom_window = dynamic_cast<OcctCaWindow *>(view.get());
    
    /*if(!display_connection.get()) {
        backend_init_graphics(display);
    }*/
    
    if(context != nullptr) {
        if(custom_window.get() == nullptr) {
            custom_window = new OcctCaWindow();
        }
        opencascade::handle<OpenGl_GraphicDriver> gl_driver =
            dynamic_cast<OpenGl_GraphicDriver *>(
                ais_context->CurrentViewer()->Driver().get()
            )
        ;
        gl_driver->InitEglContext(display, context, config);
        custom_window->SetSize(view_size.x(), view_size.y());
        custom_window->SetDevicePixelRatio(scale_factor);
        view->SetWindow(custom_window, gl_context->RenderingContext());
    } else {
        opencascade::handle<OpenGl_GraphicDriver> gl_driver =
            dynamic_cast<OpenGl_GraphicDriver *>(
                ais_context->CurrentViewer()->Driver().get()
            )
        ;
        //gl_driver.get()->GetDisplayConnection().get()->Init((Aspect_XDisplay *) display);
        //custom_window->SetNativeHandle((Aspect_Drawable) config);
        opencascade::handle<Xw_Window> xw_window =
            new Xw_Window(display_connection, (Aspect_Drawable) config);
        view->SetWindow(xw_window, gl_context->RenderingContext());
    }
    
    // initPixelScaleRatio();
    view->ChangeRenderingParams().Resolution = (unsigned int )(96.0 * scale_factor + 0.5);
    ais_context->SetPixelTolerance(int(scale_factor * 6.0));
    
    /*TopoDS_Solid *undef_solid = new TopoDS_Solid();
    opencascade::handle<AIS_Shape> interactive_shape =
        opencascade::handle<AIS_Shape>(new AIS_Shape(*undef_solid));
    ais_context->Display(interactive_shape, 0);*/
}

void backend_unrealize_graphics(void) {
    opencascade::handle<Aspect_DisplayConnection> display_connection;
    if(ais_context.get()) {
        display_connection = viewer->Driver()->GetDisplayConnection();
        ais_context->RemoveAll(false);
        ais_context.Nullify();
        view->Remove();
        view.Nullify();
        viewer.Nullify();
    }
    display_connection.Nullify();
}

class OcctCaFrameBuffer : public OpenGl_FrameBuffer {
  DEFINE_STANDARD_RTTI_INLINE(OcctCaFrameBuffer, OpenGl_FrameBuffer)
public:
  OcctCaFrameBuffer() {}

  //! Make this FBO active in context.
  virtual void BindBuffer(const opencascade::handle<OpenGl_Context> &gl_context) override {
    OpenGl_FrameBuffer::BindBuffer(gl_context);
    gl_context->SetFrameBufferSRGB(true, false);
  }

  //! Make this FBO as drawing target in context.
  virtual void BindDrawBuffer(const opencascade::handle<OpenGl_Context> &gl_context) override {
    OpenGl_FrameBuffer::BindDrawBuffer(gl_context);
    gl_context->SetFrameBufferSRGB(true, false);
  }

  //! Make this FBO as reading source in context.
  virtual void BindReadBuffer(const opencascade::handle<OpenGl_Context> &gl_context) override {
    OpenGl_FrameBuffer::BindReadBuffer(gl_context);
  }
};

void backend_render_graphics(void) {
    if(!view->Window()) return;
    
    opencascade::handle<OpenGl_GraphicDriver> gl_driver =
        dynamic_cast<OpenGl_GraphicDriver *>(
            ais_context->CurrentViewer()->Driver().get()
        )
    ;
    const Handle(OpenGl_Context) gl_context = gl_driver->GetSharedContext().get();
    Handle(OpenGl_FrameBuffer) framebuffer = gl_context->DefaultFrameBuffer().get();
    if(!framebuffer) {
        framebuffer = new OcctCaFrameBuffer();
        gl_context->SetDefaultFrameBuffer(framebuffer);
    }
    static bool already_init = false;
    if(!already_init) {
        #define GL_RGBA8 0x8058
        #define GL_DEPTH24_STENCIL8 0x88F0
        framebuffer->Init(
            gl_context,
            view_size,
            0x805B,
            0,//GL_DEPTH24_STENCIL8,
            0
        );
        already_init = true;
    } else {
        framebuffer->InitWrapper(gl_context);
    }
    
    // more pixel ratio work...
    
    view->InvalidateImmediate();
    ais_controller->FlushViewEvents(ais_context, view);
    view->Redraw();
    framebuffer->UnbindBuffer(gl_context);
}

void backend_render_shape(void *shape) {
    TopoDS_Shape *actual_shape = (TopoDS_Shape *) ((tree_t) shape)[2].p;
    opencascade::handle<AIS_Shape> interactive_shape =
        opencascade::handle<AIS_Shape>(new AIS_Shape(*actual_shape));
    ais_context->Display(interactive_shape, 0);
}
