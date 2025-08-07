#include <stdlib.h>
#include <stdio.h>
#include "draw.h"
#include "vector.h"

static int color_buffer_width;
static int color_buffer_height;

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
    int k = y + h > color_buffer_height ? color_buffer_height : y + h;
    int l = x + w > color_buffer_width ? color_buffer_width : x + w;
    for (int i = y; i < k; ++i) {
        if (i < 0) { continue; }
        for (int j = x; j < l; ++j) {
            if (j < 0) { continue; }
            color_buffer[i * color_buffer_width + j] = color;
        }
    } 
}

void draw_line(const IVec2 a, const IVec2 b, const uint32_t color) {
    const int dx = b.x - a.x;
    const int dy = b.y - a.y;

    const int side_length = abs(dx) >= abs(dy) ? abs(dx) : abs(dy);
    const float x_inc = (float)dx / (float)side_length;
    const float y_inc = (float)dy / (float)side_length;

    float cx = (float)a.x;
    float cy = (float)a.y;

    for (int i = 0; i < side_length; ++i) {
        draw_pixel((int)cx, (int)cy, color);
        cx += x_inc;
        cy += y_inc;
    }
}

void clear_color_buffer(const uint32_t color) {
    for (int i = 0; i < color_buffer_width * color_buffer_height; ++i) {
        color_buffer[i] = color;
    }
}

/// Map a point to its screen coordinate
IVec2 project_point(const Vec3 point, const float fov_factor) {
    IVec2 projected_point = {
        (int)(point.x * fov_factor / point.z) + (color_buffer_width / 2),
        (int)(point.y * fov_factor / point.z) + (color_buffer_height / 2)
    };
    return projected_point;
}

void debug_print_color_buffer() {
    printf("color buffer: %d x %d\n", color_buffer_width, color_buffer_height);
}
