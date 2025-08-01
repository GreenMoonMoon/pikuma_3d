#ifndef PIKUMA3D_DRAW_H
#define PIKUMA3D_DRAW_H

#include <stdint.h>
#include "vector.h"

#define WHITE       0xFFFFFFFF
#define BLACK       0xFF000000
#define DARKGREY    0xFF333333 
#define RED         0XFFFF0000
#define GREEN       0XFF00FF00
#define BLUE        0XFF0000FF
#define MAGENTA     0XFFFF00FF
#define YELLOW      0XFFFFFF00
#define CYAN        0XFFFF00FF

extern uint32_t *color_buffer;

void setup_color_buffer(int width, int height);

void cleanup_color_buffer(void);

void draw_pixel(unsigned x, unsigned y, uint32_t color);

void draw_grid(int spacing, uint32_t color);

void draw_rectangle(int x, int y, int w, int h, uint32_t color);

void draw_line(IVector2 a, IVector2 b);

void clear_color_buffer(uint32_t color);

IVector2 project_point(Vector3 point, const float fov_factor);

void debug_print_color_buffer();

#endif//PIKUMA3D_DRAW_H
