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
	destruir_matriz(&M);
	destruir_matriz(&M_menor);
	destruir_matriz(&M_inv);
	destruir_matriz(&probar);
	
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

void test_matrices_2(){
	
	/*
		- Crear matriz con valores dados
		- Crear una copia que va a guardar los cambios
		- Mostrar ambas
	*/
	
	int fil = 4;
	int col = 4;
	
	// Creo una matriz para probar
	Matriz M, M_copia;
	M.fil = fil;
	M.col = col;	

	M = crear_matriz(M.fil, M.col);
	iniciar_matriz_rand(M);
	
	M_copia = crear_copia_matriz(M);
		
	// hacer operaciones por fila
	int opt;
	int a, b;
	double k;
	
	bool salir = false;
	while(!salir){
		
		system("cls"); // A Brian y a Dennis no les gusta.
		// elegir operación
		
		imprimir_matriz(M);
		imprimir_matriz(M_copia);
		
		printf("1 Fila a por k en fila b \n");
		printf("2 Permutar a y b \n");
		printf("3 Fila a por k \n");
		printf("0 Salir \n");
		
		printf("Elegir: \n");
		fflush(stdout);
		scanf("%d", &opt);		
		
		switch (opt){
			case 1:
				printf("a k b, a*k -> b: \n");
				fflush(stdout);
				scanf("%d %lf %d", &a, &k, &b);
				M_copia = op_sumar_fila(M_copia, a, k, b);
				imprimir_matriz(M_copia);
				break;
			
			case 2:
				printf("a <-> b: \n");
				fflush(stdout);
				scanf("%d %d", &a, &b);
				M_copia = op_permutar_fila(M_copia, a, b);
				imprimir_matriz(M_copia);
				break;
			
			case 3:
				printf("a*k a: \n");
				fflush(stdout);
				scanf("%d %lf", &a, &k);
				M_copia = op_fila_multiplicar(M_copia, a, k);
				imprimir_matriz(M_copia);
				break;
				
			case 0:
				salir = true;
				break;
				
			default:
				//tamal
				break;
		}
		
		// Averiguar qué pasa acá
		getchar();
		getchar();
		
	}
	
	destruir_matriz(&M);
	destruir_matriz(&M_copia);
	
}