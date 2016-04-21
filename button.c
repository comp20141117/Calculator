#include "button.h"


int StatusButtonColor(Button btn)
{
	if(btn.button_color){
		RenderFillRect(renderer, btn.button_rect, highlight_color);
	}else{
		RenderFillRect(renderer, btn.button_rect, button_color);
	}
	return 1;
}

void ButtonInit(Button btn[])
{
	int i;
	for(i = 0; i < 20; i++){
		btn[i].button_rect.x = button_x[i/5] + 4;
		btn[i].button_rect.y = button_y[i%5] + 3;
		btn[i].button_rect.w = BUTTON_WIDTH - 8;
		btn[i].button_rect.h = BUTTON_HEIGHT - 6;
		btn[i].button_char = button_ch[i];
		btn[i].button_status = 0;
	}
}
