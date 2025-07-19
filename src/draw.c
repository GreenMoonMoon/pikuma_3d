#include <stdlib.h>
#include <stdio.h>
#include "draw.h"

int window_width = 800;
int window_height = 600;

uint32_t *color_buffer = NULL;

void setup_color_buffer(void) {
    color_buffer = malloc(sizeof(uint32_t) * window_width * window_height);
    if(NULL == color_buffer) {
        fprintf(stderr, "Cannot allocate color buffer!\n");
        return;
    }
}

void cleanup_color_buffer(void) {
    if(NULL == color_buffer) { free(color_buffer); }
}

void draw_grid(const int spacing, const uint32_t color) {
    for (int y = 0; y < window_height; ++y) {
        for (int x = 0; x < window_width; ++x) {
            if (y % spacing == 0 || x % spacing == 0) { color_buffer[y * window_width + x] = color; }
        }
    }
}

void draw_rectangle(const int x, const int y, const int w, const int h, const uint32_t color) {
    for (int i = y; i < y + h; ++i) {
        for (int j = x; j < x + w; ++j) {
            color_buffer[i * window_width + j] = color;
        }
    } 
}

void clear_color_buffer(const uint32_t color) {
    for (int i = 0; i < window_width * window_height; ++i) {
        color_buffer[i] = color;
    }
}
