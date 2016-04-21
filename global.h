#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <stdio.h>
#include <SDL2/SDL.h>
#include <string.h>
#include <SDL2/SDL_ttf.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 420

#define MAXSIZE 100
#define NUMBER 20

extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern double result;
extern int button_x[4];
extern int button_y[5];
extern char *button_ch[NUMBER];
extern SDL_Color button_color;
extern SDL_Color highlight_color;
extern int Display_Fontsize;

extern int RenderFillRect(SDL_Renderer *renderer, SDL_Rect rect, SDL_Color color);
extern int PointInRect(SDL_Point p, SDL_Rect r);
extern int RenderTTF(SDL_Renderer *renderer, TTF_Font *font, char *str, SDL_Rect rect, int x, int y, int fontsize, int flag);

#endif
