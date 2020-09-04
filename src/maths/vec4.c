#include <maths/vec4.h>

vec4 vec4_zeros(){ return (vec4){ 0.0, 0.0, 0.0, 0.0 }; }
vec4 vec4_ones() { return (vec4){ 1.0, 1.0, 1.0, 1.0 }; }
vec4 vec4_scalar(double s) { return (vec4){ s, s, s, s }; }

void vec4_print(vec4* v) {
    printf("%p vec4(%f, %f, %f, %f)\n", v, v->x, v->y, v->z, v->w);
}

double vec4_sqr_length(vec4* v) {
    return vec4_dot(v, v);
}
double vec4_length(vec4* v) {
    return sqrt(vec4_sqr_length(v));
}
double vec4_dot(vec4* a, vec4* b) {
    return a->x * b->x + a->y * b->y + a->z * b->z + a->w * b->w;
}

vec4* vec4_neg(vec4* v, vec4* dest) {
    dest->x = -v->x;
    dest->y = -v->y;
    dest->z = -v->z;
    dest->w = -v->w;
    return dest;
}
vec4* vec4_add(vec4* a, vec4* b, vec4* dest) {
    dest->x = a->x + b->x;
    dest->y = a->y + b->y;
    dest->z = a->z + b->z;
    dest->w = a->w + b->w;
    return dest;
}
vec4* vec4_sub(vec4* a, vec4* b, vec4* dest) {
    dest->x = a->x - b->x;
    dest->y = a->y - b->y;
    dest->z = a->z - b->z;
    dest->w = a->w - b->w;
    return dest;
}
vec4* vec4_mul(vec4* a, vec4* b, vec4* dest) {
    dest->x = a->x * b->x;
    dest->y = a->y * b->y;
    dest->z = a->z * b->z;
    dest->w = a->w * b->w;
    return dest;
}
vec4* vec4_div(vec4* a, vec4* b, vec4* dest) {
    dest->x = a->x / b->x;
    dest->y = a->y / b->y;
    dest->z = a->z / b->z;
    dest->w = a->w / b->w;
    return dest;
}
vec4* vec4_cross(vec4* a, vec4* b, vec4* dest) {
    dest->x = a->y * b->z - a->z * b->y;
    dest->y = a->z * b->x - a->x * b->z;
    dest->z = a->x * b->y - a->y * b->x;
    dest->w = a->w * b->w - a->w * b->w;
    return dest;
}

vec4* vec4_add_scalar(vec4* v, double* s, vec4* dest) {
    vec4 vs = vec4_scalar(*s);
    return vec4_add(v, &vs, dest);
}
vec4* vec4_sub_scalar(vec4* v, double* s, vec4* dest) {
    vec4 vs = vec4_scalar(*s);
    return vec4_sub(v, &vs, dest);
}
vec4* vec4_mul_scalar(vec4* v, double* s, vec4* dest) {
    vec4 vs = vec4_scalar(*s);
    return vec4_mul(v, &vs, dest);
}
vec4* vec4_div_scalar(vec4* v, double* s, vec4* dest) {
    vec4 vs = vec4_scalar(*s);
    return vec4_div(v, &vs, dest);
}

vec4* vec4_normalize(vec4* v, vec4* dest) {
    double length = vec4_length(v);
    return vec4_div_scalar(v, &length, dest);
}