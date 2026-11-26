#include "Bibliotecas/FuncionesAuxiliares.h"

int main() {

    struct NodoDoble* lista;

    leerPalabra("ArchivosDeDatos/Palabra.txt", lista);

    mostrarEnPantalla(lista);

    eliminarLista(lista);

    return 0;
}
