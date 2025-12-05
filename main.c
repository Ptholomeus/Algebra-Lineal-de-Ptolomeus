// (compilar) gcc main.c funciones_matrices.c funciones_fisica_calor.c testear.c solucionar.c exportar_csv.c -o programa

#include <stdlib.h>
#include <stdio.h>
#include "funciones_matrices.h"
#include "funciones_fisica_calor.h"
#include "testear.h"
#include "solucionar.h"
#include "exportar_csv.h"

int main(){
	
	int opt;
	printf("Opciones: \n");
	printf("1: Prueba de matrices 0\n");
	printf("2: Prueba de matrices 1\n");
	printf("3: Resolver problema calor 1 \n");
	scanf("%d", &opt);
	
	// hacerme una funcion de entrada de texto 
	//opt = getchar();
	
	switch (opt){
		
		case 1:
			test_matrices();
			break;
			
		case 2:
			test_matrices_1();
			break;
			
		case 3:
			resolver();
			break;
		
		default:
			break;
	}
	
	return 0;
	
}