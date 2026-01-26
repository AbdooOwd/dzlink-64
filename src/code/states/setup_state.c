#include "fonts.h"
#include "game.h"
#include "globals.h"
#include "graphics.h"
#include "joypad.h"
#include "rdpq_attach.h"
#include "rdpq_text.h"
#include <states/setup_state.h>

void SetupState_Init(void* state) {
}

void SetupState_Main(void* state) {
  rdpq_clear(RGBA16(0, 0, 0, 0));
  rdpq_text_printf(NULL, FONTID_DBG_VAR, 10.0f, 30.0f,
                   "Setup Main!\n\nPress START to go to play state");

  if (joypad_get_buttons_pressed(JOYPAD_DEFAULT_PORT).start) {
    GameState_Change(GAMESTATE_PLAY);
  }
}

void SetupState_Destroy(void* state) {

}
