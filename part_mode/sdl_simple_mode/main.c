#include <stdio.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 560

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

int init()
{
	int success = 1;

	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = 0;
	}
	else {
		if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Warning: Linear texture filtering not enabled!\n");
		}

		window = SDL_CreateWindow(
			"display",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		if(window == NULL) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = 0;
		}
		else {
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if(renderer == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			}
		}
	}

	return success;
 }

int main(int argc, char *argv[])
{
	SDL_Texture *texture = NULL;
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB555, SDL_TEXTUREACCESS_TARGET,	SCREEN_WIDTH, SCREEN_HEIGHT);
	
	if(!init()) {
		printf("Failed to initialize!");
	}else{
		
		int quit = 0;
		SDL_Event e;
		while(!quit){
			
			SDL_SetRenderTarget(renderer, texture);
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(renderer);
			
			while(SDL_PollEvent(&e) != 0){
				if(e.type == SDL_QUIT){
					quit = 1;
				}
				
	
			}

			SDL_SetRenderTarget(renderer, NULL);
			SDL_RenderCopy(renderer, texture, NULL, NULL);   
			SDL_RenderPresent(renderer);
		}
	}

	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
	return 0;
}
