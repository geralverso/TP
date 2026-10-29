//
// Created by PC on 28/10/2026.
//

#include "FuncionesAuxiliares.h"

//FUNCIONES PROPIAS:

int mi_strlen(const char* cad) {
    int nCar;
    for (nCar = 0; cad[nCar]; nCar++) {}
    return nCar;
}

bool esDigito(char c) {
    return c>='0' and c<='9';
}

bool esMayuscula(char c) {
    return c>='A' and c<='Z';
}

bool esMinuscula(char c) {
    return c>='a' and c<='z';
}

bool esSimbolo(char c) {
    return c=='!' or c=='@' or c=='#' or c=='$' or c=='%' or c=='&' or c=='*';
}

bool esComilla(char c) {
    return c=='"' or c=='\'';
}

bool corresponde(const char *cad1, const char *cad2) {
    for (int i=0; cad2[i]; i++) {
        if (cad1[i]!=cad2[i]) return false;
    }
    return true;
}

char* mi_strstr(char *cad1, const char *cad2) {
    for (int i=0; cad1[i]; i++) {
        if (cad1[i]==cad2[0]) {
            if (corresponde(&cad1[i], cad2)) {
                return &cad1[i];
            }
        }
    }
    return nullptr;
}


//FUNCIONES PARA ABRIR ARCHIVOS:

void abrirArchLectura(const char* nombreArchivo, ifstream& archivo) {
    archivo.open(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo" << endl;
        exit(1);
    }
}

void abrirArchEscritura(const char* nombreArchivo, ofstream& archivo) {
    archivo.open(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo" << endl;
        exit(1);
    }
}


//FUNCIONES PARA CARGAR:

void acumularEImprimirValidos(ofstream &salida, int valorDelDato, int &cantValidosTelf, int &cantValidosCorreo,
    int &cantValidosContra, const char *nombreCompleto, const char *dato) {
    if (valorDelDato==TELEFONO_VALIDO) {
        cantValidosTelf++;
        salida << left << setw(50) << nombreCompleto << setw(20) << "Telefono:" << dato << endl;
    }
    if (valorDelDato==CORREO_VALIDO) {
        cantValidosCorreo++;
        salida << left << setw(50) << nombreCompleto << setw(20) << "Correo:" << dato << endl;
    }
    if (valorDelDato==CONTRASENA_VALIDA) {
        cantValidosContra++;
        salida << left << setw(50) << nombreCompleto << setw(20) << "Contraseña:" << dato << endl;
    }
}

void acumularResultados(int valorDelDato, int &cantSinArroba, int &cantConEspacio, int &cantErrorUsuario,
    int &cantErrorDominio, int &cantOtrosCar, int &cantLongIncorrectaTelf, int &cantSinMayus, int &cantSinMinus,
    int &cantSinDigito, int &cantSinSimbolo, int &cantConComillas, int &cantConFecha, int &cantLongIncorrectaContra) {
    if (valorDelDato==SIN_ARROBA) cantSinArroba++;
    if (valorDelDato==CON_ESPACIO) cantConEspacio++;
    if (valorDelDato==ERRORES_CON_USUARIO) cantErrorUsuario++;
    if (valorDelDato==ERRORES_CON_DOMINIO) cantErrorDominio++;
    if (valorDelDato==OTROS_CARACTERES) cantOtrosCar++;
    if (valorDelDato==LONGITUD_EQUIVOCADA_TELF) cantLongIncorrectaTelf++;
    if (valorDelDato==SIN_MAYUSCULA) cantSinMayus++;
    if (valorDelDato==SIN_MINUSCULA) cantSinMinus++;
    if (valorDelDato==SIN_DIGITO) cantSinDigito++;
    if (valorDelDato==SIN_SIMBOLO) cantSinSimbolo++;
    if (valorDelDato==CON_COMILLAS) cantConComillas++;
    if (valorDelDato==CON_FECHA) cantConFecha++;
    if (valorDelDato==LONGITUD_EQUIVOCADA_CONTRA) cantLongIncorrectaContra++;
}

void armarResultadosTelf(int* resultadosTelefono, int cantTelf, int cantValidosTelf, int cantOtrosCar,
    int cantLongIncorrectaTelf) {
    resultadosTelefono[0]=cantTelf;
    resultadosTelefono[1]=cantValidosTelf;
    resultadosTelefono[2]=cantOtrosCar;
    resultadosTelefono[3]=cantLongIncorrectaTelf;
    resultadosTelefono[4]='\0';
}

void armarResultadosCorreo(int* resultadosCorreo, int cantCorreo, int cantValidosCorreo, int cantSinArroba,
    int cantConEspacio, int cantErrorUsuario, int cantErrorDominio) {
    resultadosCorreo[0]=cantCorreo;
    resultadosCorreo[1]=cantValidosCorreo;
    resultadosCorreo[2]=cantSinArroba;
    resultadosCorreo[3]=cantConEspacio;
    resultadosCorreo[4]=cantErrorUsuario;
    resultadosCorreo[5]=cantErrorDominio;
    resultadosCorreo[6]='\0';
}

void armarResultadosContrasena(int* resultadosContrasena, int cantContrasena, int cantValidosContra,
    int cantLongIncorrectaContra, int cantSinMayus, int cantSinMinus, int cantSinDigito, int cantSinSimbolo,
    int cantConComillas, int cantConFecha) {
    resultadosContrasena[0]=cantContrasena;
    resultadosContrasena[1]=cantValidosContra;
    resultadosContrasena[2]=cantLongIncorrectaContra;
    resultadosContrasena[3]=cantSinMayus;
    resultadosContrasena[4]=cantSinMinus;
    resultadosContrasena[5]=cantSinDigito;
    resultadosContrasena[6]=cantSinSimbolo;
    resultadosContrasena[7]=cantConComillas;
    resultadosContrasena[8]=cantConFecha;
    resultadosContrasena[9]='\0';
}

void cargarYValidarDatos(const char *nombreArchivo1, const char *nombreArchivo2, int *resultadosTelefono,
    int *resultadosCorreo, int *resultadosContrasena) {
    ifstream entrada; abrirArchLectura(nombreArchivo1, entrada);
    ofstream salida; abrirArchEscritura(nombreArchivo2, salida);

    char nombreCompleto[CAP_NOMBRE_COMPLETO], fechaNacimiento[CAP_FECHA_NACIMIENTO];
    char tipoDeDato,c, dato[CAP_DATO];
    int valorDelDato;
    int cantTelf=0, cantValidosTelf=0, cantOtrosCar=0, cantLongIncorrectaTelf=0;
    int cantCorreo=0, cantValidosCorreo=0, cantSinArroba=0, cantConEspacio=0, cantErrorUsuario=0, cantErrorDominio=0;
    int cantContrasena=0, cantValidosContra=0, cantLongIncorrectaContra=0, cantSinMayus=0, cantSinMinus=0;
    int cantSinDigito=0, cantSinSimbolo=0, cantConComillas=0, cantConFecha=0;

    while (entrada.getline(nombreCompleto, CAP_NOMBRE_COMPLETO, ',')) {
        entrada.getline(fechaNacimiento, CAP_FECHA_NACIMIENTO, ',');
        entrada >> tipoDeDato >> c;
        entrada.getline(dato, CAP_DATO);

        valorDelDato=validarDato(tipoDeDato, dato, fechaNacimiento, cantTelf, cantCorreo, cantContrasena);
        acumularEImprimirValidos(salida, valorDelDato, cantValidosTelf, cantValidosCorreo, cantValidosContra,
            nombreCompleto, dato);
        acumularResultados(valorDelDato, cantSinArroba, cantConEspacio, cantErrorUsuario, cantErrorDominio,
            cantOtrosCar, cantLongIncorrectaTelf, cantSinMayus, cantSinMinus, cantSinDigito, cantSinSimbolo,
            cantConComillas, cantConFecha,cantLongIncorrectaContra);
    }

    armarResultadosTelf(resultadosTelefono, cantTelf, cantValidosTelf, cantOtrosCar, cantLongIncorrectaTelf);
    armarResultadosCorreo(resultadosCorreo, cantCorreo, cantValidosCorreo, cantSinArroba, cantConEspacio, cantErrorUsuario,
        cantErrorDominio);
    armarResultadosContrasena(resultadosContrasena, cantContrasena, cantValidosContra, cantLongIncorrectaContra, cantSinMayus,
        cantSinMinus, cantSinDigito, cantSinSimbolo, cantConComillas, cantConFecha);
}


//FUNCIONES PARA VALIDAR:

void armarDiaYMes(char *diaYMes, const char *fecha) {
    diaYMes[0]=fecha[0];
    diaYMes[1]=fecha[1];
    diaYMes[2]=fecha[3];
    diaYMes[3]=fecha[4];
    diaYMes[4]='\0';
}

void armarMesYAnio(char *mesYAnio, const char *fecha) {
    mesYAnio[0]=fecha[3];
    mesYAnio[1]=fecha[4];
    mesYAnio[2]=fecha[6];
    mesYAnio[3]=fecha[7];
    mesYAnio[4]=fecha[8];
    mesYAnio[5]=fecha[9];
    mesYAnio[6]='\0';
}

void armarMesYAnioCorto(char *mesYAnioCorto, const char *fecha) {
    mesYAnioCorto[0]=fecha[3];
    mesYAnioCorto[1]=fecha[4];
    mesYAnioCorto[2]=fecha[8];
    mesYAnioCorto[3]=fecha[9];
    mesYAnioCorto[4]='\0';
}

int validarTelefono(const char* cad) {
    int longitud=mi_strlen(cad);

    //1ER CASO:
    if (cad[0]=='+') { //si empieza con +, luego debe venir el codigo del pais (1-3 digitos) y el telefono (9 digitos)
        //caso codigoPais con 1 digito (minimo): +1 (2 digitos) y telefono (9 digitos) --> 11 digitos minimo
        //caso codigoPais con 3 digitos (maximo): +899 (4 digitos) y telefono (9 digitos) --> 13 digitos maximo

        if (11>longitud or longitud>13) return LONGITUD_EQUIVOCADA_TELF;
        for (int i=1; cad[i]; i++) {
            if (!esDigito(cad[i])) return OTROS_CARACTERES;
        }

        int cantDigitosCodigoPais=longitud-9-1; //9 por el telefono y 1 por el '+'
        int codigoPais=0;
        for (int i=1; i<=cantDigitosCodigoPais; i++) {
            codigoPais=codigoPais*10+(cad[i]-'0');
        }
        if (codigoPais<1 or codigoPais>899) return OTROS_CARACTERES;

        return TELEFONO_VALIDO;
    }
    else { //2DO CASO: NUMERO NORMAL
        for (int i=0; cad[i]; i++) {
            if (!esDigito(cad[i])) return OTROS_CARACTERES;
        }
        if (longitud!=9) return LONGITUD_EQUIVOCADA_TELF;
        return TELEFONO_VALIDO;
    }
}

int validarCorreo(const char* cad) {
    int cantArrobas=0, posArroba=-1, cantPuntosLuegoDelArroba=0, posUltimoPunto=-1;
    int longitud=mi_strlen(cad);

    for (int i=0; cad[i]; i++) { //BUCLE QUE ANALIZA TODO EL CORREO
        if (cad[i]==' ') return CON_ESPACIO;
        if (cad[i]=='@') {
            cantArrobas++, posArroba=i;
            if (cantArrobas>1 or posArroba==0) return ERRORES_CON_USUARIO; //si hay más de 1 arroba lo considero como
        }                                                                       //error en el usuario
        else if (cantArrobas==1 and cad[i]=='.') {
            cantPuntosLuegoDelArroba++, posUltimoPunto=i;
        }
    }

    if (cantArrobas==0) return SIN_ARROBA;
    if (cantPuntosLuegoDelArroba==0 or posUltimoPunto==posArroba+1 or posUltimoPunto==longitud-1) return ERRORES_CON_DOMINIO;
    for (int i=posArroba+1; cad[i]; i++) { //BUCLE QUE ANALIZA TODO EL DOMINIO
        if (cad[i]=='.' and cad[i+1]=='.') return ERRORES_CON_DOMINIO;
    }
    if (cantArrobas==1) return CORREO_VALIDO;
    return CORREO_VALIDO;
}

int validarContrasena(char* cad, const char* fecha) {
    int longitud=mi_strlen(cad);
    if (longitud<8) return LONGITUD_EQUIVOCADA_CONTRA;

    char diaYMes[CAP_COMBINACION_FECHA], mesYAnio[CAP_COMBINACION_FECHA], mesYAnioCorto[CAP_COMBINACION_FECHA];
    armarDiaYMes(diaYMes, fecha);
    armarMesYAnio(mesYAnio, fecha);
    armarMesYAnioCorto(mesYAnioCorto, fecha);

    int cantMayus=0, cantMinus=0, cantDigitos=0, cantSimbolos=0, cantComillas=0;
    for (int i=0; cad[i]; i++) {
        if (esMayuscula(cad[i])) cantMayus++;
        if (esMinuscula(cad[i])) cantMinus++;
        if (esDigito(cad[i])) cantDigitos++;
        if (esSimbolo(cad[i])) cantSimbolos++;
        if (esComilla(cad[i])) cantComillas++;
    }
                    // mi_strstr(cadenaAnalizada, cadena que se busca)
    char* pt_diaYMes=mi_strstr(cad, diaYMes);
    char* pt_mesYAnio=mi_strstr(cad, mesYAnio);
    char* pt_mesYAnioCorto=mi_strstr(cad, mesYAnioCorto);
    if (pt_diaYMes!=nullptr or pt_mesYAnio!=nullptr or pt_mesYAnioCorto!=nullptr) return CON_FECHA;
    if (cantMayus==0) return SIN_MAYUSCULA;
    if (cantMinus==0) return SIN_MINUSCULA;
    if (cantDigitos==0) return SIN_DIGITO;
    if (cantSimbolos==0) return SIN_SIMBOLO;
    if (cantComillas>0) return CON_COMILLAS;

    return CONTRASENA_VALIDA;
}

int validarDato(char tipoDeDato, char *dato, const char* fecha, int &cantTelf, int &cantCorreo, int &cantContrasena) {
    if (tipoDeDato=='C') {
        cantCorreo++;
        return validarCorreo(dato);
    }
    if (tipoDeDato=='T') {
        cantTelf++;
        return validarTelefono(dato);
    }
    if (tipoDeDato=='P') {
        cantContrasena++;
        return validarContrasena(dato, fecha);
    }
    return TIPO_DE_DATO_INVALIDO;
}


//FUNCIONES PARA IMPRIMIR:

void imprimirSeccionTelefono(ofstream &salida, const int *resultadosTelefono) {
    salida << "Teléfonos" << endl;
    salida << left << setw(40) << "Evaluados:" << right << setw(10) << resultadosTelefono[0] << endl;
    salida << left << setw(41) << "Válidos:" << right << setw(10) << resultadosTelefono[1] << endl;
    salida << "Inválidos por criterio:" << endl;
    salida << left << setw(40) << "   a. Otros caracteres" << right << setw(10) << resultadosTelefono[2] << endl;
    salida << left << setw(40) << "   b. Longitud equivocada" << right << setw(10) << resultadosTelefono[3] << endl;
}

void imprimirSeccionCorreo(ofstream &salida, const int *resultadosCorreo) {
    salida << "\nCorreos" << endl;
    salida << left << setw(40) << "Evaluados:" << right << setw(10) << resultadosCorreo[0] << endl;
    salida << left << setw(41) << "Válidos:" << right << setw(10) << resultadosCorreo[1] << endl;
    salida << "Inválidos por criterio:" << endl;
    salida << left << setw(40) << "   a. Sin arroba" << right << setw(10) << resultadosCorreo[2] << endl;
    salida << left << setw(40) << "   b. Con espacio" << right << setw(10) << resultadosCorreo[3] << endl;
    salida << left << setw(40) << "   c. Errores con usuario" << right << setw(10) << resultadosCorreo[4] << endl;
    salida << left << setw(40) << "   d. Errores con dominio" << right << setw(10) << resultadosCorreo[5] << endl;
}

void imprimirSeccionContrasena(ofstream &salida, const int *resultadosContrasena) {
    salida << "\nContraseñas" << endl;
    salida << left << setw(40) << "Evaluados:" << right << setw(10) << resultadosContrasena[0] << endl;
    salida << left << setw(41) << "Válidos:" << right << setw(10) << resultadosContrasena[1] << endl;
    salida << "Inválidas:" << endl;
    salida << left << setw(40) << "   a. Longitud equivocada" << right << setw(10) << resultadosContrasena[2] << endl;
    salida << left << setw(41) << "   b. Sin mayúscula" << right << setw(10) << resultadosContrasena[3] << endl;
    salida << left << setw(41) << "   c. Sin minúscula" << right << setw(10) << resultadosContrasena[4] << endl;
    salida << left << setw(41) << "   d. Sin dígito" << right << setw(10) << resultadosContrasena[5] << endl;
    salida << left << setw(41) << "   e. Sin símbolo" << right << setw(10) << resultadosContrasena[6] << endl;
    salida << left << setw(40) << "   f. Con comillas" << right << setw(10) << resultadosContrasena[7] << endl;
    salida << left << setw(40) << "   g. Con fecha" << right << setw(10) << resultadosContrasena[8] << endl;
}


//FUNCIONES PARA GENERAR REPORTES:

void generarReporte(const char *nombreArchivo, const int *resultadosTelefono, const int *resultadosCorreo,
    const int *resultadosContrasena) {
    ofstream salida;
    abrirArchEscritura(nombreArchivo, salida);
    imprimirSeccionTelefono(salida, resultadosTelefono);
    imprimirSeccionCorreo(salida, resultadosCorreo);
    imprimirSeccionContrasena(salida, resultadosContrasena);
}
