//
// Created by PC on 24/10/2026.
//

#include "Funciones.h"


//FUNCIONES PROPIAS:

void pasarAMayusculas(char *cadena) {
    for (int i=0; cadena[i]; i++) {
        if ('a'<=cadena[i] and cadena[i]<='z') {
            cadena[i]-=32;
        }
    }
}

int mi_strlen(const char *cadena) {
    int cantCar;
    for (cantCar=0; cadena[cantCar]!='\0'; cantCar++) {}
    return cantCar;
}

void mi_strcpy(char* destino, const char* fuente) {
    int i=0;
    while (true) {
        destino[i]=fuente[i];
        if (fuente[i]==0) break;
        i++;
    }
}

void mi_strcat(char *cadena1, const char *cadena2) {
    int pos=mi_strlen(cadena1);
    mi_strcpy(&cadena1[pos], cadena2);
}

int mi_strcmp(const char *cadena1, const char *cadena2) {
    int i=0;
    while (cadena1[i]==cadena2[i]) {
        if (cadena1[i]==0) return 0;
        i++;
    }
    return cadena1[i]-cadena2[i];
}

int mi_atoi(const char *cadena) {
    int valor=0, i=0, digito;
    while (esEspacio(cadena[i])) i++;
    while (esDigito(cadena[i])) {
        digito=cadena[i]-'0';
        valor=valor*10+digito;
        i++;
    }
    return valor;
}


//FUNCIONES PARA VALIDAR DATO POR DATO:

bool esEspacio(char c) {
    return c==' ' or c=='\t' or c=='\n';
}

bool esDigito(char c) {
    return c>='0' and c<='9';
}

bool sonDigitos(const char *cadena, int posInicial, int cantCaracteres) {
    for (int i=posInicial; i<posInicial+cantCaracteres; i++) {
        if (!esDigito(cadena[i])) return false;
    }
    return true;
}

bool esMayuscula(char c) {
    return c>='A' and c<='Z';
}

bool sonMayusculas(const char *cadena, int posInicial, int cantCaracteres) {
    for (int i=posInicial; i<posInicial+cantCaracteres; i++) {
        if (!esMayuscula(cadena[i])) return false;
    }
    return true;
}

bool tieneFormatoDeFecha(const char *fecha) {
    bool diaCorrecto = sonDigitos(fecha,0,2) and fecha[2]=='-';
    bool mesCorrecto = sonDigitos(fecha,3,2) and fecha[5]=='-';
    bool anioCorrecto = sonDigitos(fecha,6,4);
    return diaCorrecto and mesCorrecto and anioCorrecto;
}

int diasDelMes(int mes, int anio) {
    if (mes==2) {
        if (esBisiesto(anio)) return 29;
        return 28;
    }
    if (mes==1 or mes==3 or mes==5 or mes==7 or mes==8 or mes==10 or mes==12) return 31;
    return 30;
}

bool esBisiesto(int anio) {
    if (anio%400==0) return true;
    if (anio%100==0) return false;
    if (anio%4==0) return true;
    return false;
    // return (anio%4==0 and anio%100!=0) or anio%400==0;
}


//FUNCIONES PARA VALIDAR EL ARCH DE DATOS O LLENAR ARREGLOS:

int validarDNI(const char *dni) {
    if (mi_strlen(dni)!=8) return MOTIVO_LONG_INCORRECTA;
    if (!sonDigitos(dni,0,8)) return MOTIVO_CARACTERES_DNI_INCORRECTOS;
    return MOTIVO_VALIDO;
}

int validarPlaca(const char *placa) {
    if (mi_strlen(placa)!=7) return MOTIVO_LONG_INCORRECTA;
    if (!sonMayusculas(placa,0,3) or placa[3]!='-' or
        !sonDigitos(placa, 4, 3)) return MOTIVO_FORMATO_PLACA_INCORRECTO;
    return MOTIVO_VALIDO;
}

int validarFecha(const char *fecha) {
    if (mi_strlen(fecha)!=10) return MOTIVO_LONG_INCORRECTA;
    if (!tieneFormatoDeFecha(fecha)) return MOTIVO_FORMATO_FECHA_INCORRECTO;

    //leemos los dias (transformando de texto a entero):
    int dia=mi_atoi(&fecha[0]);
    int mes=mi_atoi(&fecha[3]);
    int anio=mi_atoi(&fecha[6]);

    if (mes<1 or mes>12) return MOTIVO_MES_INCORRECTO;
    if (dia<1 or dia>diasDelMes(mes, anio)) return MOTIVO_DIA_INCORRECTO;
    return MOTIVO_VALIDO;
}

int validarRegistro(const char *valor, const char *tipo) {
    if (mi_strcmp(tipo, "DNI") == 0) { //si el resto con DNI es cero
        return validarDNI(valor);
    }
    if (mi_strcmp(tipo, "PLACA") == 0) { //si el resto con PLACA es cero
        return validarPlaca(valor);
    }
    if (mi_strcmp(tipo, "FECHA") == 0) { //si el resto con FECHA es cero
        return validarFecha(valor);
    }
    return MOTIVO_TIPO_INCORRECTO; //si no entra a ningun if, entonces el tipo no es el buscado
}

void llenarMotivo(int valorMotivo, char *cadenaMotivo) {
    if (valorMotivo == MOTIVO_VALIDO) mi_strcpy(cadenaMotivo, "-");
    else if (valorMotivo == MOTIVO_LONG_INCORRECTA) mi_strcpy(cadenaMotivo, "Longitud incorrecta");
    else if (valorMotivo == MOTIVO_FORMATO_PLACA_INCORRECTO) mi_strcpy(cadenaMotivo, "No cumple el formato XYZ-123");
    else if (valorMotivo == MOTIVO_DIA_INCORRECTO) mi_strcpy(cadenaMotivo, "El dia no existe en ese mes");
    else if (valorMotivo == MOTIVO_CARACTERES_DNI_INCORRECTOS) mi_strcpy(cadenaMotivo, "Contiene caracteres no numericos");
    else if (valorMotivo == MOTIVO_FORMATO_FECHA_INCORRECTO) mi_strcpy(cadenaMotivo, "No cumple el formato dd-mm-aaaa");
    else if (valorMotivo == MOTIVO_TIPO_INCORRECTO) mi_strcpy(cadenaMotivo, "Tipo de dato desconocido");
    else if (valorMotivo == MOTIVO_MES_INCORRECTO) mi_strcpy(cadenaMotivo, "Mes fuera de rango (01-12)");
}

int obtenerTipoDeDato(const char *tipo) {
    if (mi_strcmp(tipo, "DNI")==0) {
        return TIPO_DNI;
    }
    if (mi_strcmp(tipo, "PLACA")==0) {
        return TIPO_PLACA;
    }
    if (mi_strcmp(tipo, "FECHA")==0) {
        return TIPO_FECHA;
    }
    return TIPO_INCORRECTO;
}

void llenarNombreTipoDeDato(int tipoDeDato, char *nombreTipoDeDato) {
    if (tipoDeDato==TIPO_DNI) mi_strcpy(nombreTipoDeDato, "DNI");
    else if (tipoDeDato==TIPO_PLACA) mi_strcpy(nombreTipoDeDato, "PLACA");
    else if (tipoDeDato==TIPO_FECHA) mi_strcpy(nombreTipoDeDato, "FECHA");
    else if (tipoDeDato==TIPO_INCORRECTO) mi_strcpy(nombreTipoDeDato, "OTRO");
}


//FUNCIONES PARA IMPRIMIR:

void imprimirEncabezado1(ofstream &salida) {
    salida << "REPORTE DE VALIDACION DE REGISTROS" << endl;
    imprimirSeparador(salida,'-', 34);
    salida << left << setw(5) << "NRO" << setw(15) << "VALOR" << setw(10) << "TIPO" << setw(15) << "ESTADO"
            << "MOTIVO" << endl;
}

void imprimirSeparador(ofstream &salida, char c, int n) {
    for (int i=0; i<n; i++) salida << c;
    salida << endl;
}

void imprimirRegistro(ofstream &salida, int numRegistros, int valorMotivo, char *cadenaMotivo, const char *valor,
    const char *tipo) {
    salida << left << setw(5) << numRegistros << setw(15) << valor << setw(10) << tipo;
    if (valorMotivo==MOTIVO_VALIDO) salida << setw(15) << "VALIDO";
    else salida << setw(15) << "INVALIDO";
    salida << cadenaMotivo << endl;
}

void imprimirEncabezado2(ofstream &salida) {
    salida << "RESUMEN POR TIPO" << endl;
    imprimirSeparador(salida,'-', 16);
    salida << left << setw(10) << "TIPO" << right << setw(10) << "VALIDOS" << setw(12) << "INVALIDOS"
            << setw(8) << "TOTAL" << endl;
}


//FUNCIONES PARA ABRIR O GENERAR REPORTES:

void abrirArchivoLectura(const char* nombreArchivo, ifstream& archivo) {
    archivo.open(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }
}

void abrirArchivoEscritura(const char* nombreArchivo, ofstream& archivo) {
    archivo.open(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }
}

void validarYGenerarReporte(const char* archEntrada, const char* archSalida, int *cantValidos, int *cantInvalidos,
    int &numRegistros) {
    ifstream entrada;
    ofstream salida;
    abrirArchivoLectura(archEntrada, entrada);
    abrirArchivoEscritura(archSalida, salida);

    //en registros.csv se ve lo siguiente:
    // VALOR    TIPO
    // 45879632,DNI
    // ABC-123,PLACA
    // 24-10-2026,FECHA

    char valor[CAPACIDAD_VALOR], tipo[CAPACIDAD_TIPO], cadenaMotivo[CAPACIDAD_MOTIVO]; //se declaran los arreglos
    int valorMotivo, tipoDeValor;
    numRegistros=0;

    imprimirEncabezado1(salida);
    while (true) {
        //lectura de datos:
        entrada.getline(valor, 100, ','); //se llena la cadena valor
        entrada.getline(tipo, 100); //se llena la cadena tipo

        pasarAMayusculas(tipo); //se pasa a mayusculas el nombre del tipo
        if (entrada.eof()) break;
        numRegistros++;

        //validacion de datos:
        valorMotivo=validarRegistro(valor,tipo);
        llenarMotivo(valorMotivo, cadenaMotivo);
        imprimirRegistro(salida, numRegistros, valorMotivo, cadenaMotivo, valor, tipo);

        //PROCEDEMOS A RELLENAR LOS ARREGLOS SEGUN EL TIPO DE VALOR (DNI, PLACA, FECHA)
        tipoDeValor=obtenerTipoDeDato(tipo);
        if (valorMotivo==MOTIVO_VALIDO) cantValidos[tipoDeValor]++;
        else cantInvalidos[tipoDeValor]++;
    }
}

void generarResumen(const char *archSalida, int *cantValidos, int *cantInvalidos, int numRegistros) {
    ofstream salida;
    abrirArchivoEscritura(archSalida, salida);

    char nombreTipoDeDato[CAPACIDAD_TIPO];

    imprimirEncabezado2(salida);
    for (int i=0; i<4; i++) {
        llenarNombreTipoDeDato(i, nombreTipoDeDato);
        salida << left << setw(10) << nombreTipoDeDato << right << setw(10) << cantValidos[i] << setw(12)
                << cantInvalidos[i] << setw(8) << cantValidos[i]+cantInvalidos[i] << endl;
    }
    imprimirSeparador(salida, '-', 40);
    salida << left << setw(30) << "Registros procesados: " << right << setw(10) << numRegistros << endl;
}
