#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "procesador.h"

// Inicializa el procesador con memoria y registros en cero
void init_processor (Proccesor *cpu){
  memset(cpu->memory, 0, MEM_SIZE * sizeof(int));
  memset(cpu->registers, 0, NUM_REGISTERS * sizeof(int));
  memset(cpu->flags, 0, NUM_FLAGS * sizeof(bool));
  cpu->PC = 0;
}

// Carga un programa desde un archivo de texto en la memoria de instrucciones
void load_program (Proccesor *cpu, const char *main){
  FILE *fp = fopen(main, "r");
  if(fp == NULL){
    printf("No se puede abrir el archivo\n");
    return;
  }
  char line[256];
  int i = 0;
  while(fgets(line, sizeof(line), fp) != NULL && i < MAX_INSTRUCTIONS) {
    sscanf(line, "%5s %c %d", cpu->code_memory[i].inst, &cpu->code_memory[i].op1, &cpu->code_memory[i].op2);
    i++;
  }
  fclose(fp);
}

// Actualiza los indicadores de bandera según el resultado de una operación
void update_flags (Proccesor *cpu, int result) {
  cpu->flags[ZF] = (result == 0);  // Bandera de cero
  cpu->flags[NF] = (result < 0);   // Bandera de negativo
}

// Ejecuta la unidad de control y la ALU
void alu_and_control_unity (Proccesor *cpu) {
  Instruction *instr = &cpu->code_memory[cpu->PC];
  int op1_val = cpu->registers[instr->op1 - 'A'];
  int op2_val = instr->op2;
  int result = 0;

void print( Proccesor *cpu) ;
void fprint( Proccesor *cpu) ;
