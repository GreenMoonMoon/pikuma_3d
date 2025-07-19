#ifndef DRAW_PIKUMA3D_H
#define DRAW_PIKUMA3D_H

#include <stdint.h>

extern int window_width;
extern int window_height;

extern uint32_t *color_buffer;

void setup_color_buffer(void);

void cleanup_color_buffer(void);

void draw_grid(const int spacing, const uint32_t color);

void draw_rectangle(const int x, const int y, const int w, const int h, const uint32_t color);

void clear_color_buffer(const uint32_t color);

#endif//DRAW_PIKUMA3D_H
