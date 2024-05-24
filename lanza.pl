#**************************************************************
#                 Pontificia Universidad Javeriana
#     Autor: Martin Vasquez Ramirez
#     Fecha: Mayo 2024
#     Materia: Sistemas Operativos
#     Tema: Taller de Evaluación de Rendimiento
#     Fichero: script adaptado para la toma de datos basado en ley 
#     de los grandes numeros para 2 algoritmos de multiplicacion de matrices
#****************************************************************

# Obtiene el directorio de trabajo actual y lo asigna a $Path
$Path = `pwd`;
# Elimina cualquier salto de línea al final de la salida del comando 'pwd'
chomp($Path);  
# Define el nombre del ejecutable que se usará en las pruebas
@Nombre_Ejecutable = ("_clasico" , "_transpuesto");

# Define los tamaños de matrices para las pruebas en un arreglo
@Tamanios = (200,400,800);
#1600,2200,2600,3000,3600);
# Define los números de hilos que se usarán en las pruebas en otro arreglo
@Num_Hilos = (1, 2, 4);

$Repeticiones = 2;

#Ciclo para iterar sobre ambos ejecutables de codigo _clasico y _transpuesto
foreach $nombre (@Nombre_Ejecutable) {
    # Ciclo for para cada tamaño de hilo y numero de hilos
    foreach $hilo (@Num_Hilos) {
        foreach $tam (@Tamanios){
        #Concatena la ruta, nombre del ejecutable, tamaño e hilos
        $file = "$Path/$nombre-$tam-Hilos-$hilo.dat";
            # Ciclo que itera por la cantidad de repeticiones
            for ($i = 0; $i < $Repeticiones; $i++) {
                # Ejecutar linea de comando y sino se puede decir mensaje de error
                system("$Path/$nombre $tam $hilo >> $file");
            }
        }
        close($file);
    }
}

#find . -name "*.bak" -type f -delete comando para borrar todos los .dat