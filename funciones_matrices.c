#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <stddef.h>
#include "funciones_matrices.h"

/*
	En lo breve:
	- Retornar un aviso / detalle en caso de argumento erróneo
	- Separar en funciones "elementales" y funciones compuestas con las "elementales"
	
	To-Do:
	
	- Verificar que los argumentos sean correctos
	- Forward y backward substitution
	- Pasar argumentos como punteros en lo que haga falta
	- Calcular autovalores (necesito un solver de polinomios)
	
	To-Do long:
	
	- Concatenar matrices, hacer bloques
	- Evaluar independencia lineal
	- Resolver sistemas indeterminados compatibles 
	- Calcular autovectores.
	- Algoritmo de Thomas y de Cholesky
	
	Hecho:
	
	+ Sumar matrices
	+ Algoritmo para triangular matrices (LISTO)
	+ Triangulación Gaussiana
	+ Matrices L y U
	
*/

double epsilon = 0.00001;

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
		
		// Por qué no usar calloc?
		A.datos  = malloc( fil * col * sizeof(double) );
		A.matriz = malloc( fil * sizeof(double *) );
	
		for (int idx = 0; idx < fil; idx++)
			A.matriz[idx] = &A.datos[idx * col];
		
		iniciar_matriz_cero (&A);
		
		return A;
	}
}

void destruir_matriz(Matriz *A){
	
	free((*A).matriz);
	free((*A).datos);
	
	(*A).matriz = NULL;
	(*A).datos  = NULL;
	
	(*A).fil = 0;
	(*A).fil = 0;
	
	return;
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
		
		A_menor = crear_matriz(A.fil-1, A.col-1);
	
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

// probar de hacerla con punteros 
// 13.12.25 Ahora no existe -0.0000 al imprimir
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
			if (fabs(A[i][j]) < epsilon / 10)
				printf("%8.4f, ", 0.0);
			else
				printf("%8.4f, ", A[i][j]); // imprimir hasta el anteultimo elemento
		}
		if (fabs(A[i][col-1]) < epsilon / 10)
			printf("%8.4f }, \n", 0.0);
		else
			printf("%8.4f }, \n", A[i][col-1]); // el ultimo elemento se formatea asi
		
	}
	// imprimir ultima fila 
	printf("\t { ");
	for (int j = 0; j < col-1; j++){
		if (fabs(A[fil-1][j]) < epsilon / 10)
			printf("%8.4f, ", 0.0);
		else
			printf("%8.4f, ", A[fil-1][j]);
	}
	if (fabs(A[fil-1][col-1]) < epsilon / 10)
		printf("%8.4f }\n", 0.0);
	else
		printf("%8.4f }\n", A[fil-1][col-1]); // imprimir sin coma
	
	// imprimir último cero
	printf("}\n");
	
	return;
}

// Gemini recomienda usar memset
// 14.12.25 cambié de doble bucle a un solo bucle, tambien el argumento.
void iniciar_matriz_cero (Matriz *A) {
	
	for (int i = 0; i < A->fil * A->col; i++){
		A->datos[i] = (double) 0;
	}
	
	return;
}

void iniciar_matriz_rand (Matriz A) {
	
	srand(time(NULL));
	
	for (int i = 0; i < A.fil; i++){
		for (int j = 0; j < A.col; j++){
			A.matriz[i][j] = (rand() % (9 + 1)) 
						   + (rand() / (double) RAND_MAX);
		}			
	}
	
	return;
}

void iniciar_matriz_rand_int(Matriz *A){
	
	srand(time(NULL));
	
	for (int i = 0; i < A->fil; i++){
		for (int j = 0; j < A->col; j++){
			A->matriz[i][j] = (rand() % (9 + 1));
		}			
	}
	
	return;
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

// 13.12.25 la modifiqué para que sea creadora
Matriz crear_escalar_mult_matriz (double a, Matriz M) {
	
	Matriz temp = crear_matriz(M.fil, M.col);
	
	for (int i = 0; i < M.fil; i++){
		for (int j = 0; j < M.col; j++){
			temp.matriz[i][j] = a * M.matriz[i][j];
		}
	}
	
	return temp;
	
}

double cofactor (Matriz M, int fil_cof, int col_cof){
	
	double cof;
	Matriz temp;
	
	double signo;
	signo = (fil_cof + col_cof) % 2 == 0 ? 1.0 : -1.0;
	
	temp = crear_submatriz (M, fil_cof, col_cof);
	cof = signo * determinante_2(&temp);
	
	destruir_matriz(&temp);
	
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
			destruir_matriz(&M_det);
		}
		return det;
	}
}

// 13.12.25 Podría haber problema en temp_1 pero no lo entiendo bien.
Matriz crear_adjunta (Matriz M){
	
	Matriz temp_1, temp_2;
	temp_1 = crear_matriz(M.fil, M.col);
	
	for (int i = 0; i < M.fil; i++){
		for (int j = 0; j < M.col; j++){
			temp_1.matriz[i][j] = cofactor(M, i+1, j+1);
		}
	}
	
	temp_2 = crear_traspuesta(temp_1);
	
	destruir_matriz(&temp_1);
	
	return temp_2;
	
}

// Acá también podría haber problema. Cuándo libero temp?
Matriz crear_inversa (Matriz *M){
	
	Matriz temp;
	
	double det;
	
	// verificar que no sea cero
	det = determinante_2 (M);
	
	temp = crear_adjunta(*M);
	
	temp = crear_escalar_mult_matriz ( (double) 1 / det, temp );
	
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

void iniciar_matriz_identidad (Matriz *M){
	
	//comprobar que M es cuadrada
	iniciar_matriz_cero(M);
	for(int i = 0; i < M->fil; i++)
		M->matriz[i][i] = (double) 1;
	
	return;
}

 /*
Matriz crear_matriz_elemental_E (){
	
	// crear matriz cuadrada 
	// iniciar en identidad
	// en fil i col j agregar k 
	// esto equivale a reemplar F_i por F_i + k*F_j
	
	return //matriz 
}

Matriz crear_matriz_elemental_P(){
	
	crear matriz identidad
	fila temp 
	en fila temp guardar fila i 
	en fila i guardar fila j 
	en fila j guardar i 
	
}

Matriz crear_matriz_elemental_M(){
	
	// la fila i se multiplica por k 
	// crear matriz identidad 
	// esto es, al elemento A_ii reemplazarlo por k 
	
}
*/


// En la matriz M suma k*a en la fila b
// A lo bruto, no void
void op_sumar_fila(Matriz *M, int a, double k, int b){
	
	for(int i = 0; i < M->col; i++){
		M->matriz[b-1][i] += k * M->matriz[a-1][i];
	}
	
	return;
}

// Intercambia las filas a y b
void op_permutar_fil(Matriz *M, int a, int b){
	
	double *temp; 
	
	temp = M->matriz[a-1];
	M->matriz[a-1] = M->matriz[b-1];
	M->matriz[b-1] = temp;
	
	return;
}

// Permutar por debajo de la diagonal
void op_permutar_fil_L(Matriz *M, int a, int b){
	
	// Para comodidad, están ordenados.
	if (b < a){
		int tmp = a;
		a = b;
		b = tmp;
	}
	
	// Recorro las columnas de la fila a
	double temp; 
	for (int j = 1; j < a; j++){
		temp = M->matriz[a-1][j-1];
		M->matriz[a-1][j-1] = M->matriz[b-1][j-1];
		M->matriz[b-1][j-1] = temp;	
	}
	
	return;
}

void op_permutar_col(Matriz *M, int a, int b){
	
	double temp; 
	
	for (int i = 0; i < M->fil; i++){
		temp = M->matriz[i][a-1];
		M->matriz[i][a-1] = M->matriz[i][b-1];
		M->matriz[i][b-1] = temp;	
	}

	return;
}

// Multiplica por k la fila a 
void op_fila_multiplicar(Matriz *M, int a, double k){
		for (int i = 0; i < M->col; i++)
			M->matriz[a-1][i] *= k;
		
	return;
}

void op_normalizar_fila(Matriz *M, int a, int b){
	
	double coef = M->matriz[a-1][b-1];
	coef = 1.0 / coef;
	
	op_fila_multiplicar(M, a, coef);
}

Matriz copiar_matriz(Matriz M){
		
		// chequear que las dimensiones den
		
		Matriz copia = crear_matriz(M.fil, M.col);
		
		memcpy(copia.datos, M.datos, M.fil * M.col * sizeof(double));
		
	return copia;
}

/*
	Descripción del algoritmo
	
	1_ Ver elemento a = M[i][j] (empezar con i = j = 1);
	2_ Verificar si es distinto de cero o no.
		2.1_ Es igual a 0
		2.2_ Si la fila no es la última, buscar el primer elemento 
		distinto de cero de la misma columna, en las filas inferiores.
			2.2.1_ Si no hay distinto de cero, continuar en paso 5.
		2.3_ Conseguido el índice, permutarlas.
		2.4_ Continuar con el paso 3.
	3_ Es != 0, entonces normalizar fila.
	4_ Si no es la última, por cada fila inferior j, tomar el elemento b = M[x][i]
		4.1_ A esa fila inferior j, restarle la fila i multiplicada por b
		4.2_ Repetir hasta la última fila 
	5_ Si no es la última, avanzar a la siguiente fila 
		5.1_ Si es la última fila, terminar programa.
	
	
*/
void triangular_matriz (Matriz *M, Vector_N *cambios){
	
	int fil_max = M->fil;
	int col_max = M->col;
	
	int fil_idx, col_idx; // 1-based
	int i, j;
	
	bool coef_es_cero = false;
	
	// double epsilon = 0.00001;
	double aux = 0; // auxiliar
	
	// Este bucle explora cada fil. fil_idx es el índice de la fila.
	// Paso 1
	fil_idx = 1;
	col_idx = 1;
	while(fil_idx <= fil_max && col_idx <= col_max){
		
		// Paso 2
		if( fabs(M->matriz[fil_idx-1][col_idx-1]) < epsilon){
			
			coef_es_cero = true;
			
			// Paso 2.2, busco debajo el primer no nulo debajo
			i = fil_idx;
			while(coef_es_cero == true && i <= fil_max){
				// Paso 2.3 Hallado el primer no nulo, permuto
				if(fabs(M->matriz[i-1][col_idx-1]) > epsilon){
					op_permutar_fil(M, fil_idx, i);
					registrar_op_elemental(cambios, -1.0);
					coef_es_cero = false; // sale del bucle y del bloque
				}
				i++;
			}
			// Paso 2.2.1, No hay elemento debajo del coef que sea no nulo, avanzo de fila
			if (coef_es_cero == true){
				col_idx++;
				continue;
			}
		}
		
		// Paso 3, elemento distinto de cero, normalizar la fila
		aux = M->matriz[fil_idx-1][col_idx-1]; // Registro antes de cambiar
		op_normalizar_fila(M, fil_idx, col_idx);
		registrar_op_elemental(cambios, aux);
		
		
		// Paso 4, eliminar coeficientes en misma columna para cada fila debajo
		if (fil_idx < fil_max){
			for(i = fil_idx+1; i <= fil_max; i++){
				op_sumar_fila(M, fil_idx, (-1.0)*M->matriz[i-1][col_idx-1], i);
				registrar_op_elemental(cambios, 1.0);
			}
		}
		
		// Paso 5, Avanzo a la siguiente fila
		fil_idx++;
		col_idx++;
	}
	
	return;
}

// 14.12.25 versión modificada de triangular_matriz
void triangular_matriz_Gauss (Matriz *M){
	
	int fil_max = M->fil;
	int col_max = M->col;
	
	int fil_idx, col_idx; // 1-based
	int i, j;
	
	bool coef_es_cero = false;
	
	double epsilon = 0.00001;
	double aux = 0; // auxiliar
	
	// Este bucle explora cada fil. fil_idx es el índice de la fila.
	// Paso 1
	fil_idx = 1;
	col_idx = 1;
	while(fil_idx <= fil_max && col_idx <= col_max){
		
		// Paso 2
		if( fabs(M->matriz[fil_idx-1][col_idx-1]) < epsilon){
			
			coef_es_cero = true;
			
			// Paso 2.2, busco debajo el primer no nulo debajo
			i = fil_idx;
			while(coef_es_cero == true && i <= fil_max){
				// Paso 2.3 Hallado el primer no nulo, permuto
				if(fabs(M->matriz[i-1][col_idx-1]) > epsilon){
					op_permutar_fil(M, fil_idx, i);
					coef_es_cero = false; // sale del bucle y del bloque
				}
				i++;
			}
			// Paso 2.2.1, No hay elemento debajo del coef que sea no nulo, avanzo de fila
			if (coef_es_cero == true){
				col_idx++;
				continue;
			}
		}
		
		// Paso 3, elemento distinto de cero, normalizar la fila
		aux = M->matriz[fil_idx-1][col_idx-1]; // Registro antes de cambiar
		/*
		op_normalizar_fila(M, fil_idx, col_idx);
		*/
		
		// Paso 4, eliminar coeficientes en misma columna para cada fila debajo
		if (fil_idx < fil_max){
			for(i = fil_idx+1; i <= fil_max; i++){
				op_sumar_fila(M, fil_idx, (-1.0) * M->matriz[i-1][col_idx-1] / aux, i);
			}
		}
		
		// Paso 5, Avanzo a la siguiente fila
		fil_idx++;
		col_idx++;
	}
	
	return;
}

// 14.12.25 versión modificada de triangular_matriz
// To-do: Pivotar con el elemento diagonal de mayor valor absoluto.
/*
	1_ Ver elemento a = U[i][j] (empezar con i = j = 1);
	2_ Verificar si es distinto de cero o no.
		2.1_ Es igual a 0
		2.2_ Si la fila no es la última, buscar el primer elemento 
		distinto de cero de la misma columna, en las filas inferiores.
			2.2.1_ Si no hay distinto de cero, continuar en paso 5.
		2.3_ Conseguido el índice, permutarlas. 
		2.4_ Registrar el cambio en L, permutando filas y columnas bajo la diagonal. 
		2.5_ Registrar el cambio en P, permutando filas.
		2.6_ Continuar con el paso 3.
	3_ Es != 0, continuar.
	4_ Si no es la última, por cada fila inferior x, tomar el elemento b = M[x][j]
		4.1_ A esa fila inferior x, restarle la fila i multiplicada por b/a
		4.2_ Registrar el cambio en L.
		4.3_ Repetir hasta la última fila 
	5_ Si no es la última, avanzar a la siguiente fila 
		5.1_ Si es la última fila, terminar programa.

*/
void obtener_P_L_U (Matriz *M, Matriz *P, Matriz *L, Matriz *U){
	
	// verificar que det es no nulo
	
	// si det es no nulo:
	
	int fil_max = M->fil;
	int col_max = M->col;
	
	int fil_idx, col_idx; // 1-based
	int i, j;
	
	
	// blablabla
	
	*P = crear_matriz(fil_max, col_max);
	*L = crear_matriz(fil_max, col_max);
	*U = crear_matriz(fil_max, col_max);
	
	iniciar_matriz_identidad(P);
	iniciar_matriz_identidad(L);
	*U = copiar_matriz(*M);
	
	// vars aux
	bool coef_es_cero = false;
	
	double epsilon = 0.00001;
	double aux = 0; // auxiliar
	
	// Este bucle explora cada fil. fil_idx es el índice de la fila.
	// Paso 1
	fil_idx = 1;
	col_idx = 1;
	while(fil_idx <= fil_max && col_idx <= col_max){
		
		// Paso 2
		if( fabs(U->matriz[fil_idx-1][col_idx-1]) < epsilon){
			
			coef_es_cero = true;
			
			// Paso 2.2, busco debajo el primer no nulo debajo
			i = fil_idx;
			while(coef_es_cero == true && i <= fil_max){
				
				// Paso 2.3 Hallado el primer no nulo, permuto luego registro.
				if(fabs(U->matriz[i-1][col_idx-1]) > epsilon){
					coef_es_cero = false; // sale del bucle y del bloque
					// Paso 2.4 registro P
					op_permutar_fil(P, fil_idx, i); // Se aplica primero la última permutación, luego la primera.
													// Esto es, P_1···P_n-1 P_n, o lo que es lo mismo, permutar por
													// derecha, o permutar columnas.
					// Paso 2.5 registro L
					op_permutar_fil_L(L, fil_idx, i); // Permuto las filas, sólo bajo la diagonal.
					op_permutar_fil(U, fil_idx, i);
				}
				i++;
				
			}
			// Paso 2.2.1, No hay elemento debajo del coef que sea no nulo, avanzo de fila
			if (coef_es_cero == true){
				col_idx++;
				continue;
			}
		}
		
		// Paso 3
		
		// Paso 4, eliminar coeficientes en misma columna para cada fila debajo
		if (fil_idx < fil_max){
			for(i = fil_idx+1; i <= fil_max; i++){
				// si hay error este es el hijo de puta, no tengo ganas de pensar más que esto y ya
				aux = U->matriz[i-1][col_idx-1] / U->matriz[fil_idx-1][col_idx-1]; // Registro antes de cambiar
				L->matriz[i-1][fil_idx-1] += aux;
				op_sumar_fila(U, fil_idx, (-1.0) * aux, i);
			}
		}
		
		// Paso 5, Avanzo a la siguiente fila
		fil_idx++;
		col_idx++;
	}
	
	return;
}

void registrar_op_elemental(Vector_N *cambios, double valor){
	// Aumento el tamaño
	size_t len_nueva = cambios->len + 1;
	
	double *temp = realloc(cambios->vector, len_nueva*sizeof(double));
	
	if (temp == NULL) 
		return;
	
	cambios->vector = temp;
	cambios->vector[len_nueva-1] = valor;
	cambios->len = len_nueva;
	
	return;
	
}

// verificar que sea cuadrada
double determinante_2(Matriz *M){
	
	Vector_N operaciones = {NULL, 0};
	Matriz M_copia = crear_matriz(M->fil, M->col);
	M_copia = copiar_matriz(*M);
	
	triangular_matriz (&M_copia, &operaciones);
	
	int len = operaciones.len;
	double det = (double) 1;
	for(int i = 0; i < len; i++){
		det *= operaciones.vector[i];
	}
	
	// CORRECCIÓN DE GEMINI:::::
	// CRÍTICO: Multiplicar por la diagonal resultante de la matriz triangular
	for(int i = 0; i < M_copia.fil; i++){
	det *= M_copia.matriz[i][i]; 
	}
	// Si la matriz era singular, algún elemento diagonal 
	// será 0, haciendo det = 0 correctamente.

	free(operaciones.vector);
	destruir_matriz(&M_copia);
	
	return det;
	
}

Matriz crear_fwd_subs(Matriz *L, Matriz *Pb){
	
	Matriz y = crear_matriz(Pb->fil, 1);
	
	y.matriz[0][0] = (1 / L->matriz[0][0]) * Pb->matriz[0][0];
	for (int i = 1; i < Pb->fil; i++){
		y.matriz[i][0] = Pb->matriz[i][0];
		for(int j = 0; j < i; j++)
			y.matriz[i][0] -= L->matriz[i][j] * y.matriz[j][0]; 
	}
	return y;
	
}

// Solo si U es cuadrada e invertible
// Ver bien los argumentos
Matriz crear_bwd_subs(Matriz *U, Matriz *y){
	
	Matriz x = crear_matriz(y->fil, 1);
	
	x.matriz[x.fil-1][0] = (1 / U->matriz[x.fil-1][x.fil-1]) * y->matriz[x.fil-1][0];
	for (int i = x.fil-2; i >= 0; i--){
		x.matriz[i][0] = y->matriz[i][0];
		for(int j = x.fil-1; j > i; j--)
			x.matriz[i][0] -= U->matriz[i][j] * x.matriz[j][0]; 
		x.matriz[i][0] *= (1 / U->matriz[i][i]);
	}
	
	return x;
}

// A + B = C, opera así porque me parece peligroso que una operación así de 
// frecuente (¿?) reserve memoria cada vez que aparece. Debería hacer lo mismo
// con la multiplicación.

// Revisar que se cumplan las condiciones
void suma_matrices (Matriz *A, Matriz *B, Matriz *C){
	
	for (int i = 0; i < C->fil; i++){
		for (int j = 0; j < C->col; j++)
			C->matriz[i][j] = A->matriz[i][j] + B->matriz[i][j];
	}
	
	return;
}

void resta_matrices (Matriz *A, Matriz *B, Matriz *C){
	
	for (int i = 0; i < C->fil; i++){
		for (int j = 0; j < C->col; j++)
			C->matriz[i][j] = A->matriz[i][j] - B->matriz[i][j];
	}
	
	return;
}

void resolver_sistema(Matriz *x, Matriz *A, Matriz *b){
	
	Matriz P, L, U, y, Pb;
	
	obtener_P_L_U(A, &P, &L, &U);
	Pb = crear_mult_matriz(P, *b);
	
	y = crear_fwd_subs(&L, &Pb);
	*x = crear_bwd_subs(&U, &y);
	
	destruir_matriz(&P);
	destruir_matriz(&L);
	destruir_matriz(&U);
	destruir_matriz(&Pb);
	destruir_matriz(&y);
	
	return;
}