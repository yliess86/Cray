#ifndef CORE_H
#define CORE_H

#include <stdbool.h>
#include <stdint.h>
#include <math.h>

#include <color.h>
#include <maths.h>

// ============ CONSTANTS ============
#define ARRAY_DEFAULT 10
#define ARRAY_GROWTH  1.5

// ============ STRUCTS ============
typedef struct { vec3 origin, direction; }                                                            ray;

typedef struct { vec3 albedo; }                                                                       lambertian;
typedef struct { vec3 albedo; double fuzz; }                                                          metalic;
typedef struct { vec3 albedo; double eta; }                                                           dielectric;
typedef struct { uint32_t type; union { lambertian* l; metalic* m; dielectric* d; } data; }           material;

typedef struct { vec3 point, normal; double t; bool front_face; material* m; }                        hit;

typedef struct { vec3 position; double radius; material* m; }                                         sphere;
typedef struct { vec3 position; vec3 normal; material* m; }                                           plane;
typedef struct { uint32_t type; union { sphere* s; plane* p; } data; }                                object;

typedef struct { object* objects; uint32_t n_objects; uint32_t n_max_objects; }                       world;

typedef struct { vec3 origin, lower_left_corner, horizontal, vertical, u, v, w; double lens_radius; } camera;

// ============ ENUMS ============
enum primtives { SPHERE, PLANE };
enum materials { LAMBERTIAN, METALIC, DIELECTRIC };

// ============ RAY METHODS ============
void ray_at              (ray* r, double t, vec3* dest);
vec3 ray_color           (ray* r, world* w, int depth);
void ray_hit_face_normal (ray* r, hit* h);

// ============ MATERIAL METHODS ============
void lambertian_create   (vec3* albedo, material* dest);
void metalic_create      (vec3* albedo, double fuzz, material* dest);
void dielectric_create   (vec3* albedo, double eta, material* dest);

bool lambertian_scatter  (lambertian* l, hit* h, vec3* attenuation, ray* r_scattered);
bool metalic_scatter     (metalic* m, ray* r_in, hit* h, vec3* attenuation, ray* r_scattered);
bool dielectric_scatter  (dielectric* d, ray* r_in, hit* h, vec3* attenuation, ray* r_scattered);
bool material_scatter    (material* m, ray* r_in, hit* h, vec3* attenuation, ray* r_scattered);

// ============ SPHERE METHODS ============
void sphere_create       (vec3* position, double radius, material* m, sphere* dest);
bool sphere_ray_hit      (sphere* s, ray* r, double t_min, double t_max, hit* h);

// ============ WORLD METHODS ============
void  world_create       (world* w);
void  world_add_sphere   (world* w, sphere* s);
void  world_free         (world* w);
bool  world_hit          (world* w, ray* r, double t_min, double t_max, hit* h);

// ============ CAMERA METHODS ============
void  camera_setup       (vec3* lookfrom, vec3* lookat, vec3* vup, double vfov, double aspect_ratio, double aperture, double focus_dist, camera* cam);
void  camera_ray         (double s, double t, camera* cam, ray* r);

#endif