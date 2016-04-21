#include "global.h"
#include "button.h"
#include "display.h"
#include "calculate.h"

int button_x[4] = {0, 80, 160, 240};
int button_y[5] = {120, 180, 240, 300, 360};

char *button_ch[NUMBER] = {"(", "1", "4", "7", ".",
			")", "2", "5", "8", "0",
			"C", "3", "6", "9", "=",
			"<-", "+", "-", "*", "/"};

int Display_Fontsize = 40;
double result = 0;
char postfix[MAXSIZE] = {'\0'};

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Color button_color = {0xCC, 0xCC, 0xCC, 0xFF};
SDL_Color highlight_color = {0xFF, 0x8C, 0x00, 0xFF};

int init();
int RenderFillRect(SDL_Renderer *renderer, SDL_Rect rect, SDL_Color color);
int PointInRect(SDL_Point p, SDL_Rect r);
int RenderTTF(SDL_Renderer *renderer, TTF_Font *font, char *str, SDL_Rect rect, int x, int y, int fontsize, int flag);

int main(int argc, char *argv[])
{
	int i, j;
	SDL_Texture *texture = NULL;
	TTF_Font *font;
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB555, SDL_TEXTUREACCESS_TARGET,	SCREEN_WIDTH, SCREEN_HEIGHT);
	Button button[NUMBER];
	ButtonInit(button);
	Display display;
	DisplayInit(&display);
	
	if(!init()) {
		printf("Failed to initialize!");
	}else{
		
		int quit = 0;
		SDL_Event e;
		while(!quit){

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
			for(i = 0; i < NUMBER; i++){
				StatusButtonColor(button[i]);			
			        RenderTTF(renderer, font, button[i].button_char, button[i].button_rect, button[i].button_rect.x + 25, button[i].button_rect.y + 10, BUTTON_FONTSIZE, 0);
			}
			DisplayShow(font, display);
		
			while(SDL_PollEvent(&e) != 0){
				if(e.type == SDL_QUIT){
					quit = 1;
				}else if(e.type == SDL_MOUSEBUTTONDOWN){
					if(e.button.button == SDL_BUTTON_LEFT){
						SDL_Point point;
						SDL_GetMouseState(&point.x, &point.y);
						for(i = 0; i < NUMBER; i++){
							if(PointInRect(point, button[i].button_rect))
								button[i].button_color = 1;
						}
					}
				}else{
					for(i = 0; i < NUMBER; i++){
						button[i].button_color = 0;
					}
					if(e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT){
						SDL_Point point;
						SDL_GetMouseState(&point.x, &point.y);
						for(i = 0; i < NUMBER; i++){
							if(PointInRect(point, button[i].button_rect)){
								if(i != 10 && i != 14 && i != 15)
									strcat(display.input, button_ch[i]);
								if(i == 14){
									strcat(display.input, "\n");
									InfixToPostfix(display.input, postfix);
									Calculate(postfix, &result);
								}else if(i == 10){
									strcpy(display.input, "\0");
								}else if(i == 15){
								        display.input[strlen(display.input) - 1] = '\0';
								}
							}
						}
					}
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

int PointInRect(SDL_Point p, SDL_Rect r)
{
  	if(p.x >= r.x && p.x <= (r.x + r.w)){
	  	if(p.y >= r.y && p.y <=(r.y + r.h))
	    		return 1;
		else
		  	return 0;
	} else
	  	return 0;
}

int RenderTTF(SDL_Renderer *renderer, TTF_Font *font, char *str, SDL_Rect rect, int x, int y, int fontsize, int flag)
{
	font = TTF_OpenFont("Choko.ttf", fontsize);
	SDL_Color ttf_color = {0, 0, 0};

	SDL_Texture *ttexture;
	SDL_Surface *surface;
	SDL_Rect rrect;
	ttexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB555, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
	surface = TTF_RenderText_Solid(font, str, ttf_color);
	ttexture = SDL_CreateTextureFromSurface(renderer, surface);
	TTF_SizeText(font, str, &rrect.w, &rrect.h);
	
	if(flag && rrect.w >= DISPLAY_WIDTH && fontsize > 15)
		Display_Fontsize -= 5;
	
	rrect.x = x;
	rrect.y = y;
				
	SDL_SetRenderTarget(renderer, ttexture);
	SDL_RenderCopyEx(renderer, ttexture, NULL, &rrect, 0.0, NULL, SDL_FLIP_NONE); 

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(ttexture);
	TTF_CloseFont(font);
	
	return 0;
}
