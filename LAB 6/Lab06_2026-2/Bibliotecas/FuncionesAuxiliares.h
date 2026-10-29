//
// Created by PC on 28/10/2026.
//

#ifndef LAB06_2026_2_FUNCIONESAUXILIARES_H
#define LAB06_2026_2_FUNCIONESAUXILIARES_H

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

#define CAP_NOMBRE_COMPLETO 50
#define CAP_FECHA_NACIMIENTO 30
#define CAP_DATO 60
#define CAP_COMBINACION_FECHA 20

#define CAP_RESULTADOS_TELEFONO 4
#define CAP_RESULTADOS_CORREO 6
#define CAP_RESULTADOS_CONTRASENA 9

#define TIPO_DE_DATO_INVALIDO 0
#define TELEFONO_VALIDO 1
#define CORREO_VALIDO 2
#define CONTRASENA_VALIDA 3

//ANALISIS DE CORREO
#define SIN_ARROBA 4
#define CON_ESPACIO 5
#define ERRORES_CON_USUARIO 6
#define ERRORES_CON_DOMINIO 7

//ANALISIS DE TELEFONO
#define OTROS_CARACTERES 8
#define LONGITUD_EQUIVOCADA_TELF 9

//ANALISIS DE CONTRASEÑA
#define SIN_MAYUSCULA 10
#define SIN_MINUSCULA 11
#define SIN_DIGITO 12
#define SIN_SIMBOLO 13
#define CON_COMILLAS 14
#define CON_FECHA 15
#define LONGITUD_EQUIVOCADA_CONTRA 16

//FUNCIONES PROPIAS:
int mi_strlen(const char* cad);
bool esDigito(char c);
bool esMayuscula(char c);
bool esMinuscula(char c);
bool esSimbolo(char c);
bool esComilla(char c);
bool corresponde(const char* cad1, const char* cad2);
char* mi_strstr(char* cad1, const char* cad2);

//FUNCIONES PARA ABRIR ARCHIVOS:
void abrirArchLectura(const char* nombreArchivo, ifstream& archivo);
void abrirArchEscritura(const char* nombreArchivo, ofstream& archivo);

//FUNCIONES PARA CARGAR:
void acumularEImprimirValidos(ofstream &salida, int valorDelDato, int &cantValidosTelf, int &cantValidosCorreo,
    int &cantValidosContra, const char* nombreCompleto, const char* dato);
void acumularResultados(int valorDelDato, int &cantSinArroba, int &cantConEspacio, int &cantErrorUsuario,
    int &cantErrorDominio, int &cantOtrosCar, int &cantLongIncorrectaTelf, int &cantSinMayus, int &cantSinMinus,
    int &cantSinDigito, int &cantSinSimbolo, int &cantConComillas, int &cantConFecha, int &cantLongIncorrectaContra);
void armarResultadosTelf(int* resultadosTelefono, int cantTelf, int cantValidosTelf, int cantOtrosCar,
        int cantLongIncorrectaTelf);
void armarResultadosCorreo(int* resultadosCorreo, int cantCorreo, int cantValidosCorreo, int cantSinArroba,
    int cantConEspacio, int cantErrorUsuario, int cantErrorDominio);
void armarResultadosContrasena(int* resultadosContrasena, int cantContrasena, int cantValidosContra,
    int cantLongIncorrectaContra, int cantSinMayus, int cantSinMinus, int cantSinDigito, int cantSinSimbolo,
    int cantConComillas, int cantConFecha);
void cargarYValidarDatos(const char *nombreArchivo1, const char *nombreArchivo2, int *resultadosTelefono,
    int *resultadosCorreo, int *resultadosContrasena);

//FUNCIONES PARA VALIDAR:
void armarDiaYMes(char *diaYMes, const char *fecha);
void armarMesYAnio(char *diaYMes, const char *fecha);
void armarMesYAnioCorto(char *diaYMes, const char *fecha);
int validarTelefono(const char* cad);
int validarCorreo(const char* cad);
int validarContrasena(char* cad, const char* fecha);
int validarDato(char tipoDeDato, char *dato, const char* fecha, int &cantTelf, int &cantCorreo, int &cantContrasena);

//FUNCIONES PARA IMPRIMIR:
void imprimirSeccionTelefono(ofstream &salida, const int *resultadosTelefono);
void imprimirSeccionCorreo(ofstream &salida, const int *resultadosCorreo);
void imprimirSeccionContrasena(ofstream &salida, const int *resultadosContrasena);

//FUNCIONES PARA GENERAR REPORTES:
void generarReporte(const char *nombreArchivo, const int *resultadosTelefono, const int *resultadosCorreo,
    const int *resultadosContrasena);


#endif //LAB06_2026_2_FUNCIONESAUXILIARES_H
