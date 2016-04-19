#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 160
#define NUMBER 15

int TTF_FONTSIZE = 30;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

char str[100] = "\0";

int keystate[NUMBER] = {SDL_SCANCODE_KP_0, SDL_SCANCODE_KP_1, SDL_SCANCODE_KP_2, SDL_SCANCODE_KP_3,
		    SDL_SCANCODE_KP_4, SDL_SCANCODE_KP_5, SDL_SCANCODE_KP_6,
		    SDL_SCANCODE_KP_7, SDL_SCANCODE_KP_8, SDL_SCANCODE_KP_9,
		    SDL_SCANCODE_KP_PLUS, SDL_SCANCODE_KP_MINUS,
		    SDL_SCANCODE_KP_MULTIPLY, SDL_SCANCODE_KP_DIVIDE, SDL_SCANCODE_KP_PERIOD};

char *charstate[NUMBER] = {"0\0", "1\0", "2\0", "3\0", "4\0",
		       "5\0", "6\0", "7\0", "8\0", "9\0",
		       "+\0", "-\0", "*\0", "/\0", ".\0"};

int ShowText(TTF_Font *font, SDL_Renderer *renderer, SDL_Texture *texture, char *str)
{
	font = TTF_OpenFont("Choko.ttf", TTF_FONTSIZE);
	const char *fstr = str;
	SDL_Color color = {0, 0, 0};
				
	SDL_Texture *ttexture;
	SDL_Surface *surface;
	ttexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB555, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_Rect display = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	TTF_SizeText(font, fstr, &display.w, &display.h);
	
	if(display.w >= SCREEN_WIDTH && TTF_FONTSIZE > 15)
		TTF_FONTSIZE -= 5;

	surface = TTF_RenderText_Solid(font, fstr, color);
	ttexture = SDL_CreateTextureFromSurface(renderer, surface);
				
	SDL_SetRenderTarget(renderer, ttexture);
	SDL_RenderCopyEx(renderer, ttexture, NULL, &display, 0.0, NULL, SDL_FLIP_NONE); 

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(ttexture);
	TTF_CloseFont(font);
				
	SDL_SetRenderTarget(renderer, NULL);
	SDL_RenderCopy(renderer, texture, NULL, NULL);   
	SDL_RenderPresent(renderer);
}

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
			}else{
				if(TTF_Init() == -1){
					printf("TTF could not be create! SDL Error: %s\n", SDL_GetError());
				}
			}
		}
	}

	return success;
 }

int main(int argc, char *argv[])
{
	int i;
	char *ch = "\0";
	
	TTF_Font *font;
	
	SDL_Texture *texture = NULL;

	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB555, SDL_TEXTUREACCESS_TARGET,	SCREEN_WIDTH, SCREEN_HEIGHT);
	
	if(!init()) {
		printf("Failed to initialize!");
	}else{
		
		int quit = 0;
		SDL_Event e;
		while(!quit){

			while(SDL_PollEvent(&e) != 0){
				if(e.type == SDL_QUIT){
					quit = 1;
				}

				SDL_SetRenderTarget(renderer, texture);
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(renderer);

				const Uint8 *state = SDL_GetKeyboardState(NULL);
					for(i = 0; i < NUMBER; i++){
						if(state[keystate[i]]){
							ch = charstate[i];
							if(strlen(str) < 100){
								strcat(str, ch);
								SDL_Delay(250);
							}
						}
					}
				
				ShowText(font, renderer, texture, str);
			}
		}
	}

	
	TTF_Quit();
	SDL_DestroyTexture(texture);
	texture = NULL;
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
	return 0;
}
