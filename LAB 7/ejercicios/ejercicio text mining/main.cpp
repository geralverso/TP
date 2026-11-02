#include "Bibliotecas/Funciones.h"

int main() {

    char* dicOtros[CAP_OTROS], *dicPalabras[CAP_PALABRAS], *dicDesconocidas[CAP_DESCONOCIDOS];
    int numOtros, numPalabras, numDesconocidas;
    int cantAparicionesOtros[CAP_OTROS]{}, cantAparicionesPalabras[CAP_PALABRAS]{},
        cantAparicionesDesconocidas[CAP_DESCONOCIDOS]{};

    cargarDiccionario("ArchivosDeDatos/otros.txt", dicOtros, numOtros);
    cargarDiccionario("ArchivosDeDatos/palabras.txt", dicPalabras, numPalabras);

    generarReporteSimple("ArchivosDeReporte/ReporteSimple.txt", dicOtros, dicPalabras, numOtros, numPalabras);

    ordenarDiccionario(dicOtros, numOtros);
    ordenarDiccionario(dicPalabras, numPalabras);
    generarReporteSimple("ArchivosDeReporte/ReporteSimpleOrdenado.txt", dicOtros, dicPalabras, numOtros,
        numPalabras);

    leerTexto("ArchivosDeDatos/texto.txt", dicOtros, dicPalabras, dicDesconocidas, numOtros, numPalabras,
        numDesconocidas, cantAparicionesOtros, cantAparicionesPalabras, cantAparicionesDesconocidas);

    ordenarDesconocidas(dicDesconocidas, numDesconocidas, cantAparicionesDesconocidas);
    generarListaDesconocidas("ArchivosDeReporte/desconocidas.txt", dicDesconocidas, numDesconocidas,
        cantAparicionesDesconocidas);

    generarResumenGeneral("ArchivosDeReporte/Reporte1.txt", numOtros, numPalabras,numDesconocidas,
        cantAparicionesOtros, cantAparicionesPalabras, cantAparicionesDesconocidas);

    ordenarHistograma(numPalabras, cantAparicionesPalabras, dicPalabras);
    generarHistograma("ArchivosDeReporte/Reporte2.txt", numPalabras, cantAparicionesPalabras, dicPalabras);

    generarRankingGeneral("ArchivosDeReporte/Reporte3.txt", numOtros, numPalabras, cantAparicionesOtros,
        cantAparicionesPalabras, dicOtros, dicPalabras);

    liberarMemoria(dicOtros, dicPalabras, dicDesconocidas, numOtros, numPalabras, numDesconocidas);

    return 0;
}
