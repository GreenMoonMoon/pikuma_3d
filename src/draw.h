#ifndef DRAW_PIKUMA3D_H
#define DRAW_PIKUMA3D_H

#include <stdint.h>
#include "vector.h"

extern uint32_t *color_buffer;

void setup_color_buffer(int width, int height);

void cleanup_color_buffer(void);

void draw_pixel(unsigned x, unsigned y, uint32_t color);

void draw_grid(int spacing, uint32_t color);

void draw_rectangle(int x, int y, int w, int h, uint32_t color);

void clear_color_buffer(uint32_t color);

IVector2 project_point(Vector3 point, const float fov_factor);

void debug_print_color_buffer();

#endif//DRAW_PIKUMA3D_H
