#include <stdio.h>
#include <stdlib.h>
#include "procesador.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Faltan argumentos. Uso: %s <archivo_instrucciones> <archivo_estado>\n", argv[0]);
        exit(1);
    }

    // Abre el archivo de instrucciones en modo lectura
    FILE *file = fopen("archivo.txt", "r");
    if (file == NULL) {
        printf("No puedes abrir el archivo:\n");
        return -1;
    }
    fclose(file); // Cerramos el archivo ya que `load_program` también lo abrirá

    // Inicializa el procesador
    Processor cpu; // Almacena los registros, memoria y banderas
    init_processor(&cpu);
    load_program(&cpu, "archivo.txt"); // Carga el programa en la memoria);

    // Bucle para ejecutar la serie de instrucciones
    while (cpu.PC < MAX_INSTRUCTIONS) {
        Instruction *instr = &cpu.code_memory[cpu.PC];
        // Verifica si la instrucción está vacía (indicando el final del programa)
        if (instr->inst[0] == '\0') {
            break;
        }
        alu_and_control_unity(&cpu);    // Ejecuta la instrucción en el contador del programa
        print(&cpu);                     // Imprime el estado de las banderas y registros
        fprint(&cpu);                    // Guarda el estado en el archivo de salida
    }

    printf("Ejecución completada.\n");
    return 0;
}

