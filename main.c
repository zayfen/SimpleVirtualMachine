#include <stdio.h>
#include "include/vm.h"


int main (int argc, char* argv[]) {

  instruction ins[256];         /* each instruction 8bit, so 256 instructions total */

  /* init instructs */
  for (int i = 0; i < 256; i++) {
    ins[i] = op_nop;
  }

  /* register instructs handlers */
  ins[TYPE_NOP] = op_nop;
  ins[TYPE_HALT] = op_halt;
  ins[TYPE_PUSH_CHAR] = op_push_char;
  ins[TYPE_EMIT] = op_emit;

  /* environment */
  uint8_t* code = load_file(argv[1]);
  if (code == NULL) {
    return -100;                /* load file failed */
  }

  uint8_t* ip = code;
  Stack* data = stack_new(1024); /* allocate 1MB memory */

  /* execute all instructions */
  while (resolve_code(*ip) != TYPE_HALT) {
    ip = ins[resolve_code(*ip)](ip, data);
  }

  return 0;
}
