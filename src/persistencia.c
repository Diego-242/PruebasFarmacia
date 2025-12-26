#include "../include/persistencia.h"

// ------------------- CLIENTES -------------------
void guardarClientes(Cliente* cabeza) {
    FILE *archivo = fopen("data/clientes.txt", "w");
    if (archivo == NULL) {
        printf("[Error] No se pudo abrir data/clientes.txt para escribir.\n");
        return;
    }

    Cliente* aux = cabeza;
    while (aux != NULL) {
        // Orden: CEDULA|NOMBRE|DIRECCION|TELEFONO|TARJETA|CORREO|PLAN|PUNTOS|PT_DOR|TOTAL
        fprintf(archivo, "%s|%s|%s|%s|%s|%s|%d|%d|%d|%.2f\n",
                aux->cedula,
                aux->nombre,
                aux->direccion,
                aux->telefono,
                aux->numero_tarjeta,
                aux->correo,
                aux->plan,
                aux->puntos,
                aux->puntos_dorados,
                aux->total_compras);
        aux = aux->sig;
    }
    fclose(archivo);
    printf("[Persistencia] Datos de clientes guardados.\n");
}

void cargarClientes(Cliente** cabeza) {
    FILE *archivo = fopen("data/clientes.txt", "r");
    if (archivo == NULL) {
        printf("[Info] No se encontro archivo de clientes. Se iniciara vacio.\n");
        return;
    }

    char linea[512];
    while (fgets(linea, sizeof(linea), archivo)) {
        // Variables temporales para leer
        char ced[11], nom[60], dir[100], tel[20], tar[30], corr[80];
        int planInt, pt, ptD;
        float tot;

        // sscanf con formato seguro [^|] lee hasta encontrar el pipe
        // Nota: Hay 10 campos en el struct Cliente
        if (sscanf(linea, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%d|%f",
                   ced, nom, dir, tel, tar, corr, &planInt, &pt, &ptD, &tot) == 10) {
            
            Cliente* nuevo = crearNodoCliente(ced, nom, dir, tel, corr, tar);
            
            // Asignamos los datos extra recuperados
            nuevo->plan = (TipoPlan)planInt;
            nuevo->puntos = pt;
            nuevo->puntos_dorados = ptD;
            nuevo->total_compras = tot;

            insertarCliente(cabeza, nuevo);
        }
    }
    fclose(archivo);
    printf("[Persistencia] Clientes cargados desde archivo.\n");
}

// ------------------- PROVEEDORES -------------------
void guardarProveedores(Proveedor* cabeza) {
    FILE *archivo = fopen("data/proveedores.txt", "w");
    if (!archivo) {
        printf("[Error] No se pudo abrir data/proveedores.txt\n");
        return;
    }

    Proveedor* aux = cabeza;
    while (aux != NULL) {
        // RUC|NOMBRE|DIRECCION|TELEFONO|CORREO|TOTAL_COMPRAS
        fprintf(archivo, "%s|%s|%s|%s|%s|%.2f\n",
                aux->RUC, aux->nombre, aux->direccion, 
                aux->telefono, aux->correo, aux->total_compras);
        aux = aux->sig;
    }
    fclose(archivo);
    printf("[Persistencia] Datos de proveedores guardados.\n");
}

void cargarProveedores(Proveedor** cabeza) {
    FILE *archivo = fopen("data/proveedores.txt", "r");
    if (!archivo) return;

    char linea[512];
    while (fgets(linea, sizeof(linea), archivo)) {
        char ruc[14], nom[60], dir[100], tel[20], corr[80];
        float tot;

        if (sscanf(linea, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%f",ruc, nom, dir, tel, corr, &tot) == 6) {
            
            Proveedor* nuevo = crearNodoProveedor(ruc, nom, dir, tel, corr);
            nuevo->total_compras = tot;
            
            insertarProveedor(cabeza, nuevo);
        }
    }
    fclose(archivo);
    printf("[Persistencia] Proveedores cargados desde archivo.\n");
}

void cargarConfig(void) {
    // Si necesitas leer data/config.txt en el futuro
    printf("[Persistencia] Configuracion verificada.\n");
}
