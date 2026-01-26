#include "t3d/t3d.h"
#include <graphics.h>
#include <lib/utils.h>
#include <globals.h>
#include <video/dz_display.h>

inline void display_switch_widescreen(u8* displaySettings) {
  *displaySettings ^= DISPLAY_BITMASK_WIDESCREEN;
}

inline void display_set_widescreen(u8* displaySettings, bool enableWidescreen) {
  BIT_SET_BOOL(*displaySettings, enableWidescreen, DISPLAY_BITMASK_WIDESCREEN);
}

inline bool display_widescreen_enabled(u8* displaySettings) {
  return (*displaySettings & DISPLAY_BITMASK_WIDESCREEN) != 0;
}


inline void display_switch_antialiasing(u8* displaySettings) {
  *displaySettings ^= DISPLAY_BITMASK_ANTIALIAS;
}

inline void display_set_antialiasing(u8* displaySettings, bool enableAA) {
  BIT_SET_BOOL(*displaySettings, enableAA, DISPLAY_BITMASK_ANTIALIAS);
}

inline bool display_antialiasing_enabled(u8* displaySettings) {
  return (*displaySettings & DISPLAY_BITMASK_ANTIALIAS) != 0;
}


void display_update_settings(u8* displaySettings, Camera* camera) {
  // Disable interrupts cuz if this func is interrupted
  // the screen & rdp stuff break
  disable_interrupts();

  bool widescreenEnabled = display_widescreen_enabled(displaySettings);
  u16 new_width;
  filter_options_t new_filter;

  if (widescreenEnabled)
    new_width = DISPLAY_WIDESCREEN_WIDTH;
  else
    new_width = DISPLAY_DEFAULT_WIDTH;

  if (display_antialiasing_enabled(displaySettings))
    new_filter = FILTERS_RESAMPLE_ANTIALIAS;
  else
    new_filter = FILTERS_RESAMPLE;

  // @TODO: is this much function calls ok?
  //  I mean, it's not like we're updating the display
  //  setting every frame (and should NEVER be the case), but still.
  rdpq_detach();
  display_close();
  display_init(
    (const resolution_t) {
      .width = new_width,
      .height = DISPLAY_DEFAULT_HEIGHT,
      .interlaced = INTERLACE_OFF
    },
    DEPTH_16_BPP,
    FB_COUNT,
    GAMMA_NONE,
    new_filter
  );
  rdpq_attach(display_get(), display_get_zbuf());

  if (camera != NULL) {
    float aspectRatio;
    if (widescreenEnabled)
      aspectRatio = 16.0f/9.0f;
    else
      aspectRatio = 4.0f/3.0f;
    t3d_viewport_set_area(&camera->viewport, 0, 0, new_width, DISPLAY_DEFAULT_HEIGHT);
    Camera_SetAspectRatio(camera, aspectRatio);
    // Camera_Attach(camera);
  }

  enable_interrupts();
}
