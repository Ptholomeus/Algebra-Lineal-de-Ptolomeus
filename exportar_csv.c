#include <stdio.h>
#include "funciones_matrices.h"

void exportar_matriz(Matriz M, const char *nombre){
	
	FILE *f = fopen(nombre, "w");
	if (f == NULL){
		perror("nosepuede");
		return;
	}
	
	for (int i = 0; i < M.fil; i++){
		for (int j = 0; j < M.col; j++){
			fprintf(f, "%8.4f", M.matriz[i][j]);
			if(j < M.col-1)
				fputc(',', f);
		}
		fputc('\n', f);
	}
	fclose(f);
}

// muy bruto
void exportar_solucion(Matriz M, const char *nombre){
	
	FILE *f = fopen(nombre, "w");
	if (f == NULL){
		perror("nosepuede");
		return;
	}
	
	for (int i = 0; i < M.fil; i++){
		for (int j = 0; j < M.col; j++){
			fprintf(f, "%d, %8.4f", i, M.matriz[i][j]);
		}
		fputc('\n', f);
	}
	fclose(f);
}