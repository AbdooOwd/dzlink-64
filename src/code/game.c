#include <lib/types.h>
#include <fonts.h>
#include "dragonfs.h"
#include "globals.h"
#include "joypad.h"
#include <display.h>
#include <graphics.h>
#include "rdpq.h"
#include "rdpq_attach.h"
#include "rdpq_font.h"
#include "rdpq_text.h"
#include <n64sys.h>
#include <game.h>
#include <debug.h>

#include <states/setup_state.h>
#include <states/dev_state.h>
#include <states/play_state.h>

// NOTE: Imagine this being like the super master
// of game states. This is the pointer that shall
// decide the fate of the game-state system
// and the running game-state.
GameState gMasterState;

void Game_Entry() {
  void* substate; // void* cuz states can be any struct

  // @NOTE: by default we'll start with the setup-state

  Game_Init();

  // this initializes the master state (duh)
  GameState_InitMaster();
 
  // loop over the queued states
  while (!gMasterState.exit) {
    gMasterState.stateInfo = GameState_GetInfo(gMasterState.stateId);

    substate = malloc_uncached(gMasterState.stateInfo.instanceSize);
    assertf(substate != NULL, "Couldn't allocate for state ID: %i", gMasterState.stateId);

    // initialize state
    gMasterState.stateInfo.init(substate);

    // handle the state's loop (this is technically the game-loop)
    while (!gMasterState.shouldSwitch) {
      // @NOTE: looks like a display MUST be attached to the rdp every frame...
      rdpq_attach(display_get(), display_get_zbuf());
      gMasterState.input = joypad_get_inputs(JOYPAD_DEFAULT_PORT);

      GameState_Update(substate);

      // @TODO: should these funcs be here?
      joypad_poll();
      rdpq_detach_show();
    }

    GameState_Destroy(substate);
    gMasterState.shouldSwitch = false; // aight dawg we already switched

    free_uncached(substate);
  }
  Game_Destroy();
}


void Game_Init() {
  asset_init_compression(2);
  dfs_init(DFS_DEFAULT_LOCATION);
  display_init(
    RESOLUTION_320x240,
    DEPTH_16_BPP,
    FB_COUNT,
    GAMMA_NONE,
    FILTERS_RESAMPLE);
  rdpq_init();
  joypad_init();

  // initialize font
  rdpq_font_t* lexis_font = rdpq_font_load("rom:/lexis.font64");
  rdpq_text_register_font(FONTID_LEXIS, lexis_font);
  rdpq_text_register_font(FONTID_DBG_MONO, rdpq_font_load_builtin(FONT_BUILTIN_DEBUG_MONO));
  rdpq_text_register_font(FONTID_DBG_VAR, rdpq_font_load_builtin(FONT_BUILTIN_DEBUG_VAR));
}

// @TODO: I think I should separate drawing from updating
void Game_Draw() {

}

void Game_Destroy() {
  joypad_close();
  rdpq_close();
  display_close();
}


/* ----- GAMESTATE PART ----- */

/*
 * You could call this func a function called once to prepare
 * the game for handling all states
 * */
inline void GameState_InitMaster() {
  // state info values will be NULL and such so the state info
  // logic is handled by the main loop
  gMasterState.stateInfo = (GameStateInfo) {
    .init = NULL,
    .main = NULL,
    .destroy = NULL,
    .instanceSize = 0,
    .id = GAMESTATE_NONE
  };
  gMasterState.exit = false;
  gMasterState.frames = 0;
  gMasterState.shouldSwitch = false;
  gMasterState.stateId = GAMESTATE_SETUP;
}

void GameState_Update(void* state) {
  gMasterState.frameIdx = gMasterState.frames % FB_COUNT;

  gMasterState.stateInfo.main(state);

  gMasterState.frames++;
}

void GameState_Destroy(void* state) {
  gMasterState.stateInfo.destroy(state);
}

GameStateInfo GameState_GetInfo(u8 stateId) {
  GameStateInfo stateInfo;

  // @NOTE: This func's approach probably adds more
  //  CPU instructions and such, but it happens when
  //  loading a new state, which I don't think will
  //  happen so often

  #define DEFINE_GAMESTATE(typeName, enumId)    \
    case enumId:                                \
      stateInfo.id = enumId;                    \
      stateInfo.instanceSize = sizeof(typeName##State); \
      stateInfo.init = typeName##State_Init;    \
      stateInfo.main = typeName##State_Main;    \
      stateInfo.destroy = typeName##State_Destroy; \
      break;

  switch (stateId) {
    #include <tables/gamestate_table.h>
    default:
      assertf(false, "Unknown state ID: %i", stateId);
  }

  #undef DEFINE_GAMESTATE

  return stateInfo;
}

void GameState_Change(u8 stateId) {
  gMasterState.stateId = stateId;
  gMasterState.shouldSwitch = true;
}
