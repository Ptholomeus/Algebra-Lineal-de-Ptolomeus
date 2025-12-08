#include <stdlib.h>
#include <stdio.h>
#include "funciones_matrices.h"
#include "testear.h"

void test_matrices(){
		
	int fil = 6;
	int col = 6;
	
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
	//double det = determinante_2(&M_menor);
	
	double det = determinante_2(&M);
	
	printf(" El determinante es %f.\n", det);
	
	
	// Creo inversa, pruebo inversa
	
	Matriz M_inv;
	M_inv.fil = fil;
	M_inv.col = col;
	
	M_inv = crear_inversa(&M);
	
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

// Para probar operaciones elementales por filas 
void test_matrices_2(){
	
	/*
		- Crear matriz con valores dados
		- Crear una copia que va a guardar los cambios
		- Mostrar ambas
	*/
	
	int fil;
	int col;
	
	system("cls"); // A Brian y a Dennis no les gusta.
	printf("Ingrese dimensiones \"m n\" de matriz m x n.\n");
	scanf("%d %d", &fil, &col);
	
	
	// Creo una matriz para probar
	Matriz M, M_copia;
	M.fil = fil;
	M.col = col;	

	M = crear_matriz(M.fil, M.col);
	iniciar_matriz_rand(M);
	
	M_copia = copiar_matriz(M);
		
	// hacer operaciones por fila
	int opt;
	int a, b;
	double k;
	
	// Para eliminación Gaussiana
	Vector_N operaciones = {NULL, 0};
	
	// Para test de inversas 
	Matriz M_inversa, test;
	
	
	bool salir = false;
	while(!salir){
		
		system("cls"); // A Brian y a Dennis no les gusta.
		// elegir operación
		
		printf("Matriz %d x %d \n\n", fil, col);
		imprimir_matriz(M);
		imprimir_matriz(M_copia);
		printf("\n");
		
		printf("1 Fil_a x k -> Fil_b \n");
		printf("2 Permutar Fil_a <-> Fil_b \n");
		printf("3 Fil_a x k -> a \n");
		printf("4 Normalizar Fil_a \n");
		printf("5 Eliminacion Gaussiana\n");
		printf("6 Test de inversa\n");
		printf("0 Salir \n");
		
		printf("Elegir: \n");
		fflush(stdout);
		scanf("%d", &opt);		
		
		switch (opt){
			case 1:
				printf("a k b : a*k -> b \n");
				fflush(stdout);
				scanf("%d %lf %d", &a, &k, &b);
				op_sumar_fila(&M_copia, a, k, b);
				imprimir_matriz(M_copia);
				break;
			
			case 2:
				printf("a b : a <-> b \n");
				fflush(stdout);
				scanf("%d %d", &a, &b);
				op_permutar_fila(&M_copia, a, b);
				imprimir_matriz(M_copia);
				break;
			
			case 3:
				printf("a k : a*k -> a \n");
				fflush(stdout);
				scanf("%d %lf", &a, &k);
				op_fila_multiplicar(&M_copia, a, k);
				imprimir_matriz(M_copia);
				break;
			
			case 4:
				printf("a b: a* 1/M[a][b] -> a \n");
				fflush(stdout);
				scanf("%d %d", &a, &b);
				op_normalizar_fila(&M_copia, a, b);
				imprimir_matriz(M_copia);
				break;
			
			case 5 :
				fflush(stdout);
				triangular_matriz (&M_copia, &operaciones);
				imprimir_matriz(M_copia);
				imprimir_vector_N(&operaciones);
				free(operaciones.vector);
				break;
				
			case 6 :
				fflush(stdout);
				M_inversa = crear_inversa(&M);
				test = crear_mult_matriz(M, M_inversa);
				printf("La inversa es: \n");
				imprimir_matriz(M_inversa);
				printf("M * M^-1: \n");
				imprimir_matriz(test);				
				
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
	
	destruir_matriz(&M_inversa);
	destruir_matriz(&test);
	destruir_matriz(&M);
	destruir_matriz(&M_copia);
	
}