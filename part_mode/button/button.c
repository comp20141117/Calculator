#include "button.h"


extern int buttonposx[4] = {0, 80, 160, 240};
extern int buttonposy[5] = {160, 240, 320, 400, 480};
extern char buttonchar[20] = {'C', 'D', '*', '/',
				'1', '2', '3', '+',
				'4', '5', '6', '-',
				'7', '8', '9', '=',
				'.', '0', '(', ')'};


Status InitButton()
{
	Button button[20];
	int i, j, k = 0;
	for(i = 0; i < 4; i++){
		for(j = 0; j < 5; j++){
			button[k].bnstatus = OFF;
			button[k].bnrect = {buttonposx[i], buttonposy[j], BUTTON_EDGE, BUTTON_EDGE};
			button[k].bnchar = buttonchar[k];
			k++;
		}
	}
}
