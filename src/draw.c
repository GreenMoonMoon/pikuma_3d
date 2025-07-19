#include <stdlib.h>
#include <stdio.h>
#include "draw.h"

static int color_buffer_width = 800;
static int color_buffer_height = 600;

uint32_t *color_buffer = NULL;

void setup_color_buffer(const int width, const int height) {
    color_buffer_width = width / 4;
    color_buffer_height = height / 4;
    color_buffer = malloc(sizeof(uint32_t) * color_buffer_width * color_buffer_height);
    if(NULL == color_buffer) {
        fprintf(stderr, "Cannot allocate color buffer!\n");
        return;
    }
}

void cleanup_color_buffer(void) {
    if(NULL == color_buffer) { free(color_buffer); }
}

void draw_pixel(const unsigned x, const unsigned y, const uint32_t color) {
    if (x > color_buffer_width || y > color_buffer_height) { return; }
    color_buffer[y * color_buffer_width + x] = color;
}

void draw_grid(const int spacing, const uint32_t color) {
    for (int y = 0; y < color_buffer_height; ++y) {
        for (int x = 0; x < color_buffer_width; ++x) {
            if (y % spacing == 0 || x % spacing == 0) { color_buffer[y * color_buffer_width + x] = color; }
        }
    }
}

void draw_rectangle(const int x, const int y, const int w, const int h, const uint32_t color) {
    for (int i = y; i < y + h; ++i) {
        if (i < 0) { continue; }
        for (int j = x; j < x + w; ++j) {
            if (j < 0) { continue; }
            color_buffer[i * color_buffer_width + j] = color;
        }
    } 
}

void clear_color_buffer(const uint32_t color) {
    for (int i = 0; i < color_buffer_width * color_buffer_height; ++i) {
        color_buffer[i] = color;
    }
}
