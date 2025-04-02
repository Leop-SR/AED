#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Max_Claves 300000 //Número máximo de claves
#define Max_Linea 10 //Tamaño máximo de una clave inclutendo el carácter fin de cadena '\0'

typedef struct {
    char letra; //Guarda la letra asociada al intervalo
    int inicio; //Dónde inicia el intervalo
    int fin; //Dónde termina el intervalo 
} Indice; 

Indice indices[26]; // Creamos un arreglo de 26 indices para letras A-Z
char claves[Max_Claves][Max_Linea]; //Creamos una matriz que almacena las claves 
int total_claves = 0; 

void cargarDatos(char *archivo) {
    FILE *fp = fopen(archivo, "r");
    if (!fp) {
        printf("No se pudo abrir tu archivo.\n");
        exit(1);
    } //Abre el archivo en modo lectura y avisa si hay errores 
    
    char buffer[Max_Linea]; //String auxiliar para copiar
    char letra_actual = '\0';
    int index_letra = -1; //Inicialización de variables

    while (fgets(buffer, Max_Linea, fp) && total_claves < Max_Claves) { 
        //fgets va a leer el archivo hasta y almacenara lo leído en el buffer 
        buffer[strcspn(buffer, "\n")] = 0;  // Eliminar salto de línea que se copio en el buffer
        strcpy(claves[total_claves], buffer); // Copiamos lo leído en el renglón n de la matriz 
        
        if (letra_actual != buffer[0]) { // Nueva letra detectada
            letra_actual = buffer[0];
            index_letra = letra_actual - 'A'; 
            /*Hacemos la anterior resta para encontrar el valor del index en el arreglo de indices donde 
            guardaremos la letra para ir generando la estructura de indexación*/
            indices[index_letra].letra = letra_actual;
            indices[index_letra].inicio = total_claves;
            if (index_letra > 0) {
                indices[index_letra - 1].fin = total_claves - 1;
            }
        }
        //Si encuentra una nueva letra leyendo el archivo, actualiza el struct del index n(0-27) con valores inicio/fin
        total_claves++;
    }
    if (index_letra >= 0) 
        indices[index_letra].fin = total_claves - 1;
    fclose(fp);
}

int busquedaBinaria(int inicio, int fin, char *clave) {
    int izquierda = inicio, derecha = fin;
    while (izquierda <= derecha) {
        int medio = (izquierda + derecha) / 2;
        int cmp = strcmp(claves[medio], clave);
        if (cmp == 0) 
            return medio;
        else if (cmp < 0) 
            izquierda = medio + 1;
        else 
            derecha = medio - 1;
    }
    return -1;
    /*Recibe los indices inicio y fin en el intervalo en el cual buscar y aplica la búsqueda binaria, devuelve -1
    si no encuentra la clave*/
}

void buscarClave(char *clave) {
    char letra = clave[0]; 
    int index_letra = letra - 'A'; /* Extraemos el primer carácter de la clave (la letra) y con la resta
    encontramos el index para buscar en nuestro arreglo de indices*/
    if (index_letra < 0 || index_letra >= 26 || indices[index_letra].inicio > indices[index_letra].fin) {
        printf("Clave no encontrada.\n");
        return; 
    } //Revisamos si existe el indice, es decir si introdujeron una clave valida
    
    int pos = busquedaBinaria(indices[index_letra].inicio, indices[index_letra].fin, clave);
    if (pos != -1) {
        printf("Clave %s encontrada en la posición %d.\n", clave, pos+1);
    } else {
        printf("Clave no encontrada.\n");
    } //Realizamos la busqueda binaria 
}

int main() {
    cargarDatos("SALIDA.txt");
    char clave_buscar[Max_Linea];
    
    printf("Ingrese la clave a buscar: ");
    scanf("%9s", clave_buscar); //Ingresa clave a buscar
    
    buscarClave(clave_buscar);//Busca la clave 
    return 0;
}
