#include "Bibliotecas/Funciones.h"

int main() {

    char texto[CAPACIDAD_TEXTO]{};
    char equivalencias[CAPACIDAD_TEXTO]{};
    char stopWords[CAPACIDAD_TEXTO]{};
    char terminos[CAPACIDAD_TEXTO]{};

    int numEquivalencias;

    //CARGAMOS CADA ARREGLO:
    cargarTexto("ArchivosDeDatos/RetornoDelJedi.txt", texto);
    cargarTexto("ArchivosDeDatos/Equivalencias.txt", equivalencias);
    cargarStopWords("ArchivosDeDatos/StopWords.txt", stopWords);
    cargarTexto("ArchivosDeDatos/Terminos.txt", terminos);

    normalizarTexto(texto, equivalencias, stopWords);

    generarTextoNormalizado("ArchivosDeReporte/ReporteDelJediNormalizado.txt", texto);


    return 0;
}
