#include <console.h>
#include <libdragon.h>
#include <stdio.h>

int main(void) {
  console_init();
  console_set_render_mode(RENDER_AUTOMATIC);

  puts("Hello, N64!");

  return 0;
}
