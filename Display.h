#pragma once
#ifndef DISPLAY_H
#define DISPLAY_H


#include <SDL.h> 
#include <stdbool.h> 
#include <stdint.h> 

// Variables and global declaration
extern int window_width;
extern int window_height;
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern uint32_t* color_buffer;
extern SDL_Texture* color_buffer_texture;

// Function prototypes
bool initialize_window(void);
void draw_pixel(int x, int y, uint32_t color);
void draw_grid(void);
void draw_rect(int x, int y, int width, int height, uint32_t color);
void render_color_buffer(void);
void clear_color_buffer(uint32_t color);
void destroy_window(void);

#endif