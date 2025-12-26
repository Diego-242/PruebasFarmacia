#ifndef INTERFAZ_H
#define INTERFAZ_H

#include <windows.h>
#include <stdio.h>

// Definición de colores (Fondo | Texto)
// Ejes: 0x1F = Fondo Azul (1) y Texto Blanco Brillante (F)
#define COLOR_PRINCIPAL 0x1F  // Azul con Blanco
#define COLOR_TITULO    0x1E  // Azul con Amarillo
#define COLOR_ERROR     0x4F  // Rojo con Blanco
#define COLOR_EXITO     0x2F  // Verde con Blanco

// Función para mover el cursor a una posición (X, Y)
void gotoxy(int x, int y) {
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}

// Función para ocultar el cursor (que no parpadee)
void ocultarCursor() {
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 100;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(hcon, &cci);
}

// Función para mostrar el cursor (para los scanfs)
void mostrarCursor() {
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 20; // Tamaño normal
    cci.bVisible = TRUE;
    SetConsoleCursorInfo(hcon, &cci);
}

// Cambiar colores
void color(WORD color) {
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
}

// Dibuja un marco doble elegante
void dibujarCuadro(int x1, int y1, int x2, int y2) {
    int i;
    color(COLOR_PRINCIPAL); 
    
    // Esquinas
    gotoxy(x1, y1); printf("%c", 201); // ╔
    gotoxy(x2, y1); printf("%c", 187); // ╗
    gotoxy(x1, y2); printf("%c", 200); // ╚
    gotoxy(x2, y2); printf("%c", 188); // ╝
    
    // Líneas horizontales
    for (i = x1 + 1; i < x2; i++) {
        gotoxy(i, y1); printf("%c", 205); // ═
        gotoxy(i, y2); printf("%c", 205); // ═
    }
    // Líneas verticales
    for (i = y1 + 1; i < y2; i++) {
        gotoxy(x1, i); printf("%c", 186); // ║
        gotoxy(x2, i); printf("%c", 186); // ║
    }
    
    // Rellenar fondo (para borrar lo que había antes)
    for(int y = y1 + 1; y < y2; y++){
        gotoxy(x1 + 1, y);
        for(int x = x1 + 1; x < x2; x++){
             printf(" ");
        }
    }
}

// Imprime un texto centrado en una fila específica
void textoCentrado(char* texto, int y, WORD colorTexto) {
    int len = strlen(texto);
    int x = (100 - len) / 2; // Asumiendo consola de 100 de ancho
    color(colorTexto);
    gotoxy(x, y);
    printf("%s", texto);
}

#endif