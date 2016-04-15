#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <stdio.h>
#include <SDL2/SDL.h>

#define ON 1
#define OFF 0

#define HIGHLIGTH_COLOR {0xCC, 0xCC, 0xCC}
#define BUTTON_EDGE 80

#define TEXT_COLOR {0xEA, 0xEA, 0xEA}
#define TEXT_WIDTH 320
#define TEXT_HIGHTH 160

extern int buttonposx[4];
extern int buttonposy[5];
extern char buttonchar[20];

typedef int Status;

typedef struct _BUTTON
{
	SDL_Rect bnrect;
	Status bnstatus;
	char bnchar;
}Button;

Status InitButton();

#endif
