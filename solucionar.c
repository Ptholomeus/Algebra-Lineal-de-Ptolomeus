#include <stdlib.h>
#include <stdio.h>
#include "funciones_matrices.h"
#include "funciones_fisica_calor.h"
#include "testear.h"
#include "solucionar.h"
#include "exportar_csv.h"

void resolver() {
		
	double L = 5.0;
	int M;
	double k = 1.0;
	
	printf("Introducir tamano de discretizacion. \nM = ");
	scanf("%d", &M);
	
	// Defino matrices
	Matriz solucion;
	Matriz coeficientes;
	Matriz inv_coefs;
	Matriz constantes;
	
	Matriz test;
	Vector_N vector;
	
	Matriz temp_1;
	
	// crear matriz de soluciones	
		// 13.12.25 Despues de cambiar la definicion de mult escalar matriz, no necesito crearla.
	//solucion = crear_matriz(M+1, 1); // vector columna
	
	// crear matriz de coeficientes
	coeficientes = crear_matriz_coefs_1Dsteadystate(L, M);
	
	// conseguir inversa de la matriz de coeficientes
	inv_coefs = crear_inversa(&coeficientes);
	
	// crear matriz constante
	constantes = crear_matriz_const_1Dsteadystate(M);
	
	// solucionar
	imprimir_matriz(coeficientes);
	imprimir_matriz(constantes);
	

	/*
	//imprimir y probar la inversa
	test = copiar_matriz(coeficientes);
	
	printf("Triangular coefs: \n");
	triangular_matriz(&test, &vector);
	imprimir_matriz(test);
	
	printf("Inversa\n");
	imprimir_matriz(inv_coefs);
	
	printf("Inversa de coeficientes: \n");
	imprimir_matriz(inv_coefs);
	
	printf("Producto de coeficientes e inversa: \n");
	test = crear_mult_matriz(inv_coefs, coeficientes);
	imprimir_matriz(test);
	*/
	
	// crear matriz temporal, que almacena (1/k)*A^-1
	// 13.12.25 Acá también podría haber problema, por eso cambio la def de esc mult matr
	temp_1 = crear_escalar_mult_matriz( (1/k) , inv_coefs );
	
	// solucion es (1/k)*A^-1*b
	solucion = crear_mult_matriz(temp_1, constantes);
	
	// solucion horizontal
	Matriz sol_h;
	sol_h = crear_traspuesta(solucion);
	
	imprimir_matriz(sol_h);
	
	exportar_solucion(solucion, "texto.csv");
	
	getchar();
	getchar();
	
	// destruirrr
	destruir_matriz(&solucion);
	destruir_matriz(&coeficientes);
	destruir_matriz(&constantes);
	destruir_matriz(&inv_coefs);
	destruir_matriz(&temp_1);
	destruir_matriz(&sol_h);
	// destruir_matriz(&test);
	// free(vector.vector);
	
	return;
	
}