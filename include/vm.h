#ifndef VM_H__
#define VM_H__

#include <stdint.h>

typedef struct object_t {
  uint8_t type;
  union {
    int8_t i8;
    uint8_t u8;
    int32_t i32;
    uint32_t u32;
    void* ptr;
  };

} Object;

typedef struct stack_t {
  uint32_t size;
  uint32_t top;
  Object* stack;
} Stack;


/* define instruction prototype */
typedef uint8_t* (*instruction) (uint8_t*, Stack*);

enum INSTRUCTION_TYPE
  {
   TYPE_HALT = 0,
   TYPE_NOP,
   TYPE_PUSH_CHAR,
   TYPE_EMIT
  };

/* new a stack with size */
extern Stack* stack_new (uint32_t size);

/* push an element */
extern void stack_push (Stack* stack, Object obj);

/* pop an element */
extern Object stack_pop (Stack* stack);

/* peek a value */
extern Object stack_peek (Stack* stack);

/* load file with file name */
extern uint8_t* load_file (char* filename);


extern  enum INSTRUCTION_TYPE resolve_code (uint8_t code);

/* operations handler */

/* default operation */
extern uint8_t* op_nop (uint8_t* ip, Stack* stack);

/* halt */
extern uint8_t* op_halt (uint8_t* ip, Stack* stack);

/* push char to stack */
extern uint8_t* op_push_char (uint8_t* ip, Stack* stack);

/* pop and print char to stdout */
extern uint8_t* op_emit (uint8_t* ip, Stack* stack);

#endif // VM_H__
