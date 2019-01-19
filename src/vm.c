#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "../include/vm.h"

static inline uint32_t min (uint32_t a, uint32_t b) {
  return a < b ? a : b;
}

/* print usage manual to stdout */
static void usage () {
  fprintf(stdout, "Usage:\n SimpleVirtualMachine filename.vm \n example: ./SimpleVirtualMachine test.vm\n");
}


Stack* stack_new (uint32_t size) {
  Stack* stack = (Stack*)malloc(sizeof(Stack));
  stack->stack = (Object*)malloc(size * sizeof(Object));
  stack->size = size;
  stack->top = 0;
  return stack;
}

/**
 * to check whether stack is full
 */
static int stack_full (Stack* stack) {
  return stack->top >= stack->size ? 1 : 0;
}

/**
 * to check whether stack is empty
 */
static int stack_empty (Stack* stack) {
  return stack->top == 0 ? 1 : 0;
}


void stack_push (Stack* stack, Object obj) {
  if (stack_full(stack)) {
    perror("stack is full");
    return;
  }

  stack->stack[(stack->top)++] = obj;
}

Object stack_pop (Stack* stack) {
  if (stack_empty(stack)) {
    perror("stack is empty");
    exit(-1);
  }

  return stack->stack[--stack->top];
}


Object stack_peek (Stack* stack) {
  if (stack_empty(stack)) {

  }

  return stack->stack[stack->top - 1];
}


uint8_t* load_file (char* filename) {
  FILE* file = NULL;
  uint8_t* code = NULL;
  struct stat statbuf;
  uint32_t file_size = 0;


  if ((file = fopen(filename, "r"))) {
    fstat(fileno(file), &statbuf);
  } else {
    fprintf(stderr, "Can't open %s\n", filename);
    usage();
    return code;
  }

  /* file_size = statbuf.st_size; */
  /* printf("file_size: %d", file_size); */

  code = (uint8_t*) malloc(statbuf.st_size);
  fread((void*)code, 1, statbuf.st_size, file);
  return code;
}


enum INSTRUCTION_TYPE resolve_code (uint8_t code) {
  switch (code) {
  case 'p':
    return TYPE_PUSH_CHAR;

  case 'e':
    return TYPE_EMIT;

  case '\n':
    return TYPE_HALT;

  case ' ':
  case '\t':
    return TYPE_NOP;

  default:
    return TYPE_HALT;
  }
}


uint8_t* op_nop (uint8_t* ip, Stack* stack) {
  return ip + 1;
}

/* op_halt */
uint8_t* op_halt (uint8_t* ip, Stack* stack) {
  exit(0);
}

/* push charater */
uint8_t* op_push_char (uint8_t* ip, Stack* stack) {
  Object object;
  object.type = TYPE_PUSH_CHAR;
  object.u8 = *(ip + 1);
  stack_push(stack, object);
  return ip + 2;
}

/* print charater */
uint8_t* op_emit (uint8_t* ip, Stack* stack) {
  Object object = stack_pop(stack);
  fprintf(stdout, "%c", object.u8);
  return ip + 1;
}
