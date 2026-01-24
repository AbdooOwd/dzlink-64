#ifndef DZ_DISPLAY_H
#define DZ_DISPLAY_H

#include <lib/types.h>

#define DISPLAY_WIDESCREEN_WIDTH  428
#define DISPLAY_DEFAULT_WIDTH     320
#define DISPLAY_DEFAULT_HEIGHT    240

void display_switch_widescreen();
void display_set_widescreen(bool enableWidescreen);

#endif
