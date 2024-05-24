# **************************************************************
#
# ****************************************************************

# Variables
CC = gcc
OBJ = functions.c
TARGETS = Fuente_Evaluacion mm_clasico mm_transpuesta
EJECUTABLE_C = _clasico
EJECUTABLE_T = _transpuesta

# Compilación por defecto
all: $(TARGETS)

# Reglas específicas para cada ejecutable
Fuente_Evaluacion: Fuente_Evaluacion.c $(OBJ)
	$(CC) $@.c -o $@
	
mm_clasico: mm_clasico.c $(OBJ)
	$(CC) $@.c -o $(EJECUTABLE_C)

mm_transpuesta: mm_transpuesta.c $(OBJ)
	$(CC) $@.c -o $(EJECUTABLE_T)

TAM = 1000
HILOS = 1

#El make se puede llamar de la siguiente manera
#make run_name TAM = tamanio HILOS = hilos

run_Fuente_Evaluacion:
	./Fuente_Evaluacion ${TAM} ${HILOS}

run_mm_clasico:
	./_clasico ${TAM} ${HILOS}

run_mm_transpuesta:
	./_transpuesta ${TAM} ${HILOS}

# Limpieza
clean:
	rm -f $(TARGETS)

clear:
	rm -f $(EJECUTABLE_C) $(EJECUTABLE_T) Fuente_Evaluacion

remove_dat:
	find . -name "*.dat" -type f -delete 

.PHONY: all clean run_Fuente_Evaluacion run_mm_clasico run_mm_transpuesta
