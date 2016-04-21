#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "global.h"

#define BUTTON_WIDTH 80
#define BUTTON_HEIGHT 60
#define BUTTON_FONTSIZE 40

typedef struct _BUTTON
{
	SDL_Rect button_rect;
	int button_status;
	int button_color;
	char *button_char;
}Button;

int StatusButtonColor(Button btn);
void ButtonInit(Button btn[]);

#endif
