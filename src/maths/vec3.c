#include <maths/vec3.h>

vec3 vec3_zeros(){ return (vec3){ 0.0, 0.0, 0.0 }; }
vec3 vec3_ones() { return (vec3){ 1.0, 1.0, 1.0 }; }
vec3 vec3_scalar(double s) { return (vec3){ s, s, s }; }
vec3 vec3_random_uint_disk() {
    double theta = random_double() * M_2_PI;
    double u = random_double() + random_double();
    double r = (u > 1.0)? 2.0 - u: u;
    return (vec3){ r * cos(theta), r * sin(theta), 0 };
}

void vec3_print(vec3* v) {
    printf("%p vec3(%f, %f, %f)\n", v, v->x, v->y, v->z);
}

double vec3_sqr_length(vec3* v) {
    return vec3_dot(v, v);
}
double vec3_length(vec3* v) {
    return sqrt(vec3_sqr_length(v));
}
double vec3_dot(vec3* a, vec3* b) {
    return a->x * b->x + a->y * b->y + a->z * b->z;
}

vec3* vec3_neg(vec3* v, vec3* dest) {
    dest->x = -v->x;
    dest->y = -v->y;
    dest->z = -v->z;
    return dest;
}
vec3* vec3_add(vec3* a, vec3* b, vec3* dest) {
    dest->x = a->x + b->x;
    dest->y = a->y + b->y;
    dest->z = a->z + b->z;
    return dest;
}
vec3* vec3_sub(vec3* a, vec3* b, vec3* dest) {
    dest->x = a->x - b->x;
    dest->y = a->y - b->y;
    dest->z = a->z - b->z;
    return dest;
}
vec3* vec3_mul(vec3* a, vec3* b, vec3* dest) {
    dest->x = a->x * b->x;
    dest->y = a->y * b->y;
    dest->z = a->z * b->z;
    return dest;
}
vec3* vec3_div(vec3* a, vec3* b, vec3* dest) {
    dest->x = a->x / b->x;
    dest->y = a->y / b->y;
    dest->z = a->z / b->z;
    return dest;
}
vec3* vec3_cross(vec3* a, vec3* b, vec3* dest) {
    dest->x = a->y * b->z - a->z * b->y;
    dest->y = a->z * b->x - a->x * b->z;
    dest->z = a->x * b->y - a->y * b->x;
    return dest;
}

vec3* vec3_add_scalar(vec3* v, double* s, vec3* dest) {
    vec3 vs = vec3_scalar(*s);
    return vec3_add(v, &vs, dest);
}
vec3* vec3_sub_scalar(vec3* v, double* s, vec3* dest) {
    vec3 vs = vec3_scalar(*s);
    return vec3_sub(v, &vs, dest);
}
vec3* vec3_mul_scalar(vec3* v, double* s, vec3* dest) {
    vec3 vs = vec3_scalar(*s);
    return vec3_mul(v, &vs, dest);
}
vec3* vec3_div_scalar(vec3* v, double* s, vec3* dest) {
    vec3 vs = vec3_scalar(*s);
    return vec3_div(v, &vs, dest);
}

vec3* vec3_normalize(vec3* v, vec3* dest) {
    double length = vec3_length(v);
    return vec3_div_scalar(v, &length, dest);
}