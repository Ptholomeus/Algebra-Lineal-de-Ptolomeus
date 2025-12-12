// (compilar) gcc main.c funciones_matrices.c funciones_fisica_calor.c testear.c solucionar.c exportar_csv.c -o programa

/*
git status                   (ver qué cambios hay)
git log                      (ver versiones)
git checkout                 (cambia version / rama)
git commit -m "comentario"   (guardar cambios en staging)
git commit --ammend          (permite modificar un commit)
git add file_name            (agrega cambios al staging, el . agrega todo)
git reset                    (borra el staging)
git branch branch_name       (rama)
git remote add origin link   (subir a github)
git push                     (subir cambio)
git restore .                (restaurar)
*/

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
	printf("3: Prueba de matrices 2\n");
	printf("4: Resolver problema calor 1 \n");
	
	printf("Elegir: ");
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
			test_matrices_2();
			break;
			
		case 4:
			resolver();
			break;
		
		default:
			break;
	}
	
	return 0;
	
}