#include <core/color.h>

color color_rgb (uint8_t r, uint8_t g, uint8_t b){
    return (color){ r, g, b, 255u };
}
color color_vec3(vec3* v){
    return (color){
        (uint8_t)(v->x * 255.0),
        (uint8_t)(v->y * 255.0),
        (uint8_t)(v->z * 255.0),
        255u
    };
}
color color_vec4(vec4* v){
    return (color){
        (uint8_t)(v->x * 255.0),
        (uint8_t)(v->y * 255.0),
        (uint8_t)(v->z * 255.0),
        (uint8_t)(v->w * 255.0)
    };
}

color* color_lerp(color* a, color* b, const double t, color* dest) {
    dest->r = (uint32_t)(a->r * (1.0 - t) + b->r * t);
    dest->g = (uint32_t)(a->g * (1.0 - t) + b->g * t);
    dest->b = (uint32_t)(a->b * (1.0 - t) + b->b * t);
    dest->a = (uint32_t)(a->a * (1.0 - t) + b->a * t);
    return dest;
}