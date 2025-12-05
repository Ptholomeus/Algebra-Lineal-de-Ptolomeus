#include <stdlib.h>
#include <stdio.h>
#include "funciones_matrices.h"
#include "funciones_fisica_calor.h"
#include "testear.h"
#include "solucionar.h"
#include "exportar_csv.h"

void resolver() {
		
	double L = 5.0;
	int M = 10;
	double k = 1.0;
	
	// crear matriz de soluciones
	Matriz solucion;
	solucion = crear_matriz(M+1, 1); // vector columna
	//iniciar_matriz_cero(solucion);
	
	// crear matriz de coeficientes
	Matriz coeficientes;
	coeficientes = crear_matriz_coefs_1Dsteadystate(L, M);
	
	// crear matriz constante
	Matriz constantes;
	constantes = crear_matriz_const_1Dsteadystate(M);
	
	// solucionar
	imprimir_matriz(coeficientes);
	imprimir_matriz(constantes);
	
	// conseguir inversa de la matriz de coeficientes
	Matriz inv_coefs = crear_inversa(coeficientes);
	
	// crear matriz temporal, que almacena (1/k)*A^-1
	Matriz temp_1;
	temp_1 = crear_matriz(coeficientes.fil, coeficientes.col);
	temp_1 = escalar_mult_matriz( (1/k) , inv_coefs );
	
	// solucion es (1/k)*A^-1*b
	solucion = crear_mult_matriz(temp_1, constantes);
	
	// solucion horizontal
	Matriz sol_h;
	sol_h = crear_traspuesta(solucion);
	
	imprimir_matriz(sol_h);
	
	exportar_solucion(solucion, "texto.csv");
	
	// destruirrr
	destruir_matriz(solucion);
	destruir_matriz(coeficientes);
	destruir_matriz(constantes);
	destruir_matriz(inv_coefs);
	destruir_matriz(temp_1);
	destruir_matriz(sol_h);
	
}