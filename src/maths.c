#include <maths.h>

// ============ [START] RANDOM METHODS ============
void random_init() {
    srand((int) time(NULL));
}

double random_double() {
    return (double)rand() / ((double)RAND_MAX + 1);
}

double random_double_a_b(double a, double b) {
    return a + random_double() * (b - a);
}
// ============ [END] RANDOM METHODS ============

// ============ [START] UTILS METHODS ============
double degree_to_radian(const double degree) {
    return degree * DEG2RAD;
}

double clamp(const double s, const double a, const double b) {
    return (s < a)? a: (s > b)? b: s;
}
// ============ [END] UTILS METHODS ============

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

vec3 vec3_random_unit_disk() {
    double theta = random_double_a_b(0, M2PI);
    double u = random_double() + random_double();
    double r = (u > 1.0)? 2.0 - u: u;
    return (vec3){ r * cos(theta), r * sin(theta), 0 };
}

vec3 vec3_random_unit_sphere() {
    double theta = random_double_a_b(0, M2PI);
    double phi = acos((2 * random_double()) - 1);
    double r = pow(random_double(), 1 / 3);
    return (vec3){ r * sin(phi) * cos(theta), r * sin(phi) * sin(theta), r * cos(phi) };
}

vec3 vec3_random_unit_vector() {
    double a = random_double_a_b(0, M2PI);
    double z = random_double_a_b(-1, 1);
    double r = sqrt(1 - z * z);
    return (vec3){ r * cos(a), r * sin(a), z };
}

vec3 vec3_random_a_b(double a, double b) {
    return (vec3){ random_double_a_b(a, b), random_double_a_b(a, b), random_double_a_b(a, b) };
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

void vec3_reflect(vec3* v, vec3* n, vec3* dest) {
    vec3 dir;
    vec3_mul_scalar(n, 2 * vec3_dot(v, n), &dir);
    vec3_sub(v, &dir, dest);
}

void vec3_sqrt(vec3* v, vec3* dest) {
    dest->x = sqrt(v->x);
    dest->y = sqrt(v->y);
    dest->z = sqrt(v->z);
}

void vec3_neg(vec3* v, vec3* dest) {
    dest->x = -v->x;
    dest->y = -v->y;
    dest->z = -v->z;
}

void vec3_add(vec3* a, vec3* b, vec3* dest) {
    dest->x = a->x + b->x;
    dest->y = a->y + b->y;
    dest->z = a->z + b->z;
}

void vec3_sub(vec3* a, vec3* b, vec3* dest) {
    dest->x = a->x - b->x;
    dest->y = a->y - b->y;
    dest->z = a->z - b->z;
}

void vec3_mul(vec3* a, vec3* b, vec3* dest) {
    dest->x = a->x * b->x;
    dest->y = a->y * b->y;
    dest->z = a->z * b->z;
}

void vec3_div(vec3* a, vec3* b, vec3* dest) {
    dest->x = a->x / b->x;
    dest->y = a->y / b->y;
    dest->z = a->z / b->z;
}

void vec3_lerp(vec3* a, vec3* b, double t, vec3* dest) {
    dest->x = a->x * (1 - t) + b->x * t;
    dest->y = a->y * (1 - t) + b->y * t;
    dest->z = a->z * (1 - t) + b->z * t;
}

void vec3_clamp(vec3* v, double a, double b, vec3* dest) {
    dest->x = clamp(v->x, a, b);
    dest->y = clamp(v->y, a, b);
    dest->z = clamp(v->z, a, b);
}

void vec3_cross(vec3* a, vec3* b, vec3* dest) {
    dest->x = a->y * b->z - a->z * b->y;
    dest->y = a->z * b->x - a->x * b->z;
    dest->z = a->x * b->y - a->y * b->x;
}

void vec3_add_scalar(vec3* v, double s, vec3* dest) {
    vec3 vs = vec3_scalar(s);
    vec3_add(v, &vs, dest);
}

void vec3_sub_scalar(vec3* v, double s, vec3* dest) {
    vec3 vs = vec3_scalar(s);
    vec3_sub(v, &vs, dest);
}

void vec3_mul_scalar(vec3* v, double s, vec3* dest) {
    vec3 vs = vec3_scalar(s);
    vec3_mul(v, &vs, dest);
}

void vec3_div_scalar(vec3* v, double s, vec3* dest) {
    vec3 vs = vec3_scalar(s);
    vec3_div(v, &vs, dest);
}

void vec3_normalize(vec3* v, vec3* dest) {
    vec3_div_scalar(v, vec3_length(v), dest);
}
// ============ [END] VEC3 METHODS ============