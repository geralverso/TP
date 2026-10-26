//
// Created by PC on 25/10/2026.
//

#include "Funciones.h"


//FUNCIONES PROPIAS:

int mi_strlen(const char* cadena) {
    int nCar;
    for (nCar=0; cadena[nCar]!='\0'; nCar++){}
    return nCar;
}

void mi_strcpy(char* destino, const char* fuente) {
    int i=0;
    while (true) {
        destino[i] = fuente[i];
        if (fuente[i]==0) break;
        i++;
    }
}

void mi_strcat(char* cadena1, const char* cadena2) {
    int pos=mi_strlen(cadena1);
    mi_strcpy(&cadena1[pos], cadena2);
}

void pasarAMinusculas(char *cadena) {
    for (int i=0; cadena[i]!='\0'; i++) {
        if (cadena[i]>='A' && cadena[i]<='Z') {
            cadena[i]+=+32;
        }
    }
}

bool corresponde(const char *cadena1, const char *cadena2) {
    for (int i=0; cadena2[i]!='\0'; i++) {
        if (cadena1[i]!=cadena2[i]) return false; //retorna falso si son diferentes
    }
    return true;
}

char* mi_strstr(char *cadena1, const char *cadena2) {
    for (int i=0; cadena1[i]!='\0'; i++) {
        if (cadena1[i]==cadena2[0]) {
            if (corresponde(&cadena1[i], cadena2)) {
                return &cadena1[i];
            }
        }
    }
    return nullptr;
}

void reemplazar(char *texto, const char *cadenaBuscada, const char *cadenaReemplazada) {
    char cadenaAux[CAPACIDAD_TEXTO], *puntero;
    puntero=mi_strstr(texto, cadenaBuscada);
    if (puntero==nullptr) return;
    *puntero=0;
    mi_strcpy(cadenaAux, texto);
    mi_strcat(cadenaAux, cadenaReemplazada);
    mi_strcat(cadenaAux, &puntero[mi_strlen(cadenaBuscada)]);
    mi_strcpy(texto, cadenaAux);
}


//FUNCIONES PARA CARGAR:

void abrirArchLectura(const char* nombre, ifstream &archivo) {
    archivo.open(nombre);
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }
}

void cargarTexto(const char *nombre, char *texto) {
    ifstream entrada;
    abrirArchLectura(nombre, entrada);

    char lineaDelTexto[CAPACIDAD_POR_LINEA];
    while (true) {
        if (entrada.eof()) break;
        entrada.getline(lineaDelTexto, CAPACIDAD_POR_LINEA);
        mi_strcat(texto, lineaDelTexto);
        mi_strcat(texto, "\n"); //getline descarta el \n por eso se vuelve a poner
    }
}

void cargarStopWords(const char *nombre, char *stopWords) {
    ifstream entrada;
    abrirArchLectura(nombre, entrada);

    char palabra[CAPACIDAD_PALABRA]{};
    while (entrada >> palabra) {
        mi_strcat(stopWords, palabra);
        mi_strcat(stopWords, " "); //cada palabra queda entre espacios
    }
}


//FUNCIONES PARA NORMALIZAR TEXTO:
                                                            //cadena siempre es un arreglo sin elementos
bool extraerCadena(char *&cursor, const char *delimitador, char *cadena) {
    char* pt;
    char guardado;
    cadena[0]=0; //su primer elemento se inicializa en cero
    if (*cursor==0) return false; //ya no quedan datos

    pt=mi_strstr(cursor, delimitador);
    if (pt==nullptr){
        mi_strcpy(cadena, cursor);
        cursor=&cursor[mi_strlen(cursor)]; //actualiza su direccion de memoria a la de su ultimo elemento
        return true;
    }

    guardado=*pt; //guarda el 1er caracter del delimitador
    *pt=0; //la cadena se corta luego
    mi_strcpy(cadena, cursor); //copia el tramo
    *pt=guardado; //restaura la cadena original
    cursor=&pt[mi_strlen(delimitador)]; //salta el delimitador
    return true;
}

void reemplazarEnTodoElTexto(char *texto, const char *cadenaBuscada, const char *cadenaReemplazada) {
    char* puntero=mi_strstr(texto, cadenaBuscada);
    while (puntero!=nullptr) {
        reemplazar(puntero, cadenaBuscada, cadenaReemplazada); //lo que se mueve es el puntero a traves del texto
        puntero=mi_strstr(&puntero[mi_strlen(cadenaReemplazada)], cadenaBuscada);
    }
}

void aplicarEquivalencia(char *texto, char *equivalencia) {
    char palabraBuscada[CAPACIDAD_POR_LINEA], palabraDeReemplazo[CAPACIDAD_PALABRA];
    char* cursor=equivalencia;

    //linea con formato palabraBuscada|palabraDeReemplazo
    extraerCadena(cursor, "|", palabraBuscada);
    extraerCadena(cursor, "|", palabraDeReemplazo);
    reemplazarEnTodoElTexto(texto, palabraBuscada, palabraDeReemplazo);
}

void aplicamosTodasLasEquivalencias(char* texto, char* equivalencias) {
    char equivalencia[CAPACIDAD_POR_LINEA];
    char* cursor = equivalencias; //cursor es un puntero que señala la direccion del 1er elemento de equivalencias

    while (extraerCadena(cursor, "\n", equivalencia)==true) {
        aplicarEquivalencia(texto, equivalencia);
    }
}

bool esMinuscula(char c) {
    return c>='a' and c<='z';
}

bool esDigito(char c) {
    return c>='0' and c<='9';
}

bool esCaracterValido(char c) {
    return esMinuscula(c) or esDigito(c) or c==' ' or c=='\n';
}

void quitarSignos(char *texto) {
    for (int i=0; texto[i]!='\0'; i++) {
        if (!esCaracterValido(texto[i])) {
            texto[i]=' ';
        }
    }
}

bool esStopWord(const char *palabra, char* stopWords) {
    char patron[CAPACIDAD_PALABRA];
    mi_strcpy(patron, ""); //se asigna posteriormente en la cadena vacia
    mi_strcat(patron, palabra);
    mi_strcat(patron, " ");
    return mi_strstr(stopWords, patron)!=nullptr;
}

void agregarPalabra(char *textoFinal, const char *palabra) {
    int longitud=mi_strlen(textoFinal);
    if (longitud>0 and textoFinal[longitud-1]!='\n') {
        mi_strcat(textoFinal, " ");
    }
    mi_strcat(textoFinal, palabra);
}

void filtrarLinea(char *linea, char *stopWords, char *textoFinal) {
    char palabra[CAPACIDAD_PALABRA];
    char* cursor=linea;
    while (extraerCadena(cursor, " ", palabra)==true) {
        if (!esStopWord(palabra, stopWords)) {
            if (palabra[0]!=0) agregarPalabra(textoFinal, palabra);
        }
    }
}

void quitarStopWords(char *texto, char *stopWords) {
    char textoFinal[CAPACIDAD_TEXTO], linea[CAPACIDAD_POR_LINEA];
    char* cursor=texto;
    textoFinal[0]=0; //se inicializa en 0

    while (extraerCadena(cursor, "\n", linea)==true) {
        filtrarLinea(linea, stopWords, textoFinal);
        mi_strcat(textoFinal, "\n");
    }
    mi_strcpy(texto, textoFinal); //se actualiza el texto
}

void normalizarTexto(char *texto, char *equivalencias, char *stopWords) {
    aplicamosTodasLasEquivalencias(texto, equivalencias); //1. aplicamos las equivalencias:
    pasarAMinusculas(texto); //2. pasar a minusculas todo:
    quitarSignos(texto); //3. eliminamos los simbolos extraños (#, ¡, !, @, etc ...):
    quitarStopWords(texto, stopWords); //4. eliminamos los stop words:
}


//FUNCIONES PARA GENERAR REPORTES:

void abrirArchEscritura(const char* nombre, ofstream &archivo) {
    archivo.open(nombre);
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }
}

void generarTextoNormalizado(const char *nombre, const char *texto) {
    ofstream salida;
    abrirArchEscritura(nombre, salida);
    salida << texto;
}
