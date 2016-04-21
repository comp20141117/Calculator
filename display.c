#include "display.h"

void DisplayInit(Display *ds)
{
	ds->display_input.x = 0 + 4;
	ds->display_input.y = 0 + 3;
	ds->display_input.w = DISPLAY_WIDTH - 8;
	ds->display_input.h = (DISPLAY_HEIGHT)/2 - 6;

	strcpy(ds->input, "\0");
	
	ds->display_output.x = 0 + 4;
	ds->display_output.y = ((DISPLAY_HEIGHT)/2) + 3;
	ds->display_output.w = DISPLAY_WIDTH - 8;
	ds->display_output.h = ((DISPLAY_HEIGHT)/2) - 6;

	strcpy(ds->output, "\0");
}
void DisplayShow(TTF_Font *font, Display ds)
{
		RenderTTF(renderer, font, ds.input, ds.display_input, ds.display_input.x, ds.display_input.y, Display_Fontsize, 1);
		sprintf(ds.output, "%lf", result);
		RenderTTF(renderer, font, ds.output, ds.display_output, ds.display_output.x, ds.display_output.y, BUTTON_FONTSIZE, 0);
}
