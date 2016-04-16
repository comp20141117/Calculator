#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 160
#define TTF_FONTSIZE 18

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

/*char *keystate[9] = {"SDL_SCANCODE_1", "SDL_SCANCODE_2", "SDL_SCANCODE_3",
		    "SDL_SCANCODE_4", "SDL_SCANCODE_5", "SDL_SCANCODE_6",
		    "SDL_SCANCODE_7", "SDL_SCANCODE_8", "SDL_SCANCODE_9"};
char charstate[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

char KeyStates()
{
	char ch;
	int i;
	const Uint8 *keyStates = SDL_GetKeyboardstate(NULL);
	for(i = 0; i < 9; i++){
		if(keyStates[keystate[i]])
			ch = charstate[i];
	}
	return ch;
	}*/

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
			"SDL Tutorial",
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
//	TTF_Font *font;
//	font = TTF_OpenFont("Choko.ttf", TTF_FONTSIZE);
//	SDL_Texture *texture = NULL;
//	const char *str = "hello guy";
//	SDL_Color color = {0, 0, 0};
//	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB555, SDL_TEXTUREACCESS_TARGET,	SCREEN_WIDTH, SCREEN_HEIGHT);
	if(!init()) {
		printf("Failed to initialize!");
	}else{
		int quit = 0;
		SDL_Event e;
		while(!quit){
//			const char ch;
			
			while(SDL_PollEvent(&e) != 0){
				if(e.type == SDL_QUIT){
					quit = 1;
				}
//				ch = KeyStates();
//				strcat(str, &ch);
//				SDL_SetRenderTarget(renderer, texture);
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(renderer);
				
//				SDL_Texture *ttexture;
//				SDL_Surface *surface;
//				SDL_Rect display = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

//				SDL_RenderDrawRect(renderer, &display); 
//				SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0x00);
//				SDL_RenderFillRect(renderer, &display);
/*				
				surface = TTF_RenderText_Solid(font, "hello guy", color);
				ttexture = SDL_CreateTextureFromSurface(renderer, surface);				
				SDL_RenderCopyEx(renderer, ttexture, NULL, &display, 0.0, NULL, SDL_FLIP_NONE); 
*/
//				SDL_FreeSurface(surface);
//				SDL_DestroyTexture(ttexture);
				
				SDL_SetRenderTarget(renderer, NULL);
//				SDL_RenderCopy(renderer, texture, NULL, NULL);   
				SDL_RenderPresent(renderer);

			}
		}
	}

//	TTF_CloseFont(font);
	TTF_Quit();
//	SDL_DestroyTexture(texture);
//	texture = NULL;
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
	return 0;
}
