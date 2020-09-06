#ifndef CORE_H
#define CORE_H

#include <stdbool.h>
#include <stdint.h>
#include <math.h>

#include <color.h>
#include <maths.h>

// ============ STRUCTS ============
typedef struct { vec3 origin, direction; }                                                            ray;
typedef struct { vec3 point, normal; double t; bool front_face; }                                     hit;
typedef struct { vec3 position; double radius; uint32_t type; }                                       sphere;
typedef struct { sphere* spheres; uint32_t n_spheres; }                                               world;
typedef struct { vec3 origin, lower_left_corner, horizontal, vertical, u, v, w; double lens_radius; } camera;

// ============ ENUMS ============
enum primtive { SPHERE };

// ============ RAY METHODS ============
vec3*   ray_at              (ray* r, double* t, vec3* dest);
color*  ray_color           (ray* r, world* w, color* c);
void    ray_hit_face_normal (ray* r, hit* h);

// ============ SPHERE METHODS ============
sphere* sphere_create       (vec3* position, double* radius, sphere* dest);
bool    sphere_ray_hit      (sphere* s, ray* r, double* t_min, double* t_max, hit* h);

// ============ WORLD METHODS ============
world*  world_create        (world* w);
world*  world_free          (world* w);
bool    world_hit           (world* w, ray* r, double* t_min, double* t_max, hit* h);

// ============ CAMERA METHODS ============
camera* camera_setup        (vec3* lookfrom, vec3* lookat, vec3* vup, double* vfov, double* aspect_ratio, double* aperture, double* focus_dist, camera* cam);
ray*    camera_ray          (double* s, double* t, camera* cam, ray* r);

#endif