#ifndef SETUP_STATE_H
#define SETUP_STATE_H

#include <game.h>

typedef struct SetupState {
} SetupState;

void SetupState_Init(void* state);
void SetupState_Main(void* state);
void SetupState_Destroy(void* state);

#endif
