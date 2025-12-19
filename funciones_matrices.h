#include <stddef.h>
#include "funciones_vectores.h"

typedef struct {
	double **matriz;
	double *datos;
	int fil, col;
} Matriz;

Matriz crear_matriz(int fil, int col);
void destruir_matriz(Matriz *A);
Matriz crear_submatriz (Matriz A, int fil_quitar, int col);
void imprimir_matriz (Matriz A);
void iniciar_matriz_cero (Matriz *A);
void iniciar_matriz_rand (Matriz A);
void iniciar_matriz_rand_int(Matriz *A);
Matriz crear_traspuesta(Matriz M);
Matriz crear_escalar_mult_matriz (double a, Matriz M);
Matriz crear_cofactor (Matriz M, int fil_cof, int col_cof);
double determinante_bruto (Matriz M);
Matriz crear_adjunta (Matriz M);
Matriz crear_inversa (Matriz *M);
double mult_fil_col (Matriz A, int A_fil, Matriz B, int B_col);
Matriz crear_mult_matriz (Matriz A, Matriz B);
void iniciar_matriz_identidad (Matriz *M);
Matriz crear_matriz_elemental_E ();
Matriz crear_matriz_elemental_P();
Matriz crear_matriz_elemental_M();
void op_sumar_fila(Matriz *M, int a, double k, int b);
void op_permutar_fil(Matriz *M, int a, int b);
void op_permutar_fil_L(Matriz *M, int a, int b);
void op_permutar_col(Matriz *M, int a, int b);
void op_fila_multiplicar(Matriz *M, int a, double k);
void op_normalizar_fila(Matriz *M, int a, int b);
Matriz copiar_matriz(Matriz M);
void triangular_matriz (Matriz *M, Vector_N *cambios);
void triangular_matriz_Gauss (Matriz *M);
void obtener_P_L_U (Matriz *M, Matriz *P, Matriz *L, Matriz *U);
void registrar_op_elemental(Vector_N *cambios, double valor);
double determinante_2(Matriz *M);
Matriz crear_fwd_subs(Matriz *L, Matriz *Pb);
Matriz crear_bwd_subs(Matriz *U, Matriz *y);
void suma_matrices (Matriz *A, Matriz *B, Matriz *C);
void resta_matrices (Matriz *A, Matriz *B, Matriz *C);
void crear_solucion_sistema(Matriz *x, Matriz *A, Matriz *b);