/**************************************************************
# Pontificia Universidad Javeriana
#     Autor: Martin Vasquez Ramirez
#     Fecha: Mayo 2024
#     Materia: Sistemas Operativos
#     Tema: Taller de Evaluación de Rendimiento
#     Fichero: Codigo en lenguaje C, con un algoritmo de multiplicacion de
#     matrices clasico de dato a dato
#****************************************************************/
#include "functions.h" //Incluye el archivo de cabecera con las definiciones de las funciones y variables externas
#include <pthread.h>   //Biblioteca para el manejo de hilos POSIX
#include <stdio.h>     //Biblioteca estándar para funciones de entrada/salida
#include <stdlib.h> //Contiene funciones para manejo de memoria dinámica, control de procesos y conversiones
#include <sys/time.h> //Proporciona definiciones para estructuras y funciones adicionales de manejo de tiempo
#include <time.h>     //Para manejar funciones relacionadas con el tiempo
#include <unistd.h> //Proporciona acceso a la funcionalidad del sistema operativo POSIX

int main(int argc, char *argv[]) {
  if (argc < 3) {
    // Comprueba si se han pasado suficientes argumentos al ejecutar el programa
    printf("Uso correcto: \n $./ejecutable tamMatriz numHilos\n");
    return -1; // Finaliza el programa con un código de error si no se
               // proporcionan suficientes argumentos
  }
  int SZ = atoi(argv[1]); // Convierte el primer argumento a entero para el
                          // tamaño de la matriz
  int n_threads = atoi(argv[2]); // Convierte el segundo argumento a entero para
                                 // el número de hilos

  pthread_t p[n_threads]; // Arreglo para almacenar identificadores de hilos
  pthread_attr_t atrMM;   // Variable para configurar los atributos de los hilos

  // Asigna las matrices A, B y C a segmentos de un bloque de memoria reservado
  mA = MEM_CHUNK;
  mB = mA + SZ * SZ;
  mC = mB + SZ * SZ;

  llenar_matriz(
      SZ); // Llena las matrices A y B con valores y establece C a cero
  print_matrix(SZ, mA); // Imprime la matriz A
  print_matrix(SZ, mB); // Imprime la matriz B

  inicial_tiempo(); // Captura el tiempo de inicio del procesamiento
  pthread_mutex_init(&MM_mutex, NULL); // Inicializa el mutex
  pthread_attr_init(&atrMM);           // Inicializa los atributos de los hilos
  pthread_attr_setdetachstate(
      &atrMM, PTHREAD_CREATE_JOINABLE); // Configura los hilos para que puedan
                                        // ser unidos

  // Crea los hilos para realizar la multiplicación de matrices
  for (int j = 0; j < n_threads; j++) {
    struct parametros *datos =
        (struct parametros *)malloc(sizeof(struct parametros));
    datos->idH = j;        // ID del hilo
    datos->nH = n_threads; // Número total de hilos
    datos->N = SZ;         // Tamaño de la matriz
    pthread_create(&p[j], &atrMM, mult_thread, (void *)datos); // Crea el hilo
  }

  // Espera a que todos los hilos terminen su ejecución
  for (int j = 0; j < n_threads; j++)
    pthread_join(p[j], NULL); // Espera a que el hilo finalice

  final_tiempo(); // Captura el tiempo de finalización y calcula la duración
                  // total
  print_matrix(SZ, mC); // Imprime la matriz resultante C

  // Libera los recursos utilizados
  pthread_attr_destroy(&atrMM);
  pthread_mutex_destroy(&MM_mutex);
  pthread_exit(NULL); // Finaliza todos los hilos y libera los recursos
}
