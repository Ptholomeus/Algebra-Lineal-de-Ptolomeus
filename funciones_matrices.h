#include <stddef.h>

typedef struct {
	double **matriz;
	double *datos;
	int fil, col;
} Matriz;

typedef struct {
	double *vector;
	size_t len;
} Vector_N;

Matriz crear_matriz(int fil, int col);
void destruir_matriz(Matriz *A);
Matriz crear_submatriz (Matriz A, int fil_quitar, int col);
void imprimir_matriz (Matriz A);
void iniciar_matriz_cero (Matriz A);
void iniciar_matriz_rand (Matriz A);
Matriz crear_traspuesta(Matriz M);
Matriz escalar_mult_matriz (double a, Matriz M);
Matriz crear_cofactor (Matriz M, int fil_cof, int col_cof);
double determinante_bruto (Matriz M);
Matriz crear_adjunta (Matriz M);
Matriz crear_inversa (Matriz *M);
double mult_fil_col (Matriz A, int A_fil, Matriz B, int B_col);
Matriz crear_mult_matriz (Matriz A, Matriz B);
void iniciar_matriz_identidad (Matriz M);
Matriz crear_matriz_elemental_E ();
Matriz crear_matriz_elemental_P();
Matriz crear_matriz_elemental_M();
void op_sumar_fila(Matriz *M, int a, double k, int b);
void op_permutar_fila(Matriz *M, int a, int b);
void op_fila_multiplicar(Matriz *M, int a, double k);
void op_normalizar_fila(Matriz *M, int a, int b);
Matriz copiar_matriz(Matriz M);
void triangular_matriz (Matriz *M, Vector_N *cambios);
void registrar_op_elemental(Vector_N *cambios, double valor);
void imprimir_vector_N(Vector_N *vector);
double determinante_2(Matriz *M);