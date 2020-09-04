#ifndef UTILS_H
#define UTILS_H

#include <png.h>
#include <stdint.h>
#include <stdio.h>

#include <core/color.h>

#define PIXEL_SIZE 4
#define DEPTH 8

typedef struct {
    color* pixels;
    uint32_t width;
    uint32_t height;
} bitmap;

bitmap* bitmap_create (uint32_t width, uint32_t height, bitmap* dest);
void    bitmap_free   (bitmap* b);

color* bitmap_pixel_at(bitmap* b, uint32_t x, uint32_t y);

void bitmap_to_png_file(bitmap* b, const char* path);

#endif