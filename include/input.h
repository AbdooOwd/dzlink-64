#ifndef INPUT_H
#define INPUT_H

#include "joypad.h"

// @TODO: for now, no custom input type. just libdragon's default
typedef joypad_inputs_t Input;
/*
typedef struct Input {
  joypad_buttons_t cur; // currently held buttons
  joypad_buttons_t press; // pressed once buttons
  joypad_buttons_t rel; // released buttons
} Input; // 6 bytes
*/
#endif
