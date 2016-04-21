#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#define DISPLAY_WIDTH 320
#define DISPLAY_HEIGHT 120

#include "global.h"
#include "button.h"

typedef struct _DISPLAY
{
	SDL_Rect display_input;
	char input[MAXSIZE];
	SDL_Rect display_output;
	char output[MAXSIZE];
}Display;

void DisplayInit(Display *ds);
void DisplayShow(TTF_Font *font, Display ds);

#endif
