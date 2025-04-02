#include<stdio.h>
#include<stdlib.h>
#define max 14
int solutions = 0;

void ImprimeSol(int, int [max][max]);
int Esseguro(int, int [max][max], int, int);
int Backtracking(int, int [max][max], int);
void Reinas(int);

int main(){
    int size;
    printf("Problema de las N reinas\n");
    printf("Ingrese el size del tablero:\n");
    scanf("%d", &size);
    Reinas(size);
    return 0;
}

void ImprimeSol(int n, int tablero[max][max]){
    printf("Solucion #%d:\n", solutions);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (tablero[i][j])
                printf("Q ");
            else
                printf(". ");
            }
        printf("\n");
        }
    printf("\n");
};

int Esseguro(int n, int tablero[max][max], int r, int c) {
    int i, j;
    
    // Verificar la fila hacia la izquierda
    for (i = 0; i < c; i++)
        if (tablero[r][i])
            return 0;
    
    // Verificar la diagonal superior izquierda
    for (i = r, j = c; i >= 0 && j >= 0; i--, j--)
        if (tablero[i][j])
            return 0;
    
    // Verificar la diagonal inferior izquierda
    for (i = r, j = c; j >= 0 && i < n; i++, j--)
        if (tablero[i][j])
            return 0;
    
    return 1;
}

int Backtracking(int n, int tablero[max][max], int c) {
    // Caso base: todas las reinas colocadas
    if (c == n) {
        solutions++;
        ImprimeSol(n, tablero);
        return 1;
    }
    
    int res = 0;
    for (int i = 0; i < n; i++) {
        if (Esseguro(n, tablero, i, c)) {
            tablero[i][c] = 1; // Colocar reina
            
            // Llamada recursiva para siguiente columna
            res = Backtracking(n, tablero, c + 1) || res;
            
            tablero[i][c] = 0; // Backtrack (quitar reina)
        }
    }
    
    return res;
}

void Reinas(int n) {
    if (n < 0 || n > max) {
        printf("El numero debe estar entre 0 y %d.\n", max);
        return;
    }
    
    if (n == 0) {
        printf("Para n=0 no hay solución porque el tablero es vacio.\n");
        return;
    }
    
    int tablero[max][max] = {0}; // Inicializar con 0s
    
    solutions = 0; // Reiniciar contador
    
    printf("Calculando todas las soluciones para n=%d...\n\n", n);
    Backtracking(n, tablero, 0); // Comenzar desde columna 0
    
    printf("Total de soluciones encontradas: %d\n", solutions);
}