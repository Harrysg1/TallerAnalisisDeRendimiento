/**************************************************************
# Pontificia Universidad Javeriana
#     Autor: Martin Vasquez Ramirez
#     Fecha: Mayo 2024
#     Materia: Sistemas Operativos
#     Tema: Taller de Evaluación de Rendimiento
#     Fichero: Codigo en lenguaje C, con un algoritmo de multiplicacion de   
#     matrices con funcionalidad de hilos, para separar tareas a la hora de 
#     desarrollar el algoritmo buscando un mayor rendimiento
#****************************************************************/

#include "functions.h"  //Incluir archivo de cabecera con definiciones de funciones y variables
#include <stdio.h>      //Incluir biblioteca estándar de entrada/salida
#include <pthread.h>    //Incluir biblioteca para el manejo de hilos POSIX
#include <unistd.h>     //Incluir biblioteca para interacción con el sistema operativo POSIX
#include <stdlib.h>     //Incluir biblioteca para manejo de memoria y otros utilitarios
#include <time.h>       //Incluir biblioteca para manejo del tiempo
#include <sys/time.h>   //Incluir biblioteca para manejo de tiempo de ejecucion en el sistema


int main(int argc, char *argv[]) {
    if (argc < 3) {
        //Verificar el número de argumentos pasados al programa
        printf("Ingreso de argumentos \n $./ejecutable tamMatriz numHilos\n");
        return -1;  //Devolver -1 en caso de no recibir el tamaño ni numero de hilos
    }
    
    int SZ = atoi(argv[1]);  //Casteo del tamaño recibido como argumento
    int n_threads = atoi(argv[2]);  // Casteo del numero de hilos recibido como segundo argumento

    pthread_t p[n_threads];  //Arreglo de identificadores de hilos
    pthread_attr_t atrMM;  //Atributos para los hilos

    //Asignar punteros cierta posicion de memoeria de MEM_CHUNK segun el tamaño de matriz
    mA = MEM_CHUNK;
    mB = mA + SZ*SZ;
    mC = mB + SZ*SZ;

    llenar_matriz(SZ);  // Rellena las matrices A y B con valores y la matriz C con ceros
    print_matrix(SZ, mA);  // Muestra la matriz A
    print_matrix(SZ, mB);  // Muestra la matriz B

    inicial_tiempo();  // Inicia el temporizador para medir el tiempo de la operación
    pthread_mutex_init(&MM_mutex, NULL);  // Prepara el mutex para su uso
    pthread_attr_init(&atrMM);  // Configura los atributos para los hilos
    pthread_attr_setdetachstate(&atrMM, PTHREAD_CREATE_JOINABLE);  // Configura los hilos para que puedan ser unidos

    // Creación de los hilos y llamada a la función mult_thread, con los datos empaquetados en la estructura parametros
    for (int j = 0; j < n_threads; j++) {
        struct parametros *datos = (struct parametros *) malloc(sizeof(struct parametros));
        datos->idH = j;  // Asigna el identificador del hilo
        datos->nH = n_threads;  // Asigna el número total de hilos
        datos->N = SZ;  // Asigna el tamaño de la matriz
        pthread_create(&p[j], &atrMM, mult_thread, (void *)datos);  // Crea el hilo
    }

    //Esperar a todos los hilos su finalizacion
    for (int j = 0; j < n_threads; j++)
        pthread_join(p[j], NULL);

    final_tiempo();  //Detener el temporizador y mostrar el tiempo transcurrido
    print_matrix(SZ, mC);  //Imprimir la matriz resultante C

    //Limpiar recursos
    pthread_attr_destroy(&atrMM);
    pthread_mutex_destroy(&MM_mutex);
    pthread_exit(NULL);  //Terminar todos los hilos y salir
}
