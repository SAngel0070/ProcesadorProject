
#include <stdbool.h>
#define MEM_SIZE 256
//const MEM_SIZE = 256; preprocesador y lenguaje c
#define MAX_INSTRUCTIONS 100
#define NUM_REGISTERS 2
#define NUM_FLAGS 2
// Definimos para las banderas.
#define ZF 0 
#define NF 1

typedef struct{
  char inst[6];
  char op1;
  int op2;
}Instruction;
// Estructura que representa el procesador
typedef struct{// Código de los datos especificados
  int memory[MEM_SIZE];
  int registers[NUM_REGISTERS];
  bool flags[NUM_FLAGS];
  int PC; // Contador de programa.
  Instruction code_memory[MAX_INSTRUCTIONS]; // Memoria de instrucciones.
}Proccesor;
// Funciones del procesador
/**
  * Inicializa el procesador.
  */
void init_processor (Proccesor *cpu);
void load_program (Proccesor *cpu, const char *filename);
void update_flags (Proccesor *cpu, int result);
void alu_and_control_unity (Proccesor *cpu);
void print( Proccesor *cpu) ;
void fprint( Proccesor *cpu) ;
