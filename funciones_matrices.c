#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "funciones_matrices.h"

Matriz crear_matriz(int fil, int col){
	
	/*
	A[2][3] = {
		{1, 2, 3},
		{4, 5, 6}		
	};
	*/
	
	Matriz A;
	
	if (fil <= 0 || col <= 0) {
		
		A.matriz = NULL;
		A.datos  = NULL;
		
		A.fil = 0;
		A.col = 0;
		
		return A;
	} else {
		
		A.fil = fil;
		A.col = col;
		
		A.datos  = malloc(fil * col * sizeof(double) );
		A.matriz = malloc(fil * sizeof(double *) );
	
		for (int idx = 0; idx < fil; idx++)
			A.matriz[idx] = &A.datos[idx * col];
		
		iniciar_matriz_cero (A);
		
		return A;
	}
}

void destruir_matriz(Matriz A){
	
	free(A.matriz);
	free(A.datos);	
	
}

Matriz crear_submatriz (Matriz A, int fil_quitar, int col_quitar){
	
	Matriz A_menor;
	
	if (fil_quitar <= 0 || col_quitar <= 0) {
		
		A_menor.matriz = NULL;
		A_menor.datos  = NULL;
		
		A_menor.fil = 0;
		A_menor.col = 0;
		
		return A_menor;
		
	} else {
		
		// inicializar matriz menor 
		
		A_menor.fil = A.fil-1;
		A_menor.col = A.col-1;
		
		A_menor = crear_matriz(A_menor.fil, A_menor.col);
	
		for (int i_A = 0, i_menor = 0; i_A < A.fil; i_A++){
		
			if (i_A == fil_quitar-1) // "salteo" la fila a quitar
				continue;
			
			for (int j_A = 0, j_menor = 0; j_A < A.col; j_A++){
			
				if (j_A == col_quitar-1) // "salteo" la columna a quitar
					continue;
					
				A_menor.matriz[i_menor][j_menor] = A.matriz[i_A][j_A];
				j_menor++;
			}
			i_menor++;
		}
				
		return A_menor;	

	}

}

void imprimir_matriz (Matriz matriz) {
	
	double **A = matriz.matriz;
	int fil = matriz.fil;
	int col = matriz.col;
	
	// imprimir primer corchete 	
	printf("{ \n");
	for (int i = 0; i < fil-1; i++) // imprimir hasta anteultima fila
	{
		
		// por cada fila, dejar un tab
		printf("\t { ");
		for (int j = 0; j < col-1; j++){
			printf("%8.4f, ", A[i][j]); // imprimir hasta el anteultimo elemento
		}
		printf("%8.4f }, \n", A[i][col-1]); // el ultimo elemento se formatea asi
		
	}
	// imprimir ultima fila 
	printf("\t { ");
	for (int j = 0; j < col-1; j++){
			printf("%8.4f, ", A[fil-1][j]);
	}
	printf("%8.4f }\n", A[fil-1][col-1]); // imprimir sin coma
	
	// imprimir último cero
	printf("}\n");
	
}

void iniciar_matriz_cero (Matriz A) {
	for (int i = 0; i < A.fil; i++){
		for (int j = 0; j < A.col; j++){
			A.matriz[i][j] = 0;
		}			
	}
}

void iniciar_matriz_rand (Matriz A) {
	srand(time(NULL));
	for (int i = 0; i < A.fil; i++){
		for (int j = 0; j < A.col; j++){
			A.matriz[i][j] = (rand() % (9 + 1)) 
						   + (rand() / (double) RAND_MAX);
		}			
	}
}

Matriz crear_traspuesta (Matriz M){
	
	Matriz M_t;
	M_t = crear_matriz(M.col, M.fil);
	
	for (int i = 0; i < M_t.fil; i++){
		for (int j = 0; j < M_t.col; j++){
			M_t.matriz[i][j] = M.matriz[j][i];
		}
	}
	
	return M_t;
	
}

// no crea, solo retorna matriz
Matriz escalar_mult_matriz (double a, Matriz M) {
	
	for (int i = 0; i < M.fil; i++){
		for (int j = 0; j < M.col; j++){
			M.matriz[i][j] = a * M.matriz[i][j];
		}
	}
	
	return M;
	
}

double cofactor (Matriz M, int fil_cof, int col_cof){
	
	double cof;
	Matriz temp;
	
	double signo;
	signo = (fil_cof + col_cof) % 2 == 0 ? 1.0 : -1.0;
	
	temp = crear_submatriz (M, fil_cof, col_cof);
	cof = signo * determinante_bruto(temp);
	
	destruir_matriz(temp);
	
	return cof;
	
}

double determinante_bruto (Matriz M){
	
	double det = 0, signo;
	int n = M.fil;
	
	Matriz M_det;
	
	if (n == 2) {
		det = M.matriz[0][0] * M.matriz[1][1] - M.matriz[0][1] * M.matriz[1][0];
		return det;
	} else {
		for (int j = 0; j < n; j++){
			signo = (j+1)%2 == 1 ? 1.0 : -1.0;
			M_det = crear_submatriz(M, 1, j+1);
			det += signo * M.matriz[0][j] * determinante_bruto(M_det);
			destruir_matriz(M_det);
		}
		return det;
	}
}

Matriz crear_adjunta (Matriz M){
	
	Matriz temp_1, temp_2;
	temp_1 = crear_matriz(M.fil, M.col);
	
	for (int i = 0; i < M.fil; i++){
		for (int j = 0; j < M.col; j++){
			temp_1.matriz[i][j] = cofactor(M, i+1, j+1);
		}
	}
	
	temp_2 = crear_traspuesta(temp_1);
	
	destruir_matriz(temp_1);
	
	return temp_2;
	
}

Matriz crear_inversa (Matriz M){
	
	Matriz temp;
	
	double det;
	
	// verificar que no sea cero
	det = determinante_bruto (M);
	
	temp = crear_adjunta(M);
	
	temp = escalar_mult_matriz ( 1 / det, temp );
	
	return temp;
	
}

double mult_fil_col (Matriz A, int A_fil, Matriz B, int B_col){
	
	double c = 0;
	
	for (int i = 0; i < A.col; i++ ){
		c += A.matriz[A_fil][i] * B.matriz[i][B_col];
	}
	
	return c;
	
}

Matriz crear_mult_matriz (Matriz A, Matriz B){
	
	// verificar que se cumplan las condiciones
	Matriz C;
	C = crear_matriz(A.fil, B.col);
	
	for (int i = 0; i < C.fil; i++ ){
		for (int j = 0; j < C.col; j++){
			C.matriz[i][j] = mult_fil_col(A, i, B, j);
		}
	}
	
	return C;
	
}

void iniciar_matriz_identidad (Matriz M){
	
	//comprobar que M es cuadrada
	iniciar_matriz_cero(M);
	for(int i = 0; i<M.fil; i++)
		M.matriz[i][i] = 1;
}

//to-do: sumar, concatenar, abstraer vectores, autovalores, autovectores.