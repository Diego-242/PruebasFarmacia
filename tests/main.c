#include <stdio.h>
#include <stdlib.h>
#include "../include/clientes.h"
#include "../include/proveedores.h"
#include "../include/persistencia.h"
#include "../include/interfaz.h" // <--- INCLUYE ESTO

// Configuración inicial de la ventana
void configurarConsola() {
    system("mode con: cols=100 lines=30"); // Ventana fija de 100x30
    SetConsoleTitle("SISTEMA DE GESTION DE FARMACIA v1.0");
    ocultarCursor();
}

void menuClientes(Cliente** lista) {
    int op;
    char buffer[100]; // Buffer temporal para leer strings
    // Variables temporales
    char ced[11], nom[60], dir[100], tel[20], mail[80], tar[30];

    do {
        system("cls"); // Limpiar
        color(COLOR_PRINCIPAL); // Fondo azul
        
        // Dibujamos el marco
        dibujarCuadro(10, 3, 90, 25);
        
        textoCentrado("GESTION DE CLIENTES", 5, COLOR_TITULO);
        
        gotoxy(35, 8);  printf("1. Registrar Nuevo Cliente");
        gotoxy(35, 10); printf("2. Listar Todos los Clientes");
        gotoxy(35, 12); printf("3. Actualizar Datos de Cliente");
        gotoxy(35, 14); printf("4. Eliminar Cliente");
        gotoxy(35, 16); printf("0. Volver al Menu Principal");
        
        gotoxy(35, 20); printf("Seleccione opcion: ");
        
        mostrarCursor(); // Mostrar cursor para que el usuario escriba
        scanf("%d", &op);
        ocultarCursor();

        // Limpiar area de trabajo para inputs (Efecto visual)
        if(op != 0 && op != 2) {
             dibujarCuadro(20, 8, 80, 22); // Mini ventana encima
        }

        switch(op) {
            case 1:
                textoCentrado("NUEVO CLIENTE", 9, COLOR_TITULO);
                mostrarCursor();
                gotoxy(25, 11); printf("Cedula: "); scanf(" %[^\n]", ced);
                gotoxy(25, 12); printf("Nombre: "); scanf(" %[^\n]", nom);
                gotoxy(25, 13); printf("Direccion: "); scanf(" %[^\n]", dir);
                gotoxy(25, 14); printf("Telefono: "); scanf(" %[^\n]", tel);
                gotoxy(25, 15); printf("Correo: "); scanf(" %[^\n]", mail);
                gotoxy(25, 16); printf("Num Tarjeta: "); scanf(" %[^\n]", tar);
                
                insertarCliente(lista, crearNodoCliente(ced, nom, dir, tel, mail, tar));
                ocultarCursor();
                gotoxy(25, 19); system("pause");
                break;
            case 2:
                system("cls");
                listarClientes(*lista); // Tu función de lista
                printf("\n");
                system("pause");
                break;
            case 3:
                mostrarCursor();
                gotoxy(25, 12); printf("Ingrese Cedula a editar: ");
                scanf(" %[^\n]", ced);
                // Aquí llamamos a tu función de actualizar
                // (Nota: Tu función actualizar tiene sus propios printfs, 
                //  se imprimirán en la consola normal, lo cual está bien)
                actualizarCliente(*lista, ced);
                system("pause");
                break;
            case 4:
                mostrarCursor();
                gotoxy(25, 12); printf("Ingrese Cedula a eliminar: ");
                scanf(" %[^\n]", ced);
                eliminarCliente(lista, ced);
                system("pause");
                break;
        }
    } while(op != 0);
}

// (Repetir lógica similar para menuProveedores...)

int main() {
    configurarConsola(); // <--- IMPORTANTE
    
    Cliente* listaClientes = NULL;
    Proveedor* listaProveedores = NULL;

    cargarClientes(&listaClientes);
    cargarProveedores(&listaProveedores);

    int opcion;
    do {
        system("cls");
        system("color 1F"); // Fondo Azul general, letras blancas
        
        dibujarCuadro(5, 2, 95, 28); // Marco grande
        
        textoCentrado("FARMACIA PROGRA II - PANEL DE CONTROL", 4, COLOR_TITULO);
        
        dibujarCuadro(30, 8, 70, 20); // Marco del menú interno
        
        gotoxy(40, 11); printf("1. MODULO CLIENTES");
        gotoxy(40, 13); printf("2. MODULO PROVEEDORES");
        gotoxy(40, 15); printf("0. SALIR Y GUARDAR");
        
        gotoxy(40, 18); printf("Opcion > ");
        
        mostrarCursor();
        scanf("%d", &opcion);
        ocultarCursor();

        switch(opcion) {
            case 1: menuClientes(&listaClientes); break;
            case 2: 
                // menuProveedores(&listaProveedores); // (Implementar similar al de clientes)
                system("cls"); listarProveedores(listaProveedores); system("pause"); 
                break;
            case 0: 
                textoCentrado("Guardando datos...", 24, COLOR_EXITO);
                break;
        }
    } while (opcion != 0);

    guardarClientes(listaClientes);
    guardarProveedores(listaProveedores);
    liberarListaClientes(listaClientes);
    liberarListaProveedores(listaProveedores);

    return 0;
}