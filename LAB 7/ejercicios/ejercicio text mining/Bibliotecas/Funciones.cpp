//
// Created by PC on 30/10/2026.
//

#include "Funciones.h"


//FUNCIONES PARA CARGAR Y LEER:

void abrirArchLectura(const char* nombreArch, ifstream& archivo) {
    archivo.open(nombreArch);
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }
}

char* leerCadena(ifstream &entrada, char delimitador) {
    char buffer[CAP_PALABRA];
    entrada.getline(buffer, CAP_PALABRA, delimitador);
    if (entrada.eof()) return nullptr;
    char* cadena=new char[strlen(buffer)+1];
    strcpy(cadena,buffer);
    return cadena;
}

void llenarDiccionario(ifstream &entrada, char **dic) {
    int i=0;
    while (true) {
        char* cad=leerCadena(entrada, '\n'); //lee la palabra hasta el \n
        if (cad==nullptr or entrada.eof()) break;
        dic[i]=cad;
        i++;
    }
}

void cargarDiccionario(const char* nombreArch, char**dic, int &num) {
    ifstream entrada;
    abrirArchLectura(nombreArch, entrada);
    num=0;
    calcularCantPalabras(entrada, num);
    entrada.clear();
    entrada.seekg(0);
    llenarDiccionario(entrada, dic);
}

void leerTexto(const char* nombreArch, char **dicOtros, char **dicPalabras, char** dicDesconocidas, int numOtros,
    int numPalabras, int &numDesconocidas, int *cantAparicionesOtros, int *cantAparicionesPalabras,
    int *cantAparicionesDesconocidas) {
    ifstream entrada; abrirArchLectura(nombreArch, entrada);
    char palabra[CAP_PALABRA];
    numDesconocidas=0;
    int cantPalabrasTotalesEnElTexto=0;

    while (entrada >> palabra) {
        cantPalabrasTotalesEnElTexto++;
        normalizarPalabra(palabra);
        int posOtros=buscarBinariaPalabra(dicOtros, palabra, numOtros);
        int posPalabras=buscarBinariaPalabra(dicPalabras, palabra, numPalabras);

        if (posOtros!=-1) { //palabras vacias
            cantAparicionesOtros[posOtros]++;
        }
        else if (posPalabras!=-1) { //palabras de contenido
            cantAparicionesPalabras[posPalabras]++;
        }
        else { //palabras desconocidas
            int pos=buscarPalabra(dicDesconocidas, palabra, numDesconocidas);
            if (pos!=-1) cantAparicionesDesconocidas[pos]++;
            else {
                dicDesconocidas[numDesconocidas]=new char[strlen(palabra)+1]; //se le asigna una cantidad de memoria
                strcpy(dicDesconocidas[numDesconocidas],palabra);
                cantAparicionesDesconocidas[numDesconocidas]++; //acá siempre es 1
                numDesconocidas++;
            }
        }
    }
}

int buscarPalabra(char **dic, const char *palabraBuscada, int num) {
    for (int i=0; i<num; i++) {
        if (strcmp(dic[i], palabraBuscada)==0) {
            return i;
        }
    }
    return -1;
}

int buscarBinariaPalabra(char **dic, const char *palabraBuscada, int num) {
    int posInicial=0, posFinal=num-1;
    while (true) {
        int posMedio=(posInicial+posFinal)/2;
        if (strcmp(dic[posMedio],palabraBuscada)==0) return posMedio;
        if (strcmp(dic[posMedio],palabraBuscada)<0) posInicial=posMedio+1;
        else posFinal=posMedio-1;
        if (posInicial>posFinal) return -1;
    }
}


//FUNCIONES PARA ORDENAR:

void intercambiarEntero(int &a, int&b) {
    int aux=a;
    a=b, b=aux;
}

void intercambiarCadena(char *&a, char *&b) {
    char* aux=a;
    a=b, b=aux;
}

void ordenarDiccionario(char **dic, int num) {
    for (int i=0; i<num-1; i++) {
        for (int j=i+1; j<num; j++) {
            if (strcmp(dic[i],dic[j])>0) {
                intercambiarCadena(dic[i],dic[j]);
            }
        }
    }
}

void ordenarDesconocidas(char **dicDesconocidas, int numDesconocidas, int *cantAparicionesDesconocidas) {
    for (int i=0; i<numDesconocidas-1; i++) {
        for (int j=i+1; j<numDesconocidas; j++) {
            if (strcmp(dicDesconocidas[i], dicDesconocidas[j])>0) {
                intercambiarCadena(dicDesconocidas[i], dicDesconocidas[j]);
                intercambiarEntero(cantAparicionesDesconocidas[i], cantAparicionesDesconocidas[j]);
            }
        }
    }
}

void ordenarHistograma(int numPalabras, int *cantAparicionesPalabras, char **dicPalabras) {
    for (int i=0; i<numPalabras-1; i++) {
        for (int j=i+1; j<numPalabras; j++) {
            bool cond1= cantAparicionesPalabras[i]<cantAparicionesPalabras[j];
            bool cond2=cantAparicionesPalabras[i]==cantAparicionesPalabras[j] and strcmp(dicPalabras[i],dicPalabras[j])>0;
            if (cond1 or cond2) {
                intercambiarCadena(dicPalabras[i],dicPalabras[j]);
                intercambiarEntero(cantAparicionesPalabras[i],cantAparicionesPalabras[j]);
            }
        }
    }
}

void ordenarRankingGeneral(char **dicCompleto, int *cantApariciones, char **categorias, int numElementos) {
    for (int i=0; i<numElementos-1; i++) {
        for (int j=i+1; j<numElementos; j++) {
            bool cond1=cantApariciones[i]<cantApariciones[j];
            bool cond2=cantApariciones[i]==cantApariciones[j] and strcmp(dicCompleto[i],dicCompleto[j])>0;
            if (cond1 or cond2) {
                intercambiarCadena(dicCompleto[i],dicCompleto[j]);
                intercambiarCadena(categorias[i],categorias[j]);
                intercambiarEntero(cantApariciones[i],cantApariciones[j]);
            }
        }
    }
}


//FUNCIONES PARA TOKENIZAR:

void normalizarPalabra(char *cad) {
    eliminarSignos(cad);
    pasarAMinuscula(cad);
}

void pasarAMinuscula(char *cad) {
    for (int i=0; cad[i]; i++) {
        if (cad[i]>='A' && cad[i]<='Z') {
            cad[i]+=32;
        }
    }
}

void eliminarSignos(char *cad) {
    int j=0;
    char cadAux[CAP_PALABRA];
    for (int i=0; cad[i]; i++) {
        if (cad[i]!=':' and cad[i]!='.' and cad[i]!=',' and cad[i]!='!') {
            cadAux[j]=cad[i]; //si no es un simbolo, se conserva en la cadena auxiliar
            j++;
        }
    }
    cadAux[j]='\0'; //al final se pone el caracter nulo
    strcpy(cad,cadAux); //la cadena se actualiza
}


//FUNCIONES PARA CALCULAR O ARMAR:

void copiarDatos(int num, char **dicDestino, char **dicFuente, int *cantDestino, const int *cantFuente, char **cat,
    const char *nombre, int &k) {
    for (int i=0; i<num; i++) {
        dicDestino[k]=dicFuente[i];
        cantDestino[k]=cantFuente[i];
        cat[k]=(char*)nombre;
        k++;
    }
}

void calcularCantPalabras(ifstream &entrada, int &num) {
    char palabra[CAP_PALABRA];
    while (entrada >> palabra) { //1RA LEIDA
        num++; //cuenta las palabras/lineas y se reserva la memoria exacta del diccionario
    }
}

int calcularCantTokens(const int *cantApariciones, int num) {
    int cantTokens=0;
    for (int i=0; i<num; i++) {
        cantTokens+=cantApariciones[i];
    }
    return cantTokens;
}

int calcularCantDistintas(const int *cantApariciones, int num){
    int cantDistintas=0;
    for (int i=0; i<num; i++) {
        if (cantApariciones[i]>0){
            cantDistintas++;
        }
    }
    return cantDistintas;
}


//FUNCIONES PARA IMPRIMIR:

void imprimirSeparador(ofstream &salida, char c, int n) {
    for (int i=0; i<n; i++) salida << c;
    salida << endl;
}

void imprimirEncabezadoResumenGeneral(ofstream &salida) {
    imprimirSeparador(salida, '=', ANCHO_REPORTE);
    salida << "REPORTE 1: RESUMEN GENERAL" << endl;
    imprimirSeparador(salida, '=', ANCHO_REPORTE);
    salida << left << setw(20) << "Categoria" << right << setw(10) << "Tokens" << setw(10) << "%"
            << setw(15) << "Distintas" << endl;
}

void imprimirResumenGeneral(ofstream &salida, int cantPalabras, int total, int *cantAparicionesPalabras, int numPalabras,
    int cantOtros, int *cantAparicionesOtros, int numOtros, int cantDesconocidas, int *cantAparicionesDesconocidas,
    int numDesconocidas) {
    imprimirEncabezadoResumenGeneral(salida);
    imprimirInfoCategoria(salida, "CONTENIDO", cantPalabras, total, cantAparicionesPalabras, numPalabras);
    imprimirInfoCategoria(salida, "OTROS", cantOtros, total, cantAparicionesOtros , numOtros);
    imprimirInfoCategoria(salida, "DESCONOCIDA", cantDesconocidas, total, cantAparicionesDesconocidas,
        numDesconocidas);
}

void imprimirConteo(ofstream &salida, char c, int n) {
    for (int i=0; i<n; i++) salida << c;
    salida << " (" << n << ")" << endl;
}

void imprimirEncabezadoRankingGeneral(ofstream &salida) {
    salida << "REPORTE 3: RANKING GENERAL" << endl;
    salida << left << setw(6) << "Pos" << setw(15) << "Palabra" << setw(13) << "Categoria" << right
            << setw(6) << "Frec" << endl;
}

void imprimirInfoCategoria(ofstream &salida, const char *categoria, int cant, int total, int *cantApariciones, int num) {
    double porcentaje=((double)cant/total)*100.0;
    int cantDistintas=calcularCantDistintas(cantApariciones, num);
    salida << left << setw(20) << categoria << right << setw(10) << cant << setw(10) << fixed << setprecision(2)
            << porcentaje << setw(15) << cantDistintas << endl;
}


//FUNCIONES PARA GENERAR REPORTES:

void abrirArchEscritura(const char* nombreArch, ofstream& archivo) {
    archivo.open(nombreArch);
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }
}

void generarReporteSimple(const char *nombreArch, char **dicOtros, char **dicPalabras, int numOtros, int numPalabras) {
    ofstream salida;
    abrirArchEscritura(nombreArch, salida);

    salida << "DICCIONARIO (PALABRAS VACIAS) - otros.txt" << endl;
    for (int i=0; i<numOtros; i++) {
        salida << i+1 << ". " << dicOtros[i] << endl;
    }
    salida << "\nDICCIONARIO (PALABRAS DE CONTENIDO) - palabras.txt" << endl;
    for (int i=0; i<numPalabras; i++) {
        salida << i+1 << ". " << dicPalabras[i] << endl;
    }
}

void generarListaDesconocidas(const char *nombreArch, char **dicDesconocidas, int numDesconocidas,
    const int *cantAparicionesDesconocidas) {
    ofstream salida;
    abrirArchEscritura(nombreArch, salida);

    salida << left << setw(20) << "Palabra" << "Frecuencia" << endl;
    for (int i=0; i<numDesconocidas; i++) {
        salida << left << setw(20) << dicDesconocidas[i] << cantAparicionesDesconocidas[i] << endl;
    }
}

void generarResumenGeneral(const char* nombreArch, int numOtros, int numPalabras, int numDesconocidas,
    int *cantAparicionesOtros, int *cantAparicionesPalabras, int *cantAparicionesDesconocidas) {
    ofstream salida;
    abrirArchEscritura(nombreArch, salida);

    int cantOtros=calcularCantTokens(cantAparicionesOtros,numPalabras);
    int cantPalabras=calcularCantTokens(cantAparicionesPalabras,numPalabras);
    int cantDesconocidas=calcularCantTokens(cantAparicionesDesconocidas,numDesconocidas);
    int total=cantOtros+cantPalabras+cantDesconocidas;

    imprimirResumenGeneral(salida, cantPalabras, total, cantAparicionesPalabras, numPalabras, cantOtros,
        cantAparicionesOtros, numOtros, cantDesconocidas, cantAparicionesDesconocidas, numDesconocidas);
}

void generarHistograma(const char *nombreArch, int numPalabras, int *cantAparicionesPalabras, char **dicPalabras) {
    ofstream salida;
    abrirArchEscritura(nombreArch, salida);
    salida << "REPORTE 2: HISTOGRAMA (cada # = 1 aparicion)" << endl;
    for (int i=0; i<numPalabras; i++) {
        if (cantAparicionesPalabras[i]>0) {
            salida << left << setw(15) << dicPalabras[i] << "| ";
            imprimirConteo(salida, '#', cantAparicionesPalabras[i]);
        }
    }
}

void generarRankingGeneral(const char *nombreArch, int numOtros, int numPalabras, int *cantAparicionesOtros,
    int *cantAparicionesPalabras, char **dicOtros, char **dicPalabras) {
    ofstream salida;
    abrirArchEscritura(nombreArch, salida);
    int numElementos=numOtros+numPalabras, k=0, cantApariciones[numElementos];
    char* dicCompleto[numElementos], * categorias[numElementos];

    copiarDatos(numOtros, dicCompleto, dicOtros, cantApariciones,
        cantAparicionesOtros, categorias, "OTROS", k);
    copiarDatos(numPalabras, dicCompleto, dicPalabras, cantApariciones,
        cantAparicionesPalabras,categorias, "PALABRAS", k);
    ordenarRankingGeneral(dicCompleto, cantApariciones, categorias, numElementos);

    imprimirEncabezadoRankingGeneral(salida);
    for (int i=0; i<numElementos; i++) {
        if (cantApariciones[i]>0) {
            salida << left << setw(6) << i+1 << setw(15) << dicCompleto[i] << setw(13) << categorias[i] << right
            << setw(6) << cantApariciones[i] << endl;
        }
    }
}


//FUNCIONES PARA LIBERAR RECURSOS:

void liberarMemoria(char** dicOtros, char** dicPalabras, char** dicDesconocidas, int numOtros, int numPalabras,
    int numDesconocidas) {
    for (int i=0; i<numOtros; i++) delete [] dicOtros[i];
    for (int i=0; i<numPalabras; i++) delete [] dicPalabras[i];
    for (int i=0; i<numDesconocidas; i++) delete [] dicDesconocidas[i];
}
