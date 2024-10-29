#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "procesador.h"

// Inicializa el procesador con memoria y registros en cero
void init_processor(Processor *cpu) {
    memset(cpu->memory, 0);
    memset(cpu->registers, 0);
    memset(cpu->flags, 0);
    cpu->PC = 0;
}

// Carga un programa desde el archivo main.c en la memoria de instrucciones
void load_program(Processor *cpu, const char *filename) {
    FILE *fp = fopen("main.c", "r"); // Cambio de archivo.txt a main.c
    if (fp == NULL) {
        printf("No se puede abrir el archivo main.c\n");
        return;
    }
    char line[256];
    int i = 0;
    while (fgets(line, sizeof(line), fp) != NULL && i < MAX_INSTRUCTIONS) {
        sscanf(line, "%5s %c %d", cpu->code_memory[i].inst, &cpu->code_memory[i].op1, &cpu->code_memory[i].op2);
        i++;
    }
    fclose(fp);
}

// Actualiza los indicadores de bandera según el resultado de una operación
void update_flags(Processor *cpu, int result) {
    cpu->flags[ZF] = (result == 0);  // Bandera de cero
    cpu->flags[NF] = (result < 0);   // Bandera de negativo
}

// Ejecuta la unidad de control y la ALU
void alu_and_control_unity(Processor *cpu) {
  Instruction *instr = &cpu->code_memory[cpu->PC];
  int op1_val = cpu->registers[instr->op1 - 'A'];
  int op2_val = (instr->op2 < MEM_SIZE) ? cpu->memory[instr->op2] : instr->op2;
  int result = 0;

  if (strcmp(instr->inst, "MOV") == 0) {
    if (instr->op2 < MEM_SIZE)  // Carga de memoria a registro
      cpu->registers[instr->op1 - 'A'] = cpu->memory[instr->op2];
    else  // Carga de inmediato a registro
      cpu->registers[instr->op1 - 'A'] = instr->op2;
  } else if (strcmp(instr->inst, "ADD") == 0) {
    result = op1_val + op2_val;
    cpu->registers[instr->op1 - 'A'] = result;
  } else if (strcmp(instr->inst, "SUB") == 0) {
    result = op1_val - op2_val;
    cpu->registers[instr->op1 - 'A'] = result;
  } else if (strcmp(instr->inst, "CMP") == 0) {
    result = op1_val - op2_val;
    update_flags(cpu, result);
  } else if (strcmp(instr->inst, "STORE") == 0) {
    if (instr->op2 < MEM_SIZE)
      cpu->memory[instr->op2] = op1_val;
    else
      printf("Error: Dirección de memoria inválida para STORE\n");
  } else if (strcmp(instr->inst, "LOAD") == 0) {
    if (instr->op2 < MEM_SIZE)
      cpu->registers[instr->op1 - 'A'] = cpu->memory[instr->op2];
    else
      printf("Error: Dirección de memoria inválida para LOAD\n");
  } else if (strcmp(instr->inst, "JMP") == 0) {
    if (instr->op2 < MAX_INSTRUCTIONS)
      cpu->PC = instr->op2;
    else
      printf("Error: Dirección de salto inválida para JMP\n");
    return; // No incrementar PC después de JMP
  } else if (strcmp(instr->inst, "JZ") == 0) {
    if (cpu->flags[ZF] && instr->op2 < MAX_INSTRUCTIONS)
      cpu->PC = instr->op2;
    else
      cpu->PC++;
    return;
  } else if (strcmp(instr->inst, "JN") == 0) {
    if (cpu->flags[NF] && instr->op2 < MAX_INSTRUCTIONS)
      cpu->PC = instr->op2;
    else
      cpu->PC++;
    return;
  } else {
    printf("Instrucción desconocida: %s\n", instr->inst);
  }

  update_flags(cpu, result);
  cpu->PC++;  // Incrementa PC si no hay salto
}

// Imprime el estado del procesador en pantalla
void print(Processor *cpu) {
    printf("PC: %d\n", cpu->PC);
    printf("Registros:\n");
    for (int i = 0; i < NUM_REGISTERS; i++) {
        printf("R%d: %d\n", i, cpu->registers[i]);
    }
    printf("Banderas: ZF = %d, NF = %d\n", cpu->flags[ZF], cpu->flags[NF]);
}

// Guarda el estado del procesador en main.c
void fprint(Processor *cpu) {
    FILE *fp = fopen("main.c", "w");
    if (fp == NULL) {
        printf("No se puede abrir el archivo main.c para escribir\n");
        return;
    }
    fprintf(fp, "PC: %d\n", cpu->PC);
    fprintf(fp, "Registros:\n");
    for (int i = 0; i < NUM_REGISTERS; i++) {
        fprintf(fp, "R%d: %d\n", i, cpu->registers[i]);
    }
    fprintf(fp, "Banderas: ZF = %d, NF = %d\n", cpu->flags[ZF], cpu->flags[NF]);
    fclose(fp);
}
