#include <stdio.h>
#include <stddef.h>

typedef struct {
	double *vector;
	size_t len;
} Vector_N;

void imprimir_vector_N(Vector_N *vector);