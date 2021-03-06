/*#include "arena.h"*/
#include "util.h"
/* Códigos das instruções */
typedef enum {
  PUSH,
  POP,
  DUP,
  ADD,
  SUB,
  MUL,
  DIV,
  JMP,
  JIT,
  JIF,
  CALL,
  RET,
  STS,
  RCS,
  EQ,
  GT,
  GE,
  LT,
  LE,
  NE,
  STO,
  RCL,
  END,
  PRN,
  STL,
  RCE,
  ALC,
  FRE,
  ATR
} OpCode;

/* Tipos dos operandos */
typedef enum {
  ACAO,
  BOOL,
  VAR,
  CELL,
  NUM
} Tipo;
/* Operando, agora com o atributo Tipo */
typedef struct {
   Tipo t;
  union {
 	  int n;
 	  int ac;
 	  int v;
    //Celula c;
    //Boolean b;
  }var;
 } OPERANDO;
/*typedef int OPERANDO;*/

/* Instrução */
typedef struct {
  OpCode instr;
  OPERANDO op;
} INSTR;
