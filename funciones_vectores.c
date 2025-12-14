#include "funciones_vectores.h"

/*

	To-do:
	
	- Abstraer vectores, casos particulares de matrices 

*/

void imprimir_vector_N(Vector_N *vector){
	
	int len = vector->len;
	
	if(len == 0){
		printf("No es un vector. \n");
		return;
	}	
	
	printf("( ");
	for (int i = 0; i < len-1; i++){
		printf("%8.4f, ", vector->vector[i]);
	}
	printf("%8.4f)\n",vector->vector[len-1]);
	
	return;
	
}

