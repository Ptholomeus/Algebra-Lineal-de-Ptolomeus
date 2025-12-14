SRC    := main.c \
funciones_matrices.c \
funciones_fisica_calor.c \
solucionar.c \
testear.c \
exportar_csv.c \
funciones_vectores.c
OBJ    := $(SRC:.c=.o)
DEP    := $(SRC:.c=.d)
EXE    := programa.exe
CFLAGS := -O3 -Wall -Wpedantic -Wextra -Wconversion

.PHONY: clean all

all: $(OBJ)
	gcc $(OBJ) -o $(EXE)
	
%.o : %.c
	gcc -c $< -o $@ -MMD -MP

-include $(DEP)
	
clean:
	rm -f $(EXE) $(OBJ) $(DEP)