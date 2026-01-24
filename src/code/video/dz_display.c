#include <graphics.h>
#include "interrupt.h"
#include "rdpq_attach.h"
#include <globals.h>
#include <video/dz_display.h>

bool gWidescreenEnabled = false;


void display_switch_widescreen() {
  display_set_widescreen(!gWidescreenEnabled);
}

void display_set_widescreen(bool enableWidescreen) {
  // Disable interrupts cuz if this func is interrupted
  // the screen & rdp stuff break
  disable_interrupts();

  u16 new_width;

  gWidescreenEnabled = enableWidescreen;

  if (gWidescreenEnabled)
    new_width = DISPLAY_WIDESCREEN_WIDTH;
  else
    new_width = DISPLAY_DEFAULT_WIDTH;

  // @TODO: is this much function calls ok?
  //  I mean, it's not like we're switching widescreen
  //  every frame, but still.
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
    FILTERS_RESAMPLE
  );
  rdpq_attach(display_get(), display_get_zbuf());

  enable_interrupts();
}

inline bool display_widescreen_enabled() {
  return gWidescreenEnabled;
}
