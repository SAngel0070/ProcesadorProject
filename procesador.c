#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "procesador.h"

// Inicializa el procesador con memoria y registros en cero
void init_processor(Processor *cpu) {
    memset(cpu->memory, 0, MEM_SIZE * sizeof(int));
    memset(cpu->registers, 0, NUM_REGISTERS * sizeof(int));
    memset(cpu->flags, 0, NUM_FLAGS * sizeof(bool));
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
    if (cpu->PC < 0 || cpu->PC >= MAX_INSTRUCTIONS) {
        printf("Error: PC fuera de límites\n");
        return;
    }

    Instruction *instr = &cpu->code_memory[cpu->PC];
    if (instr->op1 < 'A' || instr->op1 >= 'A' + NUM_REGISTERS) {
        printf("Registro inválido: %c\n", instr->op1);
        return;
    }

    int op1_val = cpu->registers[instr->op1 - 'A'];
    int op2_val = instr->op2;
    int result = 0;

    if (strcmp(instr->inst, "ADD") == 0) {
        result = op1_val + op2_val;
        cpu->registers[instr->op1 - 'A'] = result;
    } else if (strcmp(instr->inst, "SUB") == 0) {
        result = op1_val - op2_val;
        cpu->registers[instr->op1 - 'A'] = result;
    } else if (strcmp(instr->inst, "MOV") == 0) {
        cpu->registers[instr->op1 - 'A'] = op2_val;
    } else {
        printf("Instrucción desconocida: %s\n", instr->inst);
    }

    update_flags(cpu, result);
    cpu->PC++;
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
