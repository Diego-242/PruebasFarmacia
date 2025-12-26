#include "../include/proveedores.h"

Proveedor* crearNodoProveedor(char* ruc, char* nombre, char* direccion, char* telefono, char* correo) {
    Proveedor* nuevo = (Proveedor*)malloc(sizeof(Proveedor));
    if (!nuevo) return NULL;

    strcpy(nuevo->RUC, ruc);
    strcpy(nuevo->nombre, nombre);
    strcpy(nuevo->direccion, direccion);
    strcpy(nuevo->telefono, telefono);
    strcpy(nuevo->correo, correo);

    // Inicializamos en NULL porque la gestión de productos es otro módulo
    nuevo->producto = NULL; 
    nuevo->total_compras = 0.0;
    nuevo->sig = NULL;

    return nuevo;
}

void insertarProveedor(Proveedor** cabeza, Proveedor* nuevoNodo) {
    if (buscarProveedorPorRUC(*cabeza, nuevoNodo->RUC) != NULL) {
        printf("[Error] Proveedor con RUC %s ya existe.\n", nuevoNodo->RUC);
        free(nuevoNodo);
        return;
    }

    if (*cabeza == NULL) {
        *cabeza = nuevoNodo;
    } else {
        Proveedor* aux = *cabeza;
        while (aux->sig != NULL) {
            aux = aux->sig;
        }
        aux->sig = nuevoNodo;
    }
    printf(">> Proveedor %s agregado.\n", nuevoNodo->nombre);
}

Proveedor* buscarProveedorPorRUC(Proveedor* cabeza, char* ruc) {
    Proveedor* aux = cabeza;
    while (aux != NULL) {
        if (strcmp(aux->RUC, ruc) == 0) return aux;
        aux = aux->sig;
    }
    return NULL;
}

void listarProveedores(Proveedor* cabeza) {
    printf("\n%-15s %-25s %-15s %-20s\n", "RUC", "EMPRESA", "TELEFONO", "CORREO");
    printf("----------------------------------------------------------------------------\n");
    Proveedor* aux = cabeza;
    while (aux != NULL) {
        printf("%-15s %-25.25s %-15s %-20.25s\n", 
               aux->RUC, aux->nombre, aux->telefono, aux->correo);
        aux = aux->sig;
    }
    printf("----------------------------------------------------------------------------\n");
}

void liberarListaProveedores(Proveedor* cabeza) {
    Proveedor* aux;
    while (cabeza != NULL) {
        aux = cabeza;
        cabeza = cabeza->sig;
        free(aux);
    }
}

/*
static void formatearTexto(char* destino, const char* origen, int longitudMax) {
    if (strlen(origen) <= longitudMax) {
        strcpy(destino, origen);
    } else {
        strncpy(destino, origen, longitudMax - 3);
        destino[longitudMax - 3] = '\0'; 
        strcat(destino, "...");
    }
}

void listarProveedores(Proveedor* cabeza) {
    if (!cabeza) {
        printf("No hay proveedores registrados.\n");
        return;
    }

    char nombreFmt[26];    // Buffer para nombre recortado
    char direccionFmt[26]; // Buffer para direccion recortada
    char correoFmt[21];    // Buffer para correo recortado

    printf("\n%-15s %-25s %-25s %-15s %-20s\n", 
           "RUC", "EMPRESA", "DIRECCION", "TELEFONO", "CORREO");
    printf("--------------------------------------------------------------------------------------------------------\n");
    
    Proveedor* aux = cabeza;
    while (aux != NULL) {
        // Usamos la funcion auxiliar para proteger la tabla
        formatearTexto(nombreFmt, aux->nombre, 25);
        formatearTexto(direccionFmt, aux->direccion, 25);
        formatearTexto(correoFmt, aux->correo, 20);

        printf("%-15s %-25s %-25s %-15s %-20s\n", 
               aux->RUC, 
               nombreFmt, 
               direccionFmt, 
               aux->telefono, 
               correoFmt);
        aux = aux->sig;
    }
    printf("--------------------------------------------------------------------------------------------------------\n");
}

RUC             EMPRESA                   DIRECCION                 TELEFONO        CORREO              
--------------------------------------------------------------------------------------------------------
1790012345001   FarmaCorp S.A.            Av. De Las Americas...    0991234567      contacto@farma...   
0102030405001   Distribuidora Del A...    Parque Industrial C...    074040404       ventas@austro...    
--------------------------------------------------------------------------------------------------------


*/
