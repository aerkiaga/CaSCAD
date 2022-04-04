#include "backend.h"
#include "context.h"
#include <math.h>
#include <opencascade/Message_ProgressRange.hxx>
#include <opencascade/BRepAlgoAPI_Fuse.hxx>
#include <opencascade/BRepMesh_IncrementalMesh.hxx>
#include <opencascade/BRepPrimAPI_MakeCone.hxx>
#include <opencascade/BRepPrimAPI_MakeCylinder.hxx>
#include <opencascade/Standard_Handle.hxx>
#include <opencascade/StlAPI.hxx>
#include <opencascade/TopAbs_ShapeEnum.hxx>
#include <opencascade/TopoDS_Shape.hxx>
#include <opencascade/gp_Ax2.hxx>
#include <opencascade/gp_Dir.hxx>
#include <opencascade/gp_Pnt.hxx>

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




