#ifndef PROCESADOR_H
#define PROCESADOR_H

#include <stdbool.h>

#define MEM_SIZE 256
#define MAX_INSTRUCTIONS 100
#define NUM_REGISTERS 2
#define NUM_FLAGS 2

// Definimos los índices para las banderas
#define ZF 0
#define NF 1

// Estructura que representa una instrucción
typedef struct {
  char inst[6]; // Nombre de la instrucción, con espacio suficiente para almacenar
  char op1;     // Primer operando, típicamente un registro (e.g., 'A', 'B')
  int op2;      // Segundo operando, típicamente un valor o dirección
} Instruction;

// Estructura que representa el procesador
typedef struct {
  int memory[MEM_SIZE];                      // Memoria de datos
  int registers[NUM_REGISTERS];              // Registros del procesador
  bool flags[NUM_FLAGS];                     // Banderas (ZF y NF)
  int PC;                                    // Contador de programa
  Instruction code_memory[MAX_INSTRUCTIONS]; // Memoria de instrucciones
} Processor;

// Funciones del procesador
void init_processor(Processor *cpu); // Inicializa el procesador
void load_program(Processor *cpu, const char *filename); // Carga un programa en el procesador
void update_flags(Processor *cpu, int result); // Actualiza las banderas en base a un resultado
void alu_and_control_unity(Processor *cpu);         // Ejecuta la unidad de control y ALU
void print(Processor *cpu);  // Imprime el estado del procesador en pantalla
void fprint(Processor *cpu); // Guarda el estado del procesador en un archivo

#endif
