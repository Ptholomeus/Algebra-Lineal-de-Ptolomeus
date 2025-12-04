/*
	p66 del pdf
	Sea el dominio L. Luego 0 <= x <= L.
	L se divide en M regiones iguales, de ancho Dx = L/M.
	Se tienen entonces M+1 nodos, de i=0 a i=M.
	
	La formula discretizada es T_i-1 - 2*T_i + T_i+1 + (1/k)*Dx*g_i = 0.
	
	Si T_0 = 300, T_M = 400, la formula es valida para i entre 1 y M-1.
	
	usar k = 1.0 y g = 0.
	
	Se busca un vector v solucion (T_0, T_1, ···, T_M).
	Este vector se sabe que es (300, T_1, ···, 400).
	
	Cada T_i conseguido con la fórmula tiene un coeficiente. los coeficientes
	de T_0 y T_M son 1.0. Se tiene entonces una matriz A de coeficientes.
	
	Cada fila de la matriz corresponde a un i, entonces hay tantas filas como i's.
	Cada colunba de la matriz corresponde a un T_i. Entonces hay tantas columnas
	como i's.
	La matriz es cuadrada. dim (M+1)x(M+1)
	
	Este problema es de la forma Av = b, donde b es un vector constante.
	La matriz A se construye con los coeficientes de T_i's.

*/

#include "funciones_matrices.h"

// matriz "hardcoded"
Matriz crear_matriz_coefs_1Dsteadystate (double L, int M){
	
	double Dx = L / (double) M;
	
	Matriz coefs;
	coefs = crear_matriz(M+1, M+1);
	//iniciar_matriz_cero (coefs);
	
	coefs.matriz[0][0] = 1;
	coefs.matriz[M][M] = 1;
	
	for (int i = 1; i < M; i++){
		coefs.matriz[i][i-1] =  1;
		coefs.matriz[i][i+0] = -2;
		coefs.matriz[i][i+1] =  1;
	}
		
	return coefs;
	
}

Matriz crear_matriz_const_1Dsteadystate (int M){
	
	Matriz constante;
	constante = crear_matriz(M+1, 1);
	//iniciar_matriz_cero (constante);
	
	constante.matriz[0][0] = 300; // T_0
	constante.matriz[M][0] = 400; // T_M
	
	return constante;
	
}