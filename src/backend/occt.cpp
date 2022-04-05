#include "backend.h"
#include "context.h"
#include <math.h>
#include <opencascade/AIS_InteractiveContext.hxx>
#include <opencascade/AIS_Shape.hxx>
#include <opencascade/AIS_ViewController.hxx>
#include <opencascade/Aspect_DisplayConnection.hxx>
#include <opencascade/Aspect_NeutralWindow.hxx>
#include <opencascade/Graphic3d_Vec2.hxx>
#include <opencascade/Message_ProgressRange.hxx>
#include <opencascade/BRepAlgoAPI_Fuse.hxx>
#include <opencascade/BRepMesh_IncrementalMesh.hxx>
#include <opencascade/BRepPrimAPI_MakeCone.hxx>
#include <opencascade/BRepPrimAPI_MakeCylinder.hxx>
#include <opencascade/OpenGl_FrameBuffer.hxx>
#include <opencascade/OpenGl_GraphicDriver.hxx>
#include <opencascade/Standard_Handle.hxx>
#include <opencascade/StlAPI.hxx>
#include <opencascade/TopAbs_ShapeEnum.hxx>
#include <opencascade/TopoDS_Shape.hxx>
#include <opencascade/V3d_View.hxx>
#include <opencascade/V3d_Viewer.hxx>
#include <opencascade/Xw_Window.hxx>
#include <opencascade/gp_Ax2.hxx>
#include <opencascade/gp_Dir.hxx>
#include <opencascade/gp_Pnt.hxx>

#include <opencascade/TCollection_AsciiString.hxx>
#include <opencascade/TColStd_IndexedDataMapOfStringString.hxx>

void backend_cylinder(value_t out_value, value_t parameters) {
    /* Ignore first argument. */
    EXPECT_ARG_TYPE(2, VALUE_TYPE_NUMBER);
    double h = parameters[3].d;
    EXPECT_ARG_TYPE(4, VALUE_TYPE_NUMBER);
    double r1 = parameters[5].d;
    EXPECT_ARG_TYPE(6, VALUE_TYPE_NUMBER);
    double r2 = parameters[7].d;
    
    gp_Pnt *origin = new gp_Pnt(
        0.0, 0.0, TEST_VALUE(parameters + 8) ? -h/2 : 0.0
    );
    gp_Dir *z_direction = new gp_Dir(0.0, 0.0, 1.0);
    gp_Ax2 *axes = new gp_Ax2(
        *origin, *z_direction
    );
    const TopoDS_Solid *output_shape;
    if(r1 == r2) {
        BRepPrimAPI_MakeCylinder *make_cylinder = new BRepPrimAPI_MakeCylinder(
            *axes, r1, h
        );
        output_shape = &make_cylinder->Solid();
    } else {
        BRepPrimAPI_MakeCone *make_cone = new BRepPrimAPI_MakeCone(
            *axes, r1, r2, h
        );
        output_shape = &make_cone->Solid();
    }
    
    out_value[0].u = VALUE_TYPE_SOLID;
    out_value[1].p = const_cast<void *>(static_cast<const void *>(output_shape));
}

void backend_union(value_t out_value, value_t parameters) {
    /* If we have a single child, return it. */
    if(parameters[0].u != VALUE_TYPE_CHILDREN) {
        out_value[0].u = parameters[0].u;
        out_value[1].p = parameters[1].p;
        return;
    }
    tree_t children = parameters[1].a;
    out_value[0].u = VALUE_TYPE_EMPTY;
    out_value[1].u = 0;
    size_t i;
    for(i = 1; i <= children[0].u; i += 2) {
        if(children[i].u == VALUE_TYPE_EMPTY) continue;
        if(children[i].u != VALUE_TYPE_SOLID) {
            error("runtime error: non-shape value passed to union operation.\n");
        } 
        if(out_value[0].u == VALUE_TYPE_EMPTY) {
            out_value[0].u = children[i].u;
            out_value[1].p = children[i + 1].p;
        } else if(out_value[0].u != VALUE_TYPE_SOLID) {
            error("runtime error: union operation obtained a non-shape value.\n");
        } else {
            if(out_value[0].u != children[i].u) {
                error("runtime error: attempted union (explicit or implicit) of shapes of different type.");
            }
            Message_ProgressRange *progress_range =
                new Message_ProgressRange()
            ;
            BRepAlgoAPI_Fuse *fuse = new BRepAlgoAPI_Fuse(
                *static_cast<TopoDS_Shape *>(out_value[1].p),
                *static_cast<TopoDS_Shape *>(children[i + 1].p),
                *progress_range
            );
            const TopoDS_Shape *output_shape = &fuse->Shape();
            TopAbs_ShapeEnum shape_type = output_shape->ShapeType();
            out_value[0].u = CONVERT_SHAPE_TYPE(shape_type);
            if(out_value[0].u == VALUE_TYPE_EMPTY) {
                /* A union of nonempty geometry cannot be empty. */
                error("runtime error: union operation (explicit or implicit) failed.\n");
            }
            if(out_value[0].u == VALUE_TYPE_COMPOUND) {
                out_value[0].u = children[i].u;
            }
            out_value[1].p = const_cast<void *>(static_cast<const void *>(output_shape));
        }
    }
}

int backend_export_stl(value_t in_value, const char *path, int ascii) {
    TopoDS_Shape *shape = static_cast<TopoDS_Shape *>(in_value[1].p);
    
    Message_ProgressRange *progress_range = new Message_ProgressRange();
    BRepMesh_IncrementalMesh incremental_mesh = BRepMesh_IncrementalMesh(
        *shape, 0.1
    );
    incremental_mesh.Perform(*progress_range);
    
    return StlAPI::Write(*shape, path, ascii);
}

class OcctGtkWindow : public Aspect_NeutralWindow {
public:
    //! Constructor.
    OcctGtkWindow() {}

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

void dumpGlInfo(bool theIsBasic) {
  TColStd_IndexedDataMapOfStringString aGlCapsDict;
  view->DiagnosticInformation(
    aGlCapsDict, theIsBasic ? Graphic3d_DiagnosticInfo_Basic : Graphic3d_DiagnosticInfo_Complete
  );
  if (theIsBasic)
  {
    TCollection_AsciiString aViewport;
    aGlCapsDict.FindFromKey ("Viewport", aViewport);
    aGlCapsDict.Clear();
    aGlCapsDict.Add ("Viewport", aViewport);
  }

  // beautify output
  {
    TCollection_AsciiString* aGlVer   = aGlCapsDict.ChangeSeek ("GLversion");
    TCollection_AsciiString* aGlslVer = aGlCapsDict.ChangeSeek ("GLSLversion");
    if (aGlVer   != NULL
     && aGlslVer != NULL)
    {
      *aGlVer = *aGlVer + " [GLSL: " + *aGlslVer + "]";
      aGlslVer->Clear();
    }
  }

  TCollection_AsciiString anInfo;
  for (TColStd_IndexedDataMapOfStringString::Iterator aValueIter (aGlCapsDict); aValueIter.More(); aValueIter.Next())
  {
    if (!aValueIter.Value().IsEmpty())
    {
      if (!anInfo.IsEmpty())
      {
        anInfo += "\n";
      }
      anInfo += aValueIter.Key() + ": " + aValueIter.Value();
    }
  }
  puts(anInfo.ToCString());
}

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
    ais_controller = new AIS_ViewController();
    
    view = viewer->CreateView();
    view->SetImmediateUpdate(false);
}

void backend_realize_graphics(
    int width, int height, int scale_factor,
    void *context, void *display, void *config
) {
    Graphic3d_Vec2i logical_size(width, height);
    Graphic3d_Vec2i view_size = logical_size * scale_factor;
    opencascade::handle<OpenGl_Context> gl_context = new OpenGl_Context();
    opencascade::handle<OcctGtkWindow> custom_window = dynamic_cast<OcctGtkWindow *>(view.get());
    
    /*if(!display_connection.get()) {
        backend_init_graphics(display);
    }*/
    
    if(context != nullptr) {
        if(custom_window.get() == nullptr) {
            custom_window = new OcctGtkWindow();
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

class OcctGtkFrameBuffer : public OpenGl_FrameBuffer {
  DEFINE_STANDARD_RTTI_INLINE(OcctGtkFrameBuffer, OpenGl_FrameBuffer)
public:
  OcctGtkFrameBuffer() {}

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
    OpenGl_Context *gl_context = gl_driver->GetSharedContext().get();
    OpenGl_FrameBuffer *framebuffer = gl_context->DefaultFrameBuffer().get();
    if(!framebuffer) {
        framebuffer = new OcctGtkFrameBuffer();
        gl_context->SetDefaultFrameBuffer(framebuffer);
    }
    framebuffer->InitWrapper(gl_context);
    
    // more pixel ratio work...
    
    view->InvalidateImmediate();
    ais_controller->FlushViewEvents(ais_context, view);
    view->Redraw();
}

void backend_render_shape(void *shape) {
    TopoDS_Shape *actual_shape = (TopoDS_Shape *) ((tree_t) shape)[2].p;
    opencascade::handle<AIS_Shape> interactive_shape =
        opencascade::handle<AIS_Shape>(new AIS_Shape(*actual_shape));
    ais_context->Display(interactive_shape, 0);
}





