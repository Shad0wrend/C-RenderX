#include "Display.h"
#include <SDL.h> 
#include <stdio.h>
#include <stdbool.h> 
#include <stdint.h> 

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
uint32_t* color_buffer = NULL;
SDL_Texture* color_buffer_texture = NULL;
int window_width = 800;
int window_height = 600;

// Function to initialize the window
bool initialize_window(void) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error initializing SDL.\n");
		return false;
	}

	// Use SDL to query the display for the window
	SDL_DisplayMode display_mode;
	SDL_GetCurrentDisplayMode(0, &display_mode);
	window_width = display_mode.w;
	window_height = display_mode.h;

	// Create a window
	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		window_width,
		window_height,
		SDL_WINDOW_BORDERLESS
	);
	if (!window) {
		fprintf(stderr, "Error creating SDL window.\n");
		return false;
	}

	// Create SDL renderer
	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		fprintf(stderr, "Error creating SDL renderer.\n");
		return false;
	}
	// Set the window to fullscreen
	// SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN); // Native Fullscreen
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP); // Borderless Fullscreen
	return true;
}

// Function to draw grid
void draw_grid(void) {
	for (int y = 0; y < window_height; y+= 10) {
		for (int x = 0; x < window_width; x+= 10) {
				color_buffer[(window_width * y) + x] = 0xFF00FF00;
			}
		}
	}


//Function to draw pixel
void draw_pixel(int x, int y, uint32_t color) {
	if (x < window_width && y < window_height) {
		color_buffer[(window_width * y) + x] = color;
		}
	}

// Function to draw rectangle
void draw_rect(int x, int y, int width, int height, uint32_t color) {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			int current_x = x + i;
			int current_y = y + j;
			color_buffer[(window_width * current_y) + current_x] = color;
		}
	}
}

// Function to render the color buffer
void render_color_buffer(void) {
	SDL_UpdateTexture(
		color_buffer_texture,
		NULL,
		color_buffer,
		(int)(window_width * sizeof(uint32_t))
	);
	SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

// Function to clear the color buffer
void clear_color_buffer(uint32_t color) {
	for (int y = 0; y < window_height; y++) {
		for (int x = 0; x < window_width; x++) {
			color_buffer[(window_width * y) + x] = color;
		}
	}
}

// Function to destroy the window
void destroy_window(void) {
	free(color_buffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
