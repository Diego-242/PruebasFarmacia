#ifndef PROVEEDORES_H
#define PROVEEDORES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declaración adelantada para evitar errores de compilación

// Esta en enlazado con otras estructuras
typedef struct CategoriaProductos CategoriaProductos;

typedef struct Proveedor {
    char RUC[14];
    char nombre[60];
    char direccion[100];
    char telefono[20];
    char correo[80];
    
    CategoriaProductos *producto;
    
    float total_compras; // Para ranking proveedor que mas nos vende

    struct Proveedor *sig;
} Proveedor;

// FUNCIONES 
Proveedor* crearNodoProveedor(char* ruc, char* nombre, char* direccion, char* telefono, char* correo);
void insertarProveedor(Proveedor** cabeza, Proveedor* nuevoNodo);
Proveedor* buscarProveedorPorRUC(Proveedor* cabeza, char* ruc);
void listarProveedores(Proveedor* cabeza);
void liberarListaProveedores(Proveedor* cabeza);

#endif
