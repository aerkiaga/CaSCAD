#include <stdint.h>
#include <stdlib.h>

typedef struct pt_vector_t {
    size_t size;
    intptr_t* ptr;
} pt_vector_t;

inline pt_vector_t *pt_vector_new(pt_vector_t *vec) {
    pt_vector_t *r = (pt_vector_t *) malloc(sizeof(pt_vector_t));
    r->ptr = NULL;
    r->size = 0;
}

inline void pt_vector_clear(pt_vector_t *vec) {
    if(vec->ptr != NULL)
        free(vec->ptr);
    vec->ptr = NULL;
    vec->size = 0;
}

inline void pt_vector_append(pt_vector_t *vec, intptr_t val) {
    vec->size++;
    vec->ptr = (intptr_t *) realloc(vec->ptr, vec->size * sizeof(intptr_t));
    vec->ptr[vec->size - 1] = val;
}

inline pt_vector_t *pt_vector_delete(pt_vector_t *vec) {
    pt_vector_clear(vec);
    free(vec);
}
