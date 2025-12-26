#include "../include/clientes.h"

Cliente* crearNodoCliente(char* cedula, char* nombre, char* direccion, char* telefono, char* correo, char* tarjeta) {
    Cliente* nuevo = (Cliente*)malloc(sizeof(Cliente));
    if (!nuevo) {
        printf("[Error] No hay memoria para crear el cliente.\n");
        return NULL;
    }
    // Copia de cadenas
    strcpy(nuevo->cedula, cedula);
    strcpy(nuevo->nombre, nombre);
    strcpy(nuevo->direccion, direccion);
    strcpy(nuevo->telefono, telefono);
    strcpy(nuevo->numero_tarjeta, tarjeta);
    strcpy(nuevo->correo, correo);

    // Valores iniciales por defecto (Regla de negocio: Empiezan sin plan ni puntos)
    nuevo->plan = PLAN_SIN;
    nuevo->puntos = 0;
    nuevo->puntos_dorados = 0;
    nuevo->total_compras = 0.0;
    nuevo->sig = NULL;

    return nuevo;
}

void insertarCliente(Cliente** cabeza, Cliente* nuevoNodo) {
    // Validar duplicados
    if (buscarClientePorCedula(*cabeza, nuevoNodo->cedula) != NULL) {
        printf("[Error] La cedula %s ya existe. No se puede registrar.\n", nuevoNodo->cedula);
        free(nuevoNodo);
        return;
    }

    // Inserción al final para mantener orden de registro(al menos que cambiemos el tipo de orden)
    if (*cabeza == NULL) {
        *cabeza = nuevoNodo;
    } else {
        //Se tendria que tener un *cabeza y un *Fin para quitar el while(mas eficiente mi opinion)
        Cliente* aux = *cabeza;
        while (aux->sig != NULL) {
            aux = aux->sig;
        }
        aux->sig = nuevoNodo;
    }
    printf(">> Cliente %s registrado con exito.\n", nuevoNodo->nombre);
}

Cliente* buscarClientePorCedula(Cliente* cabeza, char* cedula) {
    Cliente* aux = cabeza;
    //Mejor con un arbol sería de ordenar bien pero en insertar cliente 
    while (aux != NULL) {
        if (strcmp(aux->cedula, cedula) == 0) {
            return aux;
        }
        aux = aux->sig;
    }
    return NULL;
}
//Si se requiere cambiar algun dato del Cliente o se ingreso mal
void actualizarCliente(Cliente* cabeza, char* cedula) {
    Cliente* c = buscarClientePorCedula(cabeza, cedula);
    if (!c) {
        printf("[Error] Cliente con cedula %s no encontrado.\n", cedula);
        return;
    }

    int opcion;
    
    do {
        // Mostramos los datos actuales para que el usuario sepa qué está editando
        printf("\n--- EDITAR CLIENTE: %s ---\n", c->nombre);
        printf("1. Nombre actual: %s\n", c->nombre);
        printf("2. Direccion actual: %s\n", c->direccion);
        printf("3. Telefono actual: %s\n", c->telefono);
        printf("4. Correo actual: %s\n", c->correo);
        printf("0. Guardar y Salir\n");
        printf("Seleccione el dato a modificar: ");
        
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Ingrese Nuevo Nombre: ");
                scanf(" %[^\n]", c->nombre);
                break;
            case 2:
                printf("Ingrese Nueva Direccion: ");
                scanf(" %[^\n]", c->direccion);
                break;
            case 3:
                printf("Ingrese Nuevo Telefono: ");
                scanf(" %[^\n]", c->telefono);
                break;
            case 4:
                printf("Ingrese Nuevo Correo: ");
                scanf(" %[^\n]", c->correo);
                break;
            case 0:
                printf(">> Cambios guardados para el cliente %s.\n", c->cedula);
                break;
            default:
                printf("[Error] Opción no válida. Intente de nuevo.\n");
        }
    } while (opcion != 0);
}

void eliminarCliente(Cliente** cabeza, char* cedula) {
    if (*cabeza == NULL) return;

    Cliente *actual = *cabeza;
    Cliente *anterior = NULL;

    while (actual != NULL && strcmp(actual->cedula, cedula) != 0) {
        anterior = actual;
        actual = actual->sig;
    }

    if (actual == NULL) {
        printf("[Info] Cliente %s no encontrado para eliminar.\n", cedula);
        return;
    }

    // Re-enlace de punteros
    if (anterior == NULL) {
        *cabeza = actual->sig; // Era el primero
    } else {
        anterior->sig = actual->sig;
    }

    printf(">> Cliente %s eliminado del sistema.\n", actual->nombre);
    free(actual);
}

void listarClientes(Cliente* cabeza) {
    printf("\n%-12s %-20s %-15s %-10s %-8s\n", "CEDULA", "NOMBRE", "TELEFONO", "PLAN", "PUNTOS");
    printf("-----------------------------------------------------------------------\n");
    Cliente* aux = cabeza;
    while (aux != NULL) {
        char planStr[10];
        if (aux->plan == PLAN_SIN) strcpy(planStr, "SIN");
        else if (aux->plan == PLAN_NORMAL) strcpy(planStr, "NORMAL");
        else strcpy(planStr, "PREMIUM");

        printf("%-12s %-20.20s %-15s %-10s %-8d\n", aux->cedula, aux->nombre, aux->telefono, planStr, aux->puntos);
        aux = aux->sig;
    }
    printf("-----------------------------------------------------------------------\n");
}

void liberarListaClientes(Cliente* cabeza) {
    Cliente* aux;
    while (cabeza != NULL) {
        aux = cabeza;
        cabeza = cabeza->sig;
        free(aux);
    }
}

/*
Para la visualizacion de los Clientes este es un mejor formato pero es de la interfaz primero pulir logica

// Función auxiliar para formatear texto con "..." si es muy largo
void formatearTexto(char* destino, const char* origen, int longitudMax) {
    if (strlen(origen) <= longitudMax) {
        strcpy(destino, origen);
    } else {
        // Copiamos hasta (longitudMax - 3) y agregamos "..."
        strncpy(destino, origen, longitudMax - 3);
        destino[longitudMax - 3] = '\0'; // Aseguramos el final de cadena
        strcat(destino, "...");
    }
}

void listarClientes(Cliente* cabeza) {
    if (!cabeza) {
        printf("No hay clientes registrados.\n");
        return;
    }

    // Buffers temporales para guardar el texto con "..."
    char nombreFmt[26];    // 25 caracteres + 1 nulo
    char direccionFmt[21]; // 20 caracteres + 1 nulo (agregamos dirección al reporte)
    char planStr[10];

    // Encabezado
    printf("\n%-12s %-25s %-20s %-15s %-10s %-8s\n", 
           "CEDULA", "NOMBRE", "DIRECCION", "TELEFONO", "PLAN", "PUNTOS");
    printf("----------------------------------------------------------------------------------------------\n");
    
    Cliente* aux = cabeza;
    while (aux != NULL) {
        // 1. Convertir el Plan a texto
        if (aux->plan == PLAN_SIN) strcpy(planStr, "SIN");
        else if (aux->plan == PLAN_NORMAL) strcpy(planStr, "NORMAL");
        else strcpy(planStr, "PREMIUM");

        // 2. Formatear Nombre (Max 25 chars)
        formatearTexto(nombreFmt, aux->nombre, 25);

        // 3. Formatear Dirección (Max 20 chars) - Opcional pero recomendado
        formatearTexto(direccionFmt, aux->direccion, 20);

        // 4. Imprimir usando los textos ya formateados
        // Nota: Usamos %-25s normal porque 'nombreFmt' ya tiene el tamaño correcto
        printf("%-12s %-25s %-20s %-15s %-10s %-8d\n", 
            aux->cedula, 
            nombreFmt, 
            direccionFmt,
            aux->telefono, 
            planStr, 
            aux->puntos);
            
        aux = aux->sig;
    }
    printf("----------------------------------------------------------------------------------------------\n");
}

CEDULA       NOMBRE                    DIRECCION            TELEFONO        PLAN       PUNTOS
----------------------------------------------------------------------------------------------
0102030405   Juan Perez                Av. Loja             0991234567      NORMAL     100
1755555555   Roberto Carlos De La...   Calle de los Euc...  0988888888      PREMIUM    500
0102030406   Ana Loor                  Centro               0997654321      SIN        0


*/