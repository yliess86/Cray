#include <utils.h>

bitmap* bitmap_create(uint32_t width, uint32_t height, bitmap* dest) {
    dest->width = width; 
    dest->height = height;
    dest->pixels = (color*)malloc(width * height * sizeof(color));

    return dest; 
}
void bitmap_free(bitmap* b) {
    free(b->pixels);
    b = NULL;
}


color* bitmap_pixel_at(bitmap* b, uint32_t x, uint32_t y) {
    uint32_t id = x + y * b->width;
    return &b->pixels[id]; 
}

void bitmap_to_png_file(bitmap* b, const char* path) {
    FILE* fp = fopen(path, "wb");
    
    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info = png_create_info_struct(png);
    
    png_set_IHDR(
        png, info, b->width, b->height,
        DEPTH,
        PNG_COLOR_TYPE_RGB_ALPHA,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT
    );

    png_byte** rows = png_malloc(png, b->height * sizeof(png_byte*));
    for(uint32_t y = 0; y < b->height; y++) {
        png_byte* row = png_malloc(png, b->width * PIXEL_SIZE * sizeof(uint8_t));
        rows[y] = row;
        for(uint32_t x = 0; x < b->width; x++) {
            color* pixel = bitmap_pixel_at(b, x, y);
            *row++ = pixel->r;
            *row++ = pixel->g;
            *row++ = pixel->b;
            *row++ = pixel->a;
        }
    }

    png_init_io (png, fp);
    png_set_rows (png, info, rows);
    png_write_png (png, info, PNG_TRANSFORM_IDENTITY, NULL);

    for (uint32_t y = 0; y < b->height; y++)
        png_free(png, rows[y]);
    png_free (png, rows);
    fclose(fp);
    png_destroy_write_struct(&png, &info);
}