#include "context.h"
#include "tree.h"
#include <opencascade/TopAbs_ShapeEnum.hxx>

#ifdef __cplusplus
extern "C" {
#endif

void error(const char *fmt, ...);

extern void backend_sphere(value_t out_value, value_t parameters);
extern void backend_cube(value_t out_value, value_t parameters);
extern void backend_cylinder(value_t out_value, value_t parameters);
extern void backend_translate(value_t out_value, value_t parameters);
extern void backend_union(value_t out_value, value_t parameters);

extern void backend_export_triangles(
    value_t in_value,
    float **out_coords, unsigned int *out_ncoords,
    unsigned int **out_indices, unsigned int *out_nindices
);
extern int backend_export_stl(value_t in_value, const char *path, int ascii);

#ifdef __cplusplus
} // extern "C"
#endif

#define EXPECT_ARG_TYPE(n, t) do { \
    if(parameters[(n)].u != (t)) \
        error("runtime error: argument type is incorrect.\n"); \
} while(0);

// TODO: vectors
#define TEST_VALUE(v) (!( \
    (((v)[0].u == VALUE_TYPE_BOOLEAN) && !(v)[1].u) || \
    (((v)[0].u == VALUE_TYPE_NUMBER) && ((v)[1].d == 0.0)) || \
    (((v)[0].u == VALUE_TYPE_STRING) && ((v)[1].s[0] == '\0')) || \
    ((v)[0].u == VALUE_TYPE_UNDEF) \
))

#define CONVERT_SHAPE_TYPE(t) ( \
    ((t) == TopAbs_SOLID) ? VALUE_TYPE_SOLID : \
    ((t) == TopAbs_COMPOUND) ? VALUE_TYPE_COMPOUND : \
    VALUE_TYPE_EMPTY \
)
    
