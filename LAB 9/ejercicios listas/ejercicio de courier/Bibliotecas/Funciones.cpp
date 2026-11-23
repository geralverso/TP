//
// Created by PC on 17/11/2026.
//

#include "Funciones.h"

#include "Nodo.h"

void abrirArchLectura(const char* nombreArch, ifstream &archivo) {
    archivo.open(nombreArch);
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }
}

char* leerCadenaExacta(ifstream &archivo, char delimitador) {
    char buffer[CAP_BUFFER];
    archivo.getline(buffer, CAP_BUFFER, delimitador);
    if (archivo.eof()) return nullptr;
    char* cadena=new char[strlen(buffer)+1];
    strcpy(cadena, buffer);
    return cadena;
}

int calcularFecha(int dia, int mes, int anio) {
    return (anio*10000)+(mes*100)+dia;
}

bool esBisiesto(int anio) {
    if (anio%400==0) return true;
    if (anio%100==0) return false;
    if (anio%4==0) return true;
    return false;
}

int calcularDias(int mes, int anio) {
    if (mes==2) {
        if (esBisiesto(anio)) return 29;
        return 28;
    }
    if (mes==1 or mes==3 or mes==5 or mes==7 or mes==8 or mes==10 or mes==12) return 31;
    return 30;
}

bool validarFecha(int dia, int mes, int anio) {
    if (dia<1 or dia>calcularDias(mes, anio)) return false;
    if (mes<1 or mes>12) return false;
    if (anio<1) return false;
    return true;
}

void insertarOrdenado(struct Nodo *&lista, struct Envio envioAux) {
    struct Nodo *puntero = lista;
    struct Nodo* anterior=nullptr;
    struct Nodo* nuevo;
    nuevo=new struct Nodo;
    nuevo->envio=envioAux;

    int fechaNueva=calcularFecha(envioAux.fechaRegistro.dia, envioAux.fechaRegistro.mes, envioAux.fechaRegistro.anio);

    while (puntero!=nullptr) {
        int fechaPuntero=calcularFecha(puntero->envio.fechaRegistro.dia, puntero->envio.fechaRegistro.mes,
            puntero->envio.fechaRegistro.anio);
        if (fechaNueva<fechaPuntero) break;
        anterior=puntero;
        puntero=puntero->siguiente;
    }
    nuevo->siguiente=puntero;
    if (anterior==nullptr) lista=nuevo;
    else anterior->siguiente=nuevo;
}

void cargarEnvios(const char* nombreArch, struct Nodo*& lista, struct Resumen& resumen) {
    ifstream entrada;
    abrirArchLectura(nombreArch, entrada);

    struct Envio envioAux{};
    lista=nullptr;
    char c, sinCobertura[CAP_BUFFER]="(sin cobertura)", clienteNoRegis[CAP_BUFFER]="(cliente no registrado)";

    while (true) {
        envioAux.codigo=leerCadenaExacta(entrada, ',');
        if (envioAux.codigo==nullptr or entrada.eof()) break;
        entrada >> envioAux.fechaRegistro.dia >> c >> envioAux.fechaRegistro.mes >> c >> envioAux.fechaRegistro.anio
                >> c >> envioAux.remitente.dni >> c >> envioAux.destinatario.dni >> c  >> envioAux.destino.codigoDistrito
                >> c >> envioAux.peso;
        entrada.ignore();
        envioAux.entrega.estado='P'; //cada envío inicia en estado pendiente

        //se declara inicialmente los nombres:
        envioAux.destino.nombreDistrito=new char[CAP_BUFFER];
        strcpy(envioAux.destino.nombreDistrito, sinCobertura);
        envioAux.remitente.nombre=new char[CAP_BUFFER];
        strcpy(envioAux.remitente.nombre, clienteNoRegis);
        envioAux.destinatario.nombre=new char[CAP_BUFFER];
        strcpy(envioAux.destinatario.nombre, clienteNoRegis);

        if (validarFecha(envioAux.fechaRegistro.dia, envioAux.fechaRegistro.mes, envioAux.fechaRegistro.anio))
            insertarOrdenado(lista, envioAux); //solo se insertan y ordenan los registros con fechas validas
        else resumen.cantFilasFechaInvalida++;
    }
}

struct Nodo * buscarDNI(struct Nodo *lista, int dniBuscado, char cliente) {
    struct Nodo *puntero=lista;
    if (cliente=='R') { //revisa el remitente
        while (puntero and puntero->envio.remitente.dni!=dniBuscado) puntero=puntero->siguiente;
        return puntero; //solo devuelve la primera coincidencia
    }
    else if (cliente=='D') { //revisa el destinatario
        while (puntero and puntero->envio.destinatario.dni!=dniBuscado) puntero=puntero->siguiente;
        return puntero; //solo devuelve la primera coincidencia
    }
}

void procesarClientes(const char *nombreArch, struct Nodo *&lista) {
    ifstream entrada;
    abrirArchLectura(nombreArch, entrada);
    int dni, telefono; char c;

    while (entrada >>dni >> c) {
        char *nombre=leerCadenaExacta(entrada, ',');
        entrada >> telefono;

        struct Nodo *puntero=lista;
        while (puntero) { //se lee toda la lista
            if (puntero->envio.remitente.dni==dni) {
                puntero->envio.remitente.telefono=telefono;
                delete [] puntero->envio.remitente.nombre; //se borra el nombre anterior
                puntero->envio.remitente.nombre=new char[strlen(nombre)+1];
                strcpy(puntero->envio.remitente.nombre, nombre);
            }
            if (puntero->envio.destinatario.dni==dni) {
                puntero->envio.destinatario.telefono=telefono;
                delete [] puntero->envio.destinatario.nombre; //se borra el nombre anterior
                puntero->envio.destinatario.nombre=new char[strlen(nombre)+1];
                strcpy(puntero->envio.destinatario.nombre, nombre);
            }
            puntero=puntero->siguiente;
        }
    }
}

struct Nodo * buscarDistrito(struct Nodo *lista, int distritoBuscado) {
    struct Nodo *puntero=lista;
    while (puntero and puntero->envio.destino.codigoDistrito!=distritoBuscado) puntero=puntero->siguiente;
    return puntero;
}

void procesarDestinos(const char* nombreArch, struct Nodo*& lista, struct Resumen& resumen) {
    ifstream entrada;
    abrirArchLectura(nombreArch, entrada);
    int codDistrito; double tarifaBase, tarifaPorKg; char zona, c;

    while (entrada >> codDistrito >> c) {
        char* distrito=leerCadenaExacta(entrada, ',');
        entrada >> zona >> c >> tarifaBase >> c >> tarifaPorKg;

        struct Nodo* distritoEncontrado=buscarDistrito(lista, codDistrito);
        struct Nodo *puntero=lista;
        if (distritoEncontrado==nullptr) resumen.cantDistritosSinCobertura++;
        while (puntero) { //recorre toda la lista
            if (puntero->envio.destino.codigoDistrito==codDistrito) {
                delete [] puntero->envio.destino.nombreDistrito;
                puntero->envio.destino.nombreDistrito=new char[strlen(distrito)+1];
                strcpy(puntero->envio.destino.nombreDistrito, distrito);
                puntero->envio.destino.tarifa.tarifaBase=tarifaBase;
                puntero->envio.destino.tarifa.tarifaPorKg=tarifaPorKg;
                puntero->envio.destino.zona=zona;
            }
            puntero=puntero->siguiente;
        }
    }
}

void eliminarSinCobertura(struct Nodo *&lista, char *cadena) {
    struct Nodo* puntero=lista;
    struct Nodo* anterior=nullptr;
    struct Nodo* sale;

    while (puntero) {
        if (strcmp(puntero->envio.destino.nombreDistrito, cadena)!=0) {
            anterior=puntero;
            puntero=puntero->siguiente;
        }
        else {
            sale = puntero;
            if (anterior==nullptr) {
                lista=puntero->siguiente;
                puntero=lista;
            }
            else {
                anterior->siguiente=puntero->siguiente;
                puntero=puntero->siguiente;
            }
            delete sale;
        }
    }
}

struct Nodo * buscarEnvio(struct Nodo *lista, char *codEnvioBuscado) {
    struct Nodo* puntero=lista;
    while (puntero and strcmp(puntero->envio.codigo,codEnvioBuscado)!=0) puntero=puntero->siguiente;
    return puntero;
}

long long pasarFechaADias(struct Fecha f) {
    long long total=0;
    for (int i=1; i<f.anio; i++) {
        total+= esBisiesto(i)?366:365;
    }
    for (int j=1; j<f.mes; j++) {
        total+=calcularDias(j, f.anio);
    }
    total+=(f.dia-1);
    return total;
}

int calcularDiasDeDemora(struct Fecha fechaFin, struct Fecha fechaInicio) {
    return pasarFechaADias(fechaFin)-pasarFechaADias(fechaInicio);
}

int retornarFechaRegistro(struct Nodo *lista, char *codEnvio) {
    struct Nodo* puntero=lista;
    while (puntero) {
        if (strcmp(codEnvio, puntero->envio.codigo)==0) {
            return calcularFecha(puntero->envio.fechaRegistro.dia, puntero->envio.fechaRegistro.mes,
                puntero->envio.fechaRegistro.anio);
        }
        puntero=puntero->siguiente;
    }
    return -1;
}

void registrarEntregas(const char *nombreArch, struct Nodo *&lista, struct Resumen& resumen) {
    ifstream entrada;
    abrirArchLectura(nombreArch, entrada);
    int dia, mes, anio; char c, estado;

    while (char* codEnvio=leerCadenaExacta(entrada, ',')) {
        entrada >> dia >> c >> mes >> c >> anio >> c >> estado;

        struct Nodo* codEnvioEncontrado=buscarEnvio(lista, codEnvio);
        bool cond1=codEnvioEncontrado!=nullptr;
        bool cond2=validarFecha(dia, mes, anio)==true;
        bool cond3=retornarFechaRegistro(lista, codEnvio)!=-1;
        bool cond4=calcularFecha(dia, mes, anio)>retornarFechaRegistro(lista, codEnvio);

        if (cond1 and cond2 and cond3 and cond4) {
            codEnvioEncontrado->envio.entrega.fechaEntrega.dia=dia;
            codEnvioEncontrado->envio.entrega.fechaEntrega.mes=mes;
            codEnvioEncontrado->envio.entrega.fechaEntrega.anio=anio;
            codEnvioEncontrado->envio.entrega.estado=estado;
            codEnvioEncontrado->envio.entrega.cantDiasDemora=calcularDiasDeDemora(codEnvioEncontrado->
                envio.entrega.fechaEntrega, codEnvioEncontrado->envio.fechaRegistro);
        }
        else resumen.cantEntregasIgnoradas++;
    }
}

void calcularCostos(struct Nodo *&lista) {
    struct Nodo* puntero=lista;
    while (puntero) {
        puntero->envio.costo=puntero->envio.destino.tarifa.tarifaBase+
            (puntero->envio.destino.tarifa.tarifaPorKg*puntero->envio.peso);
        if (puntero->envio.peso>10) puntero->envio.costo+=(puntero->envio.costo*RECARGO);
        puntero=puntero->siguiente;
    }
}

void imprimirSeparador(ofstream &archivo, char c, int n) {
    for (int i = 0; i < n; i++) archivo << c;
    archivo << endl;
}

void imprimirFecha(ofstream &archivo, int dd, int mm, int aa) {
    archivo << right << setw(2) << setfill('0') << dd << "/" << setw(2) << mm << "/" << setw(4) << aa
            << setfill(' ');
}

void imprimirEncabezado(ofstream &archivo) {
    archivo << "ENVIOS REGISTRADOS" << endl;
    imprimirSeparador(archivo, '=', ANCHO_REPORTE);
    archivo << left << setw(9) << "CODIGO" << setw(13) << "REGISTRO" << setw(22) << "DISTRITO"
            << setw(10) << "ZONA" << setw(9) << "PESO" << setw(9) << "COSTO" << setw(12) << "ESTADO"
            << setw(12) << "FECHA" << "DIAS" << endl;
    imprimirSeparador(archivo, '-', ANCHO_REPORTE);
}

void imprimirResumenZona(ofstream &salida, struct TotalPorZona totalPorZona, char zona) {
    int pos=(int)zona - 'A';
    salida << left << setw(4) << zona << right << setw(10) << totalPorZona.cantEnvios[pos]
            << setw(12) << fixed << setprecision(2) << totalPorZona.pesoTotal[pos]
            << setw(14) << totalPorZona.montoTotal[pos] << endl;
}

void imprimirResumenZonas(ofstream &salida, struct TotalPorZona totalPorZona) {
    imprimirSeparador(salida, '=', ANCHO_REPORTE);
    salida << "RESUMEN POR ZONA" << endl;
    salida << left << setw(4) << "ZONA" << right << setw(10) << "ENVIOS" << setw(12) << "PESO (KG)"
            << setw(14) << "MONTO (S/)" << endl;
    imprimirResumenZona(salida, totalPorZona, 'A');
    imprimirResumenZona(salida, totalPorZona, 'B');
    imprimirResumenZona(salida, totalPorZona, 'C');
    imprimirResumenZona(salida, totalPorZona, 'D');
}

void abrirArchEscritura(const char* nombreArch, ofstream &archivo) {
    archivo.open(nombreArch);
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }
}

void generarReporte(const char* nombreArch, struct Nodo* lista, struct Resumen resumen,
    struct TotalPorZona &totalPorZona) {
    ofstream salida;
    abrirArchEscritura(nombreArch, salida);
    imprimirEncabezado(salida);

    struct Nodo *puntero=lista;

    //declaramos el contenido del arrZonas (CAPACIDAD=4)
    totalPorZona.arrZonas[0]='A';
    totalPorZona.arrZonas[1]='B';
    totalPorZona.arrZonas[2]='C';
    totalPorZona.arrZonas[3]='D';

    int cantEnvios=0, cantPendientes=0;

    while (puntero) {
        salida << left << setw(9) << puntero->envio.codigo;
        imprimirFecha(salida, puntero->envio.fechaRegistro.dia, puntero->envio.fechaRegistro.mes,
            puntero->envio.fechaRegistro.anio);

        salida << left << setw(3) << " " << setw(22) << puntero->envio.destino.nombreDistrito;

        if (puntero->envio.destino.zona=='A' or puntero->envio.destino.zona=='B' or puntero->envio.destino.zona=='C'
            or puntero->envio.destino.zona=='D') {
            salida << setw(10) << puntero->envio.destino.zona;
        }
        else salida << setw(10) << " ";

        salida << setw(9) << fixed << setprecision(2) << puntero->envio.peso << setw(9) << puntero->envio.costo;
        if (puntero->envio.entrega.estado=='P') {
            salida << setw(12) << "PENDIENTE";
            cantPendientes++;
        }
        else if (puntero->envio.entrega.estado=='E') salida << setw(12) << "ENTREGADO";
        else if (puntero->envio.entrega.estado=='D') salida << setw(12) << "DEVUELTO";

        if (puntero->envio.entrega.estado=='E' or puntero->envio.entrega.estado=='D') {
            imprimirFecha(salida, puntero->envio.entrega.fechaEntrega.dia,puntero->envio.entrega.fechaEntrega.mes,
            puntero->envio.entrega.fechaEntrega.anio);
            salida << setw(2) << "" << setw(4) << puntero->envio.entrega.cantDiasDemora << endl;
        }
        else salida << endl;

        salida << setw(9) << "" << left << setw(15) << "Remitente:" << setw(11) << puntero->envio.remitente.dni
                << setw(30) << puntero->envio.remitente.nombre;
        if (puntero->envio.remitente.telefono!=0) salida << "Tel. " << puntero->envio.remitente.telefono << endl;
        else salida << endl;

        salida << setw(9) << "" << setw(15) << "Destinatario:" << setw(11) << puntero->envio.destinatario.dni
                        << setw(30) << puntero->envio.destinatario.nombre;
        if (puntero->envio.destinatario.telefono!=0) salida<< "Tel. " << puntero->envio.destinatario.telefono << endl;
        else salida << endl;









        for (int i=0; i<4; i++) {
            if (totalPorZona.arrZonas[i]==puntero->envio.destino.zona) {
                totalPorZona.cantEnvios[i]++;
                totalPorZona.pesoTotal[i]+=puntero->envio.peso;
                totalPorZona.montoTotal[i]+=puntero->envio.costo;
            }
        }

        cantEnvios++;
        puntero=puntero->siguiente;
    }

    imprimirResumenZonas(salida, totalPorZona);



    imprimirSeparador(salida, '-', ANCHO_REPORTE);
    salida << "Envios en el reporte: " << cantEnvios << endl;
    salida << "Envios pendientes de entrega: " << cantPendientes << endl;
    salida << "Filas de envios descartadas por fecha invalida: " << resumen.cantFilasFechaInvalida << endl;
    salida << "Envios eliminados por distrito sin cobertura: " << endl;
    salida << "Entregas ignoradas: " << endl;

}