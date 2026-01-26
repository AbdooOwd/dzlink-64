#ifndef GAME_H
#define GAME_H

#include <input.h>
#include <lib/types.h>
#include <stdbool.h>

typedef void (*GameStateFunc)(void* state);

typedef struct GameStateInfo {
  u8 id;
  GameStateFunc init;
  GameStateFunc main;
  GameStateFunc destroy;
  u32 instanceSize;
} GameStateInfo;

typedef struct GameState {
  bool shouldSwitch;  // true triggers changing states in the main game loop
  u32 frames; // if the constant FPS is 20, it would take ~7 years to overflow (:
  u8 frameIdx;  // used to draw based on framebuffers count
  bool exit; // if this value is set to true... the game stops...!
  GameStateInfo stateInfo; // kind of like an overlay entry in ZeldaOoT
  u8 stateId; // controls which state the master state should work with
  Input input;
  u8 displaySettings;
} GameState;


#define DEFINE_GAMESTATE(typeName, enumID) enumID,

typedef enum GameStateID {
  GAMESTATE_NONE,
  #include <tables/gamestate_table.h>
  GAMESTATE_ID_MAX
} GameStateID;

#undef DEFINE_GAMESTATE


extern GameState gMasterState;


void Game_Init();
void Game_Entry();
void Game_Destroy();

void GameState_InitMaster();
void GameState_Update(void* state);
void GameState_Destroy(void* state);
GameStateInfo GameState_GetInfo(u8 stateId);
void GameState_Change(u8 stateId);
#endif
