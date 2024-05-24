/**************************************************************
#
#****************************************************************/

// Si no está definido, definir la interfaz functions.h
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <pthread.h> //Incluye las funciones y tipos para el manejo de hilos POSIX
#include <stdio.h> //Incluye la biblioteca estándar de entrada/salida para funciones como printf
#include <stdlib.h> //Incluye funciones de gestión de memoria dinámica y otras utilidades
#include <sys/time.h> //Incluye definiciones para estructuras y funciones adicionales de manejo de tiempo
#include <time.h> //Permite el uso de funciones relacionadas con el manejo del tiempo
#include <unistd.h> //Proporciona acceso a la API de POSIX para operaciones del sistema operativo

#define DATA_SIZE (1024 * 1024 * 64 * 3)
// Define una constante para el tamaño total de los
// datos de las matrices

// Declara extern para indicar que estas variables están definidas en otro lugar
// (por ejemplo, en un archivo .c)
extern pthread_mutex_t MM_mutex; // Mutex para gestionar el acceso concurrente
extern double MEM_CHUNK[];   // Array que contendrá las matrices A, B y C en un
                             // bloque de memoria contiguo
extern double *mA, *mB, *mC; // Punteros a las matrices A, B y C

// Estructura para pasar parámetros a las funciones de los hilos
struct parametros {
  int nH;  // Número total de hilos
  int idH; // Identificador de este hilo específico
  int N;   // Dimensión de la matriz (NxN)
};

// Variables extern para medir tiempos de ejecución, también definidas en otro
// archivo
extern struct timeval start, stop;

// Declaraciones de funciones que se encuentran en otro archivo .c
// Esto le indica al compilador qué funciones existen, pero no sus
// implementaciones específicas
void llenar_matriz(int SZ);
// Función para inicializar las matrices A y B, y poner C a 0
void print_matrix(int sz, double *matriz);
// Función para imprimir matrices de un tamaño dado
void inicial_tiempo();
// Función para iniciar la medición de tiempo
void final_tiempo();
// Función para finalizar la medición de tiempo y calcular la duración
void *mult_thread(void *variables); // Función que los hilos ejecutarán para
                                    // realizar la multiplicación de matrices

#include "functions.c"

#endif // Finaliza la condición de preprocesador iniciada con #ifndef
       // FUNCTIONS_H.
