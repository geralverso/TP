//
// Created by aml on 7/11/2026.
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

char* leerCadenaExacta(ifstream &archivo, char delimitador) {
    char buffer[CAP_BUFFER];
    archivo.getline(buffer, CAP_BUFFER, delimitador);
    if (archivo.eof()) return nullptr;
    char* cadena=new char[strlen(buffer)+1];
    strcpy(cadena, buffer);
    return cadena;
}

void cargarAniosRevisiones(ifstream &archivo, struct Vehiculo &vehiculo) {
    int numAnios=0, anio;
    while (true) { //para leer los años de revision:
        archivo >> anio;
        vehiculo.arrAniosRevisiones[numAnios]=anio;
        numAnios++;
        if (archivo.get()=='\n') break;
    }
    vehiculo.cantRevisiones=numAnios;
}

void cargarVehiculos(const char *nombreArch, struct Vehiculo *&vehiculos, int &numVehiculos) {
    ifstream entrada;
    abrirArchLectura(nombreArch, entrada);

    //se crea un arreglo dinámico (auxiliar) que almacene los datos de los vehículos
    struct Vehiculo vehiculoAux{}; //todo se inicializa en 0

    //-------si te dan como dato el numVehiculos dentro del archivo de datos:
    entrada >> numVehiculos;
    // vehiculos=new struct Vehiculo[numVehiculos]; //se lee y se asigna su memoria dinamica

    //-------si NO te dan como dato el numVehiculos dentro del archivo de datos:
    struct Vehiculo buffer[1000];
    int i=0; //i representa el numVehiculos sin acumular

    while (entrada >> vehiculoAux.codigo) {
        entrada >> vehiculoAux.categoria >> vehiculoAux.dniPropietario >> ws;
        vehiculoAux.placa=leerCadenaExacta(entrada, ' ');
        cargarAniosRevisiones(entrada,vehiculoAux);
        vehiculoAux.arrInfracciones[0].tipoInfraccion='M'; //exc.velocidad
        vehiculoAux.arrInfracciones[1].tipoInfraccion='G'; //carr.no permitido
        // vehiculos[i]=vehiculoAux; //si te dan como dato el numVehiculos, de frente se iguala al arr.dinamico

        buffer[i]=vehiculoAux; //si NO te dan como dato el numVehiculos, se iguala al buffer.estatico
        i++;
    }

    vehiculos=new struct Vehiculo[i]; //lo que se hace si NO te dan como dato el numVehiculos
    for (int j=0;j<i;j++) vehiculos[j]=buffer[j];
}

int buscarVehiculo(const struct Vehiculo *vehiculos, int numVehiculos, int codVehiculoBuscado) {
    for (int i=0; i<numVehiculos; i++) {
        if (vehiculos[i].codigo==codVehiculoBuscado) {
            return i;
        }
    }
    return NO_ENCONTRADO;
}

void agregarCaptura(struct Captura *arrCapturas, int &cantCapturas, struct Captura &capturaAux) {
    arrCapturas[cantCapturas]=capturaAux;
    cantCapturas++;
}

void cargarCapturas(const char *nombreArch, struct Vehiculo *vehiculos, int numVehiculos) {
    ifstream entrada;
    abrirArchLectura(nombreArch, entrada);

    int codVehiculo, carril, kilometro, codCamara, dia, mes, anio;
    double velocidad;
    char c;

    //se crea un arreglo auxiliar que almacene los datos de las capturas
    struct Captura capturaAux{}; //todo se inicializa en 0
    while (entrada >> codVehiculo >> c) {
        entrada >> velocidad >> c >> carril >> c >> kilometro >> c >> dia >> c >> mes >> c >> anio >> c >> codCamara;

        int pos=buscarVehiculo(vehiculos, numVehiculos, codVehiculo);
        if (pos!=NO_ENCONTRADO) { //si el vehiculo está registrado
            //los datos se guardan si el vehiculo está registrado
            capturaAux.velocidad=velocidad;
            capturaAux.carril=carril;
            capturaAux.kilometro=kilometro;
            capturaAux.fecha=(anio*10000)+(mes*100)+dia;
            capturaAux.codCamara=codCamara;

            bool capturaValida=(velocidad>=0 and velocidad<=300) and (carril>=1 and carril<=4);
            if (capturaValida) agregarCaptura(vehiculos[pos].arrCapturasValidas, vehiculos[pos].cantCapturasValidas,
                capturaAux);
            else agregarCaptura(vehiculos[pos].arrCapturasInvalidas, vehiculos[pos].cantCapturasInvalidas,
                capturaAux);
        }
    }
}

void acumularInfraccionesM(struct Vehiculo *vehiculos, int i, int carril, double vel, int km) {
    bool validar1=carril==1 and vel<=80;
    bool validar2=carril==2 and vel<=60;
    bool validar3=carril==3 and ((vel<=80 and km>=1 and km<=100) or (vel<=120 and km>=101 and km<=200)
        or (vel<=100 and km>=201 and km<=300));
    bool validar4=carril==4 and (vel>=80 and ((vel<=120 and km>=1 and km<=100) or
        (vel<=160 and km>=101 and km<=200) or (vel<=140 and km>=201 and km<=300)));
    if (!(validar1 or validar2 or validar3 or validar4)) {
        vehiculos[i].arrInfracciones[0].cantidad++; //arrInfracciones[0] xq corresponde a M – Exceso de velocidad
        vehiculos[i].arrInfracciones[0].monto+=MONTO_M;
        vehiculos[i].arrInfracciones[0].puntos+=PUNTOS_M;
    }
}

void acumularInfraccionesG(struct Vehiculo *vehiculos, int i, char cat, int carril) {
    bool validar1=(cat=='E') and carril==1;
    bool validar2=(cat=='P') and carril==2;
    bool validar3=(cat=='E' or cat=='L' or cat=='M') and carril==3;
    bool validar4=(cat=='L') and carril==4;
    if (!(validar1 or validar2 or validar3 or validar4)) {
        vehiculos[i].arrInfracciones[1].cantidad++; //arrInfracciones[1] xq corresponde a G – Carril no permitido
        vehiculos[i].arrInfracciones[1].monto+=MONTO_G;
        vehiculos[i].arrInfracciones[1].puntos+=PUNTOS_G;
    }
}

void identificarInfracciones(struct Vehiculo *vehiculos, int numVehiculos) {
    for (int i=0; i<numVehiculos; i++) {
        int numCapturas=vehiculos[i].cantCapturasValidas;
        for (int j=0; j<numCapturas; j++) {
            char cat=vehiculos[i].categoria;
            int carril=vehiculos[i].arrCapturasValidas[j].carril;
            double vel=vehiculos[i].arrCapturasValidas[j].velocidad;
            int km=vehiculos[i].arrCapturasValidas[j].kilometro;
            acumularInfraccionesM(vehiculos, i, carril, vel, km);
            acumularInfraccionesG(vehiculos, i, cat,  carril);
        }
    }
}


//FUNCIONES PARA ORDENAR:

void intercambiarVehiculo(struct Vehiculo &a, struct Vehiculo &b) {
    struct Vehiculo aux=a;
    a = b, b=aux;
}

void intercambiarCaptura(struct Captura &a, struct Captura &b) {
    struct Captura aux=a;
    a = b, b=aux;
}

void ordenarCapturas(struct Captura *captura, int numCap) {
    for (int j=0; j<numCap-1; j++) {
        for (int k=j+1; k<numCap; k++) {
            if (captura[j].fecha<captura[k].fecha) {
                intercambiarCaptura(captura[j], captura[k]);
            }
        }
    }
}

void ordenarVehiculos(struct Vehiculo *vehiculos, int numVehiculos) {
    for (int i=0; i<numVehiculos-1; i++) {
        for (int j=i+1; j<numVehiculos; j++) {
            if (strcmp(vehiculos[i].placa, vehiculos[j].placa)>0) {
                intercambiarVehiculo(vehiculos[i], vehiculos[j]);
            }
        }
    }
    for (int i=0; i<numVehiculos; i++) {
        int numCapValidas=vehiculos[i].cantCapturasValidas, numCapInvalidas=vehiculos[i].cantCapturasInvalidas;
        ordenarCapturas(vehiculos[i].arrCapturasValidas, numCapValidas);
        ordenarCapturas(vehiculos[i].arrCapturasInvalidas, numCapInvalidas);
    }
}


//FUNCIONES PARA IMPRIMIR:

void imprimirSeparador(ofstream &archivo, char c, int n) {
    for (int i=0; i<n; i++) archivo << c;
    archivo << endl;
}

void imprimirEncabezado(ofstream &archivo) {
    imprimirSeparador(archivo, '=', ANCHO_REPORTE);
    archivo << right << setw((ANCHO_REPORTE+35)/2) << "REPORTE DE INFRACCIONES DE TRANSITO" << endl;
}

void imprimirCabeceraTabla(ofstream &salida, const struct Vehiculo *vehiculos, int i) {
    imprimirSeparador(salida, '=', ANCHO_REPORTE);
    salida << left << setw(10) << "VEHICULO" << vehiculos[i].codigo << " (" << vehiculos[i].placa << setw(8)
            << ")" << "CATEGORIA: ";
    if (vehiculos[i].categoria=='E') salida << setw(20) << "Emergencia";
    else if (vehiculos[i].categoria=='P') salida << setw(20) << "Pesado";
    else if (vehiculos[i].categoria=='L') salida << setw(20) << "Ligero";
    else if (vehiculos[i].categoria=='M') salida << setw(20) << "Motocicleta";
    salida << "DNI: " << setw(14) << vehiculos[i].dniPropietario << "Revisiones: ";

    int numAnios=vehiculos[i].cantRevisiones;
    for (int j=0; j<numAnios; j++) salida << vehiculos[i].arrAniosRevisiones[j] << " ";
    salida << endl;
    imprimirSeparador(salida, '-', ANCHO_REPORTE);
}

void imprimirInfoInfracciones(ofstream &archivo, const struct Vehiculo *vehiculos, int i) {
    archivo << left << setw(30) << "INFRACCIONES" << setw(15) << "Cantidad" << setw(10) << "Monto" << "Puntos\n";
    archivo << left << setw(34) << "M - Exceso de velocidad" << setw(11) << vehiculos[i].arrInfracciones[0].cantidad
            << setw(11) << vehiculos[i].arrInfracciones[0].monto << vehiculos[i].arrInfracciones[0].puntos << endl;
    archivo << left << setw(34) << "G - Carril no permitido" << setw(11) << vehiculos[i].arrInfracciones[1].cantidad
            << setw(11) << vehiculos[i].arrInfracciones[1].monto << vehiculos[i].arrInfracciones[1].puntos << endl;
}

void imprimirFecha(ofstream &archivo, int fecha) {
    int anio=fecha/10000, mes=(fecha%10000)/100, dia=fecha%100;
    archivo << right << setw(2) << setfill('0') << dia << "/" << setw(2) << mes << "/" << setw(4) << anio
            << setfill(' ') << endl;
}

void imprimirCapturas(ofstream &salida, const char* titulo, const struct Captura *capturas, int i, int numCap){
    salida << titulo << "\n" << right << setw(12) << "carril" << setw(10) << "km" << setw(15) << "velocidad"
            << setw(10) << "camara" << setw(10) << "fecha" << endl;
    for (int j=0; j<numCap; j++) {
        salida << right << setw(10) << capturas[j].carril << setw(12) << capturas[j].kilometro
                << fixed << setprecision(2) << setw(13) << capturas[j].velocidad
                << setw(10) << capturas[j].codCamara << setw(4) << " ";
        imprimirFecha(salida, capturas[j].fecha);
    }
}

void imprimirCapValidasEInvalidas(ofstream &salida, const struct Vehiculo *vehiculos, int i) {
    int numCapValidas=vehiculos[i].cantCapturasValidas, numCapInvalidas=vehiculos[i].cantCapturasInvalidas;
    if (numCapValidas>0) {
        imprimirCapturas(salida, "CAPTURAS VALIDAS", vehiculos[i].arrCapturasValidas, i, numCapValidas);
        imprimirSeparador(salida, '-', ANCHO_REPORTE);
    }
    if (numCapInvalidas>0) {
        imprimirCapturas(salida, "CAPTURAS INVALIDAS", vehiculos[i].arrCapturasInvalidas, i, numCapInvalidas);
        imprimirSeparador(salida, '-', ANCHO_REPORTE);
    }
}


//FUNCIONES PARA GENERAR REPORTES:

void abrirArchEscritura(const char* nombreArch, ofstream& archivo) {
    archivo.open(nombreArch);
    if (!archivo) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }
}

void generarReporte(const char *nombreArch, const struct Vehiculo *vehiculos, int numVehiculos) {
    ofstream salida;
    abrirArchEscritura(nombreArch, salida);
    imprimirEncabezado(salida);
    for (int i=0; i<numVehiculos; i++) {
        imprimirCabeceraTabla(salida, vehiculos, i);
        imprimirCapValidasEInvalidas(salida, vehiculos, i);
        imprimirInfoInfracciones(salida, vehiculos, i);
    }
}
