#include <stdlib.h>
#include <stdio.h>
#include "funciones_matrices.h"
#include "testear.h"

void test_matrices(){
		
	int fil = 3;
	int col = 3;
	
	// Creo una matriz para probar
	Matriz M;
	M.fil = fil;
	M.col = col;	

	M = crear_matriz(M.fil, M.col);
	
	iniciar_matriz_rand(M);
	imprimir_matriz(M);

	// Creo una menor, para probar
	Matriz M_menor;
			
	M_menor = crear_submatriz(M, 2, 3);
	imprimir_matriz(M_menor);
	
	// pruebo el determinante 
	double det = determinante_bruto(M_menor);
	printf(" El determinante es %f.\n", det);
	
	
	// Creo inversa, pruebo inversa
	
	Matriz M_inv;
	M_inv.fil = fil;
	M_inv.col = col;
	
	M_inv = crear_inversa(M);
	
	imprimir_matriz(M_inv);
	
	// Pruebo inversa, creo nueva
	
	Matriz probar;
	probar = crear_mult_matriz(M, M_inv);
	
	imprimir_matriz(probar);
	
	
	
	// detruyo todo lo creado
	destruir_matriz(M);
	destruir_matriz(M_menor);
	destruir_matriz(M_inv);
	destruir_matriz(probar);
	
}

void test_matrices_1(){
	int fil = 5;
	int col = 1;
	
	// Creo una matriz para probar
	Matriz M;
	M.fil = fil;
	M.col = col;	

	M = crear_matriz(M.fil, M.col);
	
	iniciar_matriz_rand(M);
	imprimir_matriz(M);
}