#include <stdio.h>
#include <stdlib.h>
#include "../include/clientes.h"
#include "../include/proveedores.h"
#include "../include/persistencia.h"

void menuClientes(Cliente** lista) {
    int op;
    char ced[11], nom[60], dir[100], tel[20], mail[80], tar[30];
    
    do {
        printf("\n--- GESTION CLIENTES ---\n");
        printf("1. Registrar Cliente\n");
        printf("2. Listar Clientes\n");
        printf("3. Actualizar Cliente\n");
        printf("4. Eliminar Cliente\n");
        printf("0. Volver\n");
        printf("Opcion: ");
        scanf("%d", &op);

        switch(op) {
            case 1:
                printf("Cedula: "); scanf(" %[^\n]", ced);
                printf("Nombre: "); scanf(" %[^\n]", nom);
                printf("Direccion: "); scanf(" %[^\n]", dir);
                printf("Telefono: "); scanf(" %[^\n]", tel);
                printf("Correo: "); scanf(" %[^\n]", mail);
                printf("Num Tarjeta: "); scanf(" %[^\n]", tar);
                insertarCliente(lista, crearNodoCliente(ced, nom, dir, tel, mail, tar));
                break;
            case 2:
                listarClientes(*lista);
                break;
            case 3:
                printf("Cedula a editar: "); scanf(" %[^\n]", ced);
                actualizarCliente(*lista, ced);
                break;
            case 4:
                printf("Cedula a eliminar: "); scanf(" %[^\n]", ced);
                eliminarCliente(lista, ced);
                break;
        }
    } while(op != 0);
}

void menuProveedores(Proveedor** lista) {
    int op;
    char ruc[14], nom[60], dir[100], tel[20], mail[80];

    do {
        printf("\n--- GESTION PROVEEDORES ---\n");
        printf("1. Registrar Proveedor\n");
        printf("2. Listar Proveedores\n");
        printf("0. Volver\n");
        printf("Opcion: ");
        scanf("%d", &op);

        switch(op) {
            case 1:
                printf("RUC: "); scanf(" %[^\n]", ruc);
                printf("Empresa: "); scanf(" %[^\n]", nom);
                printf("Direccion: "); scanf(" %[^\n]", dir);
                printf("Telefono: "); scanf(" %[^\n]", tel);
                printf("Correo: "); scanf(" %[^\n]", mail);
                insertarProveedor(lista, crearNodoProveedor(ruc, nom, dir, tel, mail));
                break;
            case 2:
                listarProveedores(*lista);
                break;
        }
    } while(op != 0);
}

int main() {
    // 1. Inicializar listas vacías
    Cliente* listaClientes = NULL;
    Proveedor* listaProveedores = NULL;

    // 2. Cargar datos del disco (Si existen)
    printf("--- INICIANDO SISTEMA ---\n");
    cargarClientes(&listaClientes);
    cargarProveedores(&listaProveedores);

    // 3. Menú Principal
    int opcion;
    do {
        printf("\n=== FARMACIA: MODULO ADMIN ===\n");
        printf("1. Gestionar Clientes\n");
        printf("2. Gestionar Proveedores\n");
        printf("0. Guardar y Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1: menuClientes(&listaClientes); break;
            case 2: menuProveedores(&listaProveedores); break;
            case 0: printf("Saliendo...\n"); break;
            default: printf("Opcion invalida.\n");
        }
    } while (opcion != 0);

    // 4. Guardar todo antes de morir
    guardarClientes(listaClientes);
    guardarProveedores(listaProveedores);

    // 5. Limpiar memoria (Evitar leaks)
    liberarListaClientes(listaClientes);
    liberarListaProveedores(listaProveedores);

    return 0;
}