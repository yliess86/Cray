#include <maths.h>

// ============ [START] RANDOM METHODS ============
void random_init() {
    srand((int) time(NULL));
}

double random_double() {
    return (double)rand() / ((double)RAND_MAX + 1);
}

double random_double_a_b(double a, double b) {
    return a + random() * (b - a);
}
// ============ [END] RANDOM METHODS ============

// ============ [START] ANGLES METHODS ============
double degree_to_radian(const double degree) {
    return degree * DEG2RAD;
}
// ============ [END] ANGLES METHODS ============

// ============ [START] VEC2 METHODS ============
vec2 vec2_zeros() {
    return (vec2){ 0.0, 0.0 };
}
vec2 vec2_ones() {
    return (vec2){ 1.0, 1.0 };
}
vec2 vec2_scalar(double s) {
    return (vec2){ s, s };
}

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
// ============ [END] VEC2 METHODS ============

// ============ [START] VEC3 METHODS ============
vec3 vec3_zeros() {
    return (vec3){ 0.0, 0.0, 0.0 };
}

vec3 vec3_ones() {
    return (vec3){ 1.0, 1.0, 1.0 };
}

vec3 vec3_scalar(double s) {
    return (vec3){ s, s, s };
}

vec3 vec3_random_uint_disk() {
    double theta = random_double() * M2PI;
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
// ============ [END] VEC3 METHODS ============

// ============ [START] VEC4 METHODS ============
vec4 vec4_zeros() {
    return (vec4){ 0.0, 0.0, 0.0, 0.0 };
}

vec4 vec4_ones() {
    return (vec4){ 1.0, 1.0, 1.0, 1.0 };
}

vec4 vec4_scalar(double s) {
    return (vec4){ s, s, s, s };
}

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
// ============ [END] VEC4 METHODS ============