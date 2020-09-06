#ifndef CORE_COLOR_H
#define CORE_COLOR_H

#include <stdint.h>

#include <maths.h>

// ============ CONSTANTS ============
#define BLACK   color_rgb( 0,    0,   0);
#define WHITE   color_rgb(255, 255, 255);
#define RED     color_rgb(255,   0,   0);
#define GREEN   color_rgb(  0, 255,   0);
#define BLUE    color_rgb(  0,   0, 255);
#define MAGENTA color_rgb(255,   0, 255);
#define CYAN    color_rgb(  0, 255, 255);
#define YELLOW  color_rgb(255, 255,   0);

// ============ STRUCTS ============
typedef struct { uint8_t r, g, b, a; } color;

// ============ COLOR METHODS ============
color  color_rgb  (uint8_t r, uint8_t g, uint8_t b);
color  color_vec3 (vec3* v);
color* color_lerp (color* a, color* b, const double t, color* dest);

#endif