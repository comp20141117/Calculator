#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 420

#define BUTTON_WIDTH 80
#define BUTTON_HEIGHT 60
#define DISPLAY_WIDTH 320
#define DISPLAY_HEIGHT 160

int button_x[4] = {0, 80, 160, 240};
int button_y[5] = {120, 180, 240, 300, 360};

char *button_ch[20] = {"(", "1", "4", "7", ".",
			")", "2", "5", "8", "0",
			"C", "3", "6", "9", "=",
			"<-", "+", "-", "*", "/"};

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

SDL_Color button_color = {0xCC, 0xCC, 0xCC, 0xFF};
SDL_Color highlight_color = {0xFF, 0x8C, 0x00, 0xFF};

typedef struct _BUTTON
{
	SDL_Rect button_rect;
	int button_status;
	char *button_char;
}Button;

int RenderFillRect(SDL_Renderer *renderer, SDL_Rect rect, SDL_Color color)
{
	SDL_RenderDrawRect(renderer, &rect); 
	SDL_SetRenderDrawColor(renderer, 
			       color.r, 
			       color.g, 
			       color.b, 
			       color.a); 
	SDL_RenderFillRect(renderer, &rect);
	return 1;
}

int StatusButton(Button btn)
{
	if(btn.button_status == 1){
		RenderFillRect(renderer, btn.button_rect, highlight_color);
	}else{
		RenderFillRect(renderer, btn.button_rect, button_color);
	}
	return 1;
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
			"Calculator",
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
			if(TTF_Init() == -1){
				printf("ttf init fail!\n");
			}
		}
	}

	return success;
 }

int main(int argc, char *argv[])
{
	int i, j;
	SDL_Texture *texture = NULL;
	TTF_Font *font;
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB555, SDL_TEXTUREACCESS_TARGET,	SCREEN_WIDTH, SCREEN_HEIGHT);
	
	if(!init()) {
		printf("Failed to initialize!");
	}else{
		
		int quit = 0;
		SDL_Event e;
		while(!quit){

			Button button[20];
			for(i = 0; i < 20; i++){
				button[i].button_rect.x = button_x[i/5] + 4;
				button[i].button_rect.y = button_y[i%5] + 3;
				button[i].button_rect.w = BUTTON_WIDTH - 8;
				button[i].button_rect.h = BUTTON_HEIGHT - 6;
				button[i].button_char = button_ch[i];
				button[i].button_status = 0;
			}
			
			SDL_SetRenderTarget(renderer, texture);
			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);			
			SDL_RenderClear(renderer);

			SDL_SetRenderTarget(renderer, texture);
			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);			
			for(i = 0; i < 4; i++){
				SDL_RenderDrawLine(renderer, button_x[i], button_y[0], button_x[i], SCREEN_HEIGHT);
			}
			for(i = 0; i < 5; i++){
				SDL_RenderDrawLine(renderer, button_x[0], button_y[i], SCREEN_WIDTH, button_y[i]);
			}
			for(i = 0; i < 20; i++){
				RenderFillRect(renderer, button[i].button_rect, button_color);
			
				font = TTF_OpenFont("Choko.ttf", 35);
				SDL_Color ttf_color = {0, 0, 0};

				SDL_Texture *ttexture;
				SDL_Surface *surface;
				SDL_Rect rect;
				ttexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB555, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
				surface = TTF_RenderText_Solid(font, button[i].button_char, ttf_color);
				ttexture = SDL_CreateTextureFromSurface(renderer, surface);

				TTF_SizeText(font, button[i].button_char, &rect.w, &rect.h);
				rect.x = button[i].button_rect.x + (BUTTON_WIDTH - rect.w)/2;
				rect.y = button[i].button_rect.y + (BUTTON_HEIGHT - rect.h)/2;
				
				SDL_SetRenderTarget(renderer, ttexture);
				SDL_RenderCopyEx(renderer, ttexture, NULL, &rect, 0.0, NULL, SDL_FLIP_NONE); 

				SDL_FreeSurface(surface);
				SDL_DestroyTexture(ttexture);
				TTF_CloseFont(font);
			}
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
	
	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
	return 0;
}
