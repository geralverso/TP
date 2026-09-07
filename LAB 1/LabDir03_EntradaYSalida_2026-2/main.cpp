#include <iostream>
using namespace std;
#include "Bibliotecas/Funciones.h"

int main() {

    // PARTE 1:
    //en este proyecto se busca leer los datos de asegurados.txt e imprimirlos de manera ordenada en
    //un reporte ReporteAlineado.txt
    leerEscribirAsegurados();

    // PARTE 2:
    //en este proyecto se busca determinar principalmente si la poliza de la persona registrada está vencida
    //o vigente, y cuántos días pasaron/faltan respecto a la fecha establecida 31/08/2026. todo lo anterior
    //presentado en un ReportePolizas.txt de manera ordenada en una tabla.
    int dFijo=31, mFijo=8, aFijo=2026;
    //generarReportePolizas(dFijo, mFijo, aFijo);

    return 0;
}
