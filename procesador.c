#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "procesador.h"
void init_processor (Proccesor *cpu){
  memset(cpu -> memory, 0, 256); // la -> es para los campos de apuntador *nombre de la estructura
  memset(cpu -> registers, 0, 2);
  memset(cpu -> flags, 0, 2);
  //memset(cpu -> PC, 0, 1);
  cpu -> PC = 0;
}
void load_program (Proccesor *cpu, const char *main){
  FILE *fp = fopen(main, "r");
  if(fp == NULL){
    printf("No tienes derecho para abrir el archivo\n");
  }
  char line[256]; //char c;
  //while 
  int i = 0;
  while{fgets(line, 256, fp) != NULL
    sscanf(line, "%s %c %d", cpu -> code_memory[i].inst, &cpu -> code_memory[i].op1, &cpu -> code_memory[i].op2);
    i++;
  }
}
void update_flags (Proccesor *cpu, int result);
void alu_and_control_unity (Proccesor *cpu);
void print( Proccesor *cpu) ;
void fprint( Proccesor *cpu) ;
