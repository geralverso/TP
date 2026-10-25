//
// Created by PC on 24/10/2026.
//

#ifndef EJERCICIO01_RESUELTO_POR_MI_FUNCIONES_H
#define EJERCICIO01_RESUELTO_POR_MI_FUNCIONES_H

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

#define CAPACIDAD_REGISTROS 100
#define CAPACIDAD_VALOR 50
#define CAPACIDAD_TIPO 20
#define CAPACIDAD_MOTIVO 80

//VALORES POR EL MOTIVO:
#define MOTIVO_LONG_INCORRECTA 0
#define MOTIVO_CARACTERES_DNI_INCORRECTOS 1
#define MOTIVO_FORMATO_PLACA_INCORRECTO 2
#define MOTIVO_FORMATO_FECHA_INCORRECTO 3
#define MOTIVO_MES_INCORRECTO 4
#define MOTIVO_DIA_INCORRECTO 5
#define MOTIVO_TIPO_INCORRECTO 6
#define MOTIVO_VALIDO 7

//VALORES POR EL TIPO DE VALOR:
#define TIPO_DNI 0
#define TIPO_PLACA 1
#define TIPO_FECHA 2
#define TIPO_INCORRECTO 3


//FUNCIONES PROPIAS:
void pasarAMayusculas(char* cadena);
int mi_strlen(const char* cadena);
void mi_strcpy(char* destino, const char* fuente);
void mi_strcat(char *cadena1, const char *cadena2);
int mi_strcmp(const char* cadena1, const char* cadena2);
int mi_atoi(const char* cadena);

//FUNCIONES PARA VALIDAR DATO POR DATO:
bool esEspacio(char c);
bool esDigito(char c);
bool sonDigitos(const char *cadena, int posInicial, int cantCaracteres);
bool esMayuscula(char c);
bool sonMayusculas(const char *cadena, int posInicial, int cantCaracteres);
bool tieneFormatoDeFecha(const char* fecha);
int diasDelMes(int mes, int anio);
bool esBisiesto(int anio);

//FUNCIONES PARA VALIDAR EL ARCH DE DATOS O LLENAR ARREGLOS:
int validarDNI(const char* dni);
int validarPlaca(const char *placa);
int validarFecha(const char *fecha);
int validarRegistro(const char* valor, const char* tipo);
void llenarMotivo(int valorMotivo, char* motivo);
int obtenerTipoDeDato(const char* tipo);
void llenarNombreTipoDeDato(int tipoDeDato, char* nombreTipoDeDato);

//FUNCIONES PARA IMPRIMIR:
void imprimirEncabezado1(ofstream &salida);
void imprimirSeparador(ofstream &salida, char c, int n);
void imprimirRegistro(ofstream &salida, int numRegistros, int valorMotivo, char *cadenaMotivo, const char *valor,
    const char *tipo);
void imprimirEncabezado2(ofstream &salida);

//FUNCIONES PARA ABRIR O GENERAR REPORTES:
void abrirArchivoLectura(const char* nombreArchivo, ifstream& archivo);
void abrirArchivoEscritura(const char* nombreArchivo, ofstream& archivo);
void validarYGenerarReporte(const char* archEntrada, const char* archSalida, int *cantValidos, int *cantInvalidos,
    int &numRegistros);
void generarResumen(const char* archSalida, int *cantValidos, int *cantInvalidos, int numRegistros);


#endif //EJERCICIO01_RESUELTO_POR_MI_FUNCIONES_H
