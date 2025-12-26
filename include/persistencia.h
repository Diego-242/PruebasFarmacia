#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include "clientes.h"
#include "proveedores.h"

// Funciones para cargar/guardar CLIENTES
void cargarClientes(Cliente** cabeza);
void guardarClientes(Cliente* cabeza);

// Funciones para cargar/guardar PROVEEDORES
void cargarProveedores(Proveedor** cabeza);
void guardarProveedores(Proveedor* cabeza);

// Configuración opcional
void cargarConfig(void);

#endif
