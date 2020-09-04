#include <maths/vec2.h>

vec2 vec2_zeros(){ return (vec2){ 0.0, 0.0 }; }
vec2 vec2_ones() { return (vec2){ 1.0, 1.0 }; }
vec2 vec2_scalar(double s) { return (vec2){ s, s }; }

void vec2_print(vec2* v) {
    printf("%p vec2(%f, %f)\n", v, v->x, v->y);
}

double vec2_sqr_length(vec2* v) {
    return vec2_dot(v, v);
}
double vec2_length(vec2* v) {
    return sqrt(vec2_sqr_length(v));
}
double vec2_dot(vec2* a, vec2* b) {
    return a->x * b->x + a->y * b->y;
}

vec2* vec2_neg(vec2* v, vec2* dest) {
    dest->x = -v->x;
    dest->y = -v->y;
    return dest;
}
vec2* vec2_add(vec2* a, vec2* b, vec2* dest) {
    dest->x = a->x + b->x;
    dest->y = a->y + b->y;
    return dest;
}
vec2* vec2_sub(vec2* a, vec2* b, vec2* dest) {
    dest->x = a->x - b->x;
    dest->y = a->y - b->y;
    return dest;
}
vec2* vec2_mul(vec2* a, vec2* b, vec2* dest) {
    dest->x = a->x * b->x;
    dest->y = a->y * b->y;
    return dest;
}
vec2* vec2_div(vec2* a, vec2* b, vec2* dest) {
    dest->x = a->x / b->x;
    dest->y = a->y / b->y;
    return dest;
}

vec2* vec2_add_scalar(vec2* v, double* s, vec2* dest) {
    vec2 vs = vec2_scalar(*s);
    return vec2_add(v, &vs, dest);
}
vec2* vec2_sub_scalar(vec2* v, double* s, vec2* dest) {
    vec2 vs = vec2_scalar(*s);
    return vec2_sub(v, &vs, dest);
}
vec2* vec2_mul_scalar(vec2* v, double* s, vec2* dest) {
    vec2 vs = vec2_scalar(*s);
    return vec2_mul(v, &vs, dest);
}
vec2* vec2_div_scalar(vec2* v, double* s, vec2* dest) {
    vec2 vs = vec2_scalar(*s);
    return vec2_div(v, &vs, dest);
}

vec2* vec2_normalize(vec2* v, vec2* dest) {
    double length = vec2_length(v);
    return vec2_div_scalar(v, &length, dest);
}