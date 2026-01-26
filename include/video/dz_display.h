#ifndef DZ_DISPLAY_H
#define DZ_DISPLAY_H

#include <lib/types.h>

#define DISPLAY_WIDESCREEN_WIDTH  428
#define DISPLAY_DEFAULT_WIDTH     320
#define DISPLAY_DEFAULT_HEIGHT    240

// settings masks
#define DISPLAY_BITMASK_WIDESCREEN  (1 << 0)
#define DISPLAY_BITMASK_ANTIALIAS   (1 << 1)

void display_switch_widescreen(u8* displaySettings);
void display_set_widescreen(u8* displaySettings, bool enableWidescreen);
bool display_widescreen_enabled(u8* displaySettings);

void display_switch_antialiasing(u8* displaySettings);
void display_set_antialiasing(u8* displaySettings, bool enableAA);
bool display_antialiasing_enabled(u8* displaySettings);

void display_update_settings(u8* new_settings);

#endif
