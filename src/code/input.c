#include "joypad.h"
#include <input.h>

void Input_Update(Input* input) {
  joypad_inputs_t i = joypad_get_inputs(JOYPAD_PORT_1);
}
