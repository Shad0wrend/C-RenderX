#include <SDL.h> 
#include <stdio.h>
#include <stdbool.h> 
#include <stdint.h> 
#include "Display.h"
#include "Vector.h"

// Declare array of vectors/points
const int N_POINTS = 9 * 9 / 9;
vec3_t cube_points[9 * 9 * 9]; // 9x9x9 cube

bool is_running = false;	

// Function to setup the window
void setup(void) {
	// Allocate the memory to hold the color buffer
	color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * window_width * window_height);

	// Create a texture that is used to draw to the screen
	color_buffer_texture = SDL_CreateTexture(				
		renderer,												
		SDL_PIXELFORMAT_ARGB8888,							
		SDL_TEXTUREACCESS_STREAMING,						
		window_width,										
		window_height										
	);

	int point_count = 0;

	// Start loading my array of vectors
	// From -1 to 1 (9x9x9 cube)
	for (float x = -1; x <= 1; x += 0.25) {
		for (float y = -1; y <= 1; y += 0.25) {
			for (float z = -1; z <= 1; z += 0.25) {
				vec3_t new_point = { .x = x, .y = y, .z = z };
				cube_points[point_count++] = new_point;
			}
		}
	}

}
// Function to process the input
void process_input(void) {									
	SDL_Event event;										
	SDL_PollEvent(&event);								

	// Check if the user has closed the window
	switch (event.type) {										
	case SDL_QUIT:											
		is_running = false;									
		break;												
	case SDL_KEYDOWN:										
		if (event.key.keysym.sym == SDLK_ESCAPE)			
			is_running = false;								
		break;												
	}
}


// Function that takes 3D vector and projects 2D point
vec2_t project(vec3_t point) {
	vec2_t projected_point = {
		.x = point.x,
		.y = point.y
	};
	return projected_point;
}




// Function to update the window
void update(void) {
	//TODO : Implement
}

// Function to render the window
void render(void) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	draw_grid();

	draw_pixel(20, 20, 0xFFFF0000);

	draw_rect(300, 200, 300, 150, 0xFF00FF00);

	render_color_buffer();
	clear_color_buffer(0xFF000000);

	SDL_RenderPresent(renderer);
}

// Main function
int main(void) {
	is_running = initialize_window();		

	setup();

	while (is_running) {					
		process_input();				
		update();							
		render();								
	}
	destroy_window();						
	return 0;
}