// (compilar) gcc main.c funciones_matrices.c funciones_fisica_calor.c testear.c solucionar.c exportar_csv.c -o programa

#include <stdlib.h>
#include <stdio.h>
#include "funciones_matrices.h"
#include "funciones_fisica_calor.h"
#include "testear.h"
#include "solucionar.h"
#include "exportar_csv.h"

Matriz crear_matriz(int fil, int col);
void destruir_matriz(Matriz A);
Matriz crear_submatriz (Matriz A, int fil_quitar, int col);
void imprimir_matriz (Matriz A);
void iniciar_matriz_cero (Matriz A);
void iniciar_matriz_rand (Matriz A);
Matriz crear_traspuesta(Matriz M);
Matriz escalar_mult_matriz (double a, Matriz M);
Matriz crear_cofactor (Matriz M, int fil_cof, int col_cof);
double determinante_bruto (Matriz M);
Matriz crear_adjunta (Matriz M);
Matriz crear_inversa (Matriz M);
double mult_fil_col (Matriz A, int A_fil, Matriz B, int B_col);
Matriz crear_mult_matriz (Matriz A, Matriz B);
void iniciar_matriz_identidad (Matriz M);

Matriz crear_matriz_coefs_1Dsteadystate (double L, int M);
Matriz crear_matriz_const_1Dsteadystate (int M);

int main(){
	
	//test_matrices();
	//test_matrices_1();
	resolver();

	return 0;
	
}