#ifndef CLIENTES_H
#define CLIENTES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Definimos el Enum categorizando el Tipo de Plan que Posea el Cliente
typedef enum {
    PLAN_SIN = 0,
    PLAN_NORMAL = 1,
    PLAN_PREMIUM = 2
} TipoPlan;

typedef struct Cliente {
    char cedula[11];
    char nombre[60];
    char direccion[100];
    char telefono[20];
    char numero_tarjeta[30];
    char correo[80];

    TipoPlan plan;
    int puntos;          // Puntos normales acumulados
    int puntos_dorados;

    float total_compras; // Para ranking

    struct Cliente *sig;
} Cliente;

// FUNCIONES
Cliente* crearNodoCliente(char* cedula, char* nombre, char* direccion, char* telefono, char* correo, char* tarjeta);
void insertarCliente(Cliente** cabeza, Cliente* nuevoNodo);
Cliente* buscarClientePorCedula(Cliente* cabeza, char* cedula);
void actualizarCliente(Cliente* cabeza, char* cedula);
// Actualiza solo datos personales del cliente.
// No modifica puntos, puntos dorados ni el plan.
void eliminarCliente(Cliente** cabeza, char* cedula);
void listarClientes(Cliente* cabeza);//Clientes Totales
void liberarListaClientes(Cliente* cabeza);

#endif