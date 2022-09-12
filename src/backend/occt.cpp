#include "backend.h"
#include "context.h"
#include <math.h>
#include <opencascade/Graphic3d_Vec2.hxx>
#include <opencascade/Message_ProgressRange.hxx>
#include <opencascade/BRepAlgoAPI_Fuse.hxx>
#include <opencascade/BRepBuilderAPI_Transform.hxx>
#include <opencascade/BRepMesh_IncrementalMesh.hxx>
#include <opencascade/BRepPrimAPI_MakeBox.hxx>
#include <opencascade/BRepPrimAPI_MakeCone.hxx>
#include <opencascade/BRepPrimAPI_MakeCylinder.hxx>
#include <opencascade/BRepPrimAPI_MakeSphere.hxx>
#include <opencascade/BRep_Tool.hxx>
#include <opencascade/Standard_Handle.hxx>
#include <opencascade/StlAPI.hxx>
#include <opencascade/TopAbs_Orientation.hxx>
#include <opencascade/TopAbs_ShapeEnum.hxx>
#include <opencascade/TopExp_Explorer.hxx>
#include <opencascade/TopLoc_Location.hxx>
#include <opencascade/TopoDS.hxx>
#include <opencascade/TopoDS_Shape.hxx>
#include <opencascade/gp_Ax2.hxx>
#include <opencascade/gp_Dir.hxx>
#include <opencascade/gp_Pnt.hxx>
#include <opencascade/NCollection_Array1.hxx>
#include <opencascade/TCollection_AsciiString.hxx>
#include <opencascade/TColStd_IndexedDataMapOfStringString.hxx>

void backend_sphere(value_t out_value, value_t parameters) {
    /* Ignore first argument. */
    EXPECT_ARG_TYPE(2, VALUE_TYPE_NUMBER);
    double r = parameters[3].d;

    gp_Pnt *origin = new gp_Pnt(
        0.0, 0.0, 0.0
    );
    BRepPrimAPI_MakeSphere *make_sphere = new BRepPrimAPI_MakeSphere(
        *origin, r
    );
    const TopoDS_Solid *output_shape = &make_sphere->Solid();

    out_value[0].u = VALUE_TYPE_SOLID;
    out_value[1].p = const_cast<void *>(static_cast<const void *>(output_shape));
}

void backend_cube(value_t out_value, value_t parameters) {
    /* Ignore first argument. */
    if(parameters[2].u != VALUE_TYPE_NUMBER && parameters[2].u != VALUE_TYPE_VECTOR)
        error("runtime error: argument type not among valid types.\n");
    tree_child_t dimensions = parameters[3];

    double dx, dy, dz;
    if(parameters[2].u == VALUE_TYPE_VECTOR) {
        if(dimensions.a[0].u != 6)
            error("runtime error: provided vector is not 3-dimensional.\n");
        if(dimensions.a[1].u != VALUE_TYPE_NUMBER ||
           dimensions.a[3].u != VALUE_TYPE_NUMBER ||
           dimensions.a[5].u != VALUE_TYPE_NUMBER)
            error("runtime error: provided vector contains non-numerical values.\n");
        dx = dimensions.a[2].d;
        dy = dimensions.a[4].d;
        dz = dimensions.a[6].d;
    } else {
        dx = dy = dz = dimensions.d;
    }
    
    gp_Pnt *origin = TEST_VALUE(parameters + 4) ?
        new gp_Pnt(-dx/2.0, -dy/2.0, -dz/2.0) :
        new gp_Pnt(0.0, 0.0, 0.0)
    ;
    BRepPrimAPI_MakeBox *make_box = new BRepPrimAPI_MakeBox(
        *origin, dx, dy, dz
    );
    const TopoDS_Solid *output_shape = &make_box->Solid();
    
    out_value[0].u = VALUE_TYPE_SOLID;
    out_value[1].p = const_cast<void *>(static_cast<const void *>(output_shape));
}

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

void backend_translate(value_t out_value, value_t parameters) {
    if(parameters[0].u != VALUE_TYPE_SOLID)
        error("runtime error: non-shape value passed to translate operation.\n");
    EXPECT_ARG_TYPE(2, VALUE_TYPE_VECTOR);
    tree_t displacement = parameters[3].a;

    if(displacement[0].u != 6)
        error("runtime error: provided vector is not 3-dimensional.\n");
    if(displacement[1].u != VALUE_TYPE_NUMBER ||
       displacement[3].u != VALUE_TYPE_NUMBER ||
       displacement[5].u != VALUE_TYPE_NUMBER)
        error("runtime error: provided vector contains non-numerical values.\n");
    double dx, dy, dz;
    dx = displacement[2].d;
    dy = displacement[4].d;
    dz = displacement[6].d;

    gp_Trsf transform = gp_Trsf();
    transform.SetTranslation(gp_Vec(gp_XYZ(dx, dy, dz)));
    static_cast<TopoDS_Shape *>(parameters[1].p)->Move(TopLoc_Location(transform));

    out_value[0].u = VALUE_TYPE_SOLID;
    out_value[1] = parameters[1];
}

void backend_rotate(value_t out_value, value_t parameters) {
    if(parameters[0].u != VALUE_TYPE_SOLID)
        error("runtime error: non-shape value passed to rotate operation.\n");
    if(parameters[2].u != VALUE_TYPE_NUMBER && parameters[2].u != VALUE_TYPE_VECTOR)
        error("runtime error: argument type not among valid types.\n");
    tree_child_t angles = parameters[3];

    gp_Trsf transformation = gp_Trsf();
    if(parameters[2].u == VALUE_TYPE_NUMBER) {
        EXPECT_ARG_TYPE(4, VALUE_TYPE_VECTOR);
        tree_t axis = parameters[5].a;
        if(axis[0].u != 6)
            error("runtime error: provided vector is not 3-dimensional.\n");
        gp_Ax1 ax = gp_Ax1(gp_Pnt(), gp_Dir(gp_XYZ(axis[2].d, axis[4].d, axis[6].d)));
        double angle = angles.d * M_PI / 180.0;
        transformation.SetRotation(ax, angle);
    } else {
        if(angles.a[0].u != 6)
            error("runtime error: provided vector is not 3-dimensional.\n");
        double angle_x, angle_y, angle_z;
        angle_x = angles.a[2].d * M_PI / 180.0;
        angle_y = angles.a[4].d * M_PI / 180.0;
        angle_z = angles.a[6].d * M_PI / 180.0;
        transformation.SetRotation(gp_Ax1(gp_Pnt(), gp_Dir(gp_XYZ(0.0, 0.0, 1.0))), angle_z);
        gp_Trsf transformation2;
        transformation2.SetRotation(gp_Ax1(gp_Pnt(), gp_Dir(gp_XYZ(0.0, 1.0, 0.0))), angle_y);
        transformation *= transformation2;
        transformation2.SetRotation(gp_Ax1(gp_Pnt(), gp_Dir(gp_XYZ(1.0, 0.0, 0.0))), angle_x);
        transformation *= transformation2;
    }

    BRepBuilderAPI_Transform *api_transform = new BRepBuilderAPI_Transform(
        *static_cast<const TopoDS_Shape *>(parameters[1].p), transformation
    );
    const TopoDS_Shape *output_shape = &api_transform->Shape();

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

void backend_export_triangles(
    value_t in_value,
    float **out_coords, unsigned int *out_ncoords,
    unsigned int **out_indices, unsigned int *out_nindices
) {
    const TopoDS_Shape shape = *static_cast<TopoDS_Shape *>(in_value[1].p);
    
    Message_ProgressRange *progress_range = new Message_ProgressRange();
    BRepMesh_IncrementalMesh incremental_mesh = BRepMesh_IncrementalMesh(
        shape, 0.1
    );
    incremental_mesh.Perform(*progress_range);
    
    float *coordinates = NULL;
    unsigned int *indices = NULL;
    unsigned int point_count = 0;
    unsigned int triangle_index = 0;
    
    for(TopExp_Explorer explorer(shape, TopAbs_FACE); explorer.More(); explorer.Next()) {
        TopoDS_Face face = TopoDS::Face(explorer.Current());
        TopAbs_Orientation face_orientation = face.Orientation();
        TopLoc_Location location;
        opencascade::handle<Poly_Triangulation> triangulation =
            BRep_Tool::Triangulation(face, location);
        
        if(triangulation.IsNull())
            continue;
        
        TColgp_Array1OfPnt points(1, triangulation->NbNodes());
        coordinates = (float *) realloc(coordinates, 4*(point_count + triangulation->NbNodes())*sizeof(float));
        for(Standard_Integer i = 0; i < triangulation->NbNodes(); i++) {
            gp_Pnt point = triangulation->Node(i+1).Transformed(location);            
            coordinates[4*(point_count + i)] = point.X();
            coordinates[4*(point_count + i) + 1] = point.Y();
            coordinates[4*(point_count + i) + 2] = point.Z();
            coordinates[4*(point_count + i) + 3] = 1.0f;
        }
        
        for(Standard_Integer nt = 1; nt < triangulation->NbTriangles()+1; nt++) {
            
            Standard_Integer n1, n2, n3;
            triangulation->Triangle(nt).Get(n1, n2, n3);
            
            n1 += point_count;
            n2 += point_count;
            n3 += point_count;
            
            indices = (unsigned int *) realloc(indices, 3*(triangle_index + 1)*sizeof(unsigned int));
            if(face_orientation == TopAbs_Orientation::TopAbs_FORWARD) {
                indices[3*triangle_index] = n1 - 1;
                indices[3*triangle_index+1] = n2 - 1;
                indices[3*triangle_index+2] = n3 - 1;
            } else {
                indices[3*triangle_index] = n3 - 1;
                indices[3*triangle_index+1] = n2 - 1;
                indices[3*triangle_index+2] = n1 - 1;
            }
            triangle_index++;
        }
        
        point_count += triangulation->NbNodes();
    }
    
    *out_coords = coordinates;
    *out_ncoords = 4*point_count;
    *out_indices = indices;
    *out_nindices = 3*triangle_index;
}

int backend_export_stl(value_t in_value, const char *path, int ascii) {
    const TopoDS_Shape shape = *static_cast<TopoDS_Shape *>(in_value[1].p);
    
    Message_ProgressRange *progress_range = new Message_ProgressRange();
    BRepMesh_IncrementalMesh incremental_mesh = BRepMesh_IncrementalMesh(
        shape, 0.1
    );
    incremental_mesh.Perform(*progress_range);
    
    return StlAPI::Write(shape, path, ascii);
}







