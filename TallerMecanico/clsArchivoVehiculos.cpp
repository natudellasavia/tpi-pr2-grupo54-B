#include <iostream>
#include <cstring>
#include <cstdio>
#include "clsArchivoVehiculos.h"
#include "clsVehiculo.h"
#include "funciones.h"
using namespace std;


int ArchivoVehiculos::agregarRegistro(Vehiculo reg) {
    FILE *pArchivo;
    pArchivo = fopen(nombre, "ab");
    if (pArchivo == nullptr){return -5;} // -5 no pudo abrir el archivo.

    int registrosEscritos = fwrite(&reg, tamanioRegistro, 1, pArchivo); // Escribo el registro pasado por parámetro
    fclose(pArchivo);
    return registrosEscritos; // 1 si escribió correctamente, 0 si no escribió
}


bool ArchivoVehiculos::bajaLogica(const char* nroPatente){
    Vehiculo reg;
    ArchivoVehiculos archiVehiculos;

    int pos = archiVehiculos.buscarPosicion(nroPatente); // Devolve: Posición / -1 no encontró / -2 no pudo abrir
    if(pos==-1) return false; // Registro no encontrado
    reg = archiVehiculos.leerRegistro(pos); // Traemos la información del registro
    reg.setEstado(false); // Damos de baja
    return archiVehiculos.modificarRegistro(reg, pos); // Sobrescribimos el registro
}


int ArchivoVehiculos::modificarRegistro(Vehiculo reg, int pos) {
    FILE *pArchivo;
    pArchivo = fopen(nombre, "rb+");
    if(pArchivo == nullptr){return -5;} // No pudo abrir el archivo

    fseek(pArchivo, pos * tamanioRegistro, SEEK_SET);
    int registrosEscritos = fwrite(&reg, tamanioRegistro, 1, pArchivo);

    fclose(pArchivo);
    return registrosEscritos; // El valor va a ser 1 si escribió correctamente o 0 si no escribió
}


int ArchivoVehiculos::contarRegistros(){
    FILE *pArchivo;
    pArchivo=fopen(nombre,"rb");
    if(pArchivo == nullptr){return -5;} // No pudo abrir el archivo

    fseek(pArchivo, 0, SEEK_END); // Posicionarse al final del archivo
    int tamanioArchivo = ftell(pArchivo); // Cantidad de bytes desde el inicio del archivo hasta el puntero
    fclose(pArchivo);

    int cantRegistros = tamanioArchivo/tamanioRegistro;
    return cantRegistros;
}


int ArchivoVehiculos::buscarPosicion(const char* nroPatente) {
    FILE *pArchivo;
    pArchivo = fopen(nombre, "rb");
    if (pArchivo == nullptr) {return -5;} // No pudo abrir el archivo

    int cantidadRegistros = contarRegistros();
    Vehiculo reg;

    for (int i = 0; i < cantidadRegistros; i++) {
        fseek(pArchivo, i * tamanioRegistro, SEEK_SET);
        if (fread(&reg, tamanioRegistro, 1, pArchivo) != 1) {
            fclose(pArchivo);
            return -2; // No se pudo leer el registro.

        }
        if (strcmp(reg.getNroPatente(), nroPatente) == 0) {
            fclose(pArchivo);
            return i; // Si la encuentra, retorna la posición
        }
    }
    fclose(pArchivo);
    return -1; // No encontró la patente en el archivo.
}


Vehiculo ArchivoVehiculos::leerRegistro(int pos) {
    Vehiculo reg;
    FILE *pArchivo;
    pArchivo = fopen(nombre, "rb");
    if (pArchivo == nullptr) {return reg;} // Devolvemos sus atributos con los valores iniciales del constructor.

    fseek(pArchivo, pos * tamanioRegistro, SEEK_SET);
    fread(&reg, tamanioRegistro, 1, pArchivo);

    fclose(pArchivo);
    return reg;
}


bool ArchivoVehiculos::existePatente(const char* nroPatente){
    Vehiculo reg;
    FILE *pArchivo;
    pArchivo = fopen(nombre, "rb");
    if (pArchivo == nullptr) {return false;} // false si no pudo abrir el archivo.

    while (fread(&reg, tamanioRegistro, 1, pArchivo) == 1){
        if (strcmp(reg.getNroPatente(), nroPatente) == 0){
            fclose(pArchivo);
            return true; // Patente encontrada
        }
    }

    fclose(pArchivo);
    return false; // Patente no encontrada
}


/// ------------------------- C O N S U L T A S -------------------------

int ArchivoVehiculos::consultaVehiculoPorPatente(const char* nroPatente) {
    Vehiculo reg;
    int devuelve = -1;
    FILE *pArchivo = fopen(nombre, "rb");
    if (pArchivo == nullptr) {return -5;} // Retorna -5 si no se abrio el archivo

    // Recorro el archivo de vehiculos y muestro el registro por patente
    int cantidadRegistros = contarRegistros(); // Cantidad total de registros del archivo
    for(int i = 0; i < cantidadRegistros; i++){
        reg = leerRegistro(i);
        if(strcmp(nroPatente, reg.getNroPatente()) == 0){
            reg.Mostrar();
            devuelve++; // Acumula +1 para indicar que sí encontró registro al momento de retornar
        }
    }

    fclose(pArchivo);
    return devuelve; // Si no encontró ningun registro devuelve -1
}


int ArchivoVehiculos::consultaVehiculoPorTipo(int tipoVehiculo) {
    Vehiculo reg;
    ArchivoVehiculos archiVehiculos;
    int devuelve = -1;

    // Recorro el archivo de vehiculos y muestro el registro por tipo de vehiculo
    int cantidadRegistros = archiVehiculos.contarRegistros(); // Cantidad total de registros del archivo
    for(int i = 0; i < cantidadRegistros; i++){
        reg = archiVehiculos.leerRegistro(i);
        if(reg.getTipoVehiculo() == tipoVehiculo){
            reg.Mostrar();
            devuelve++; // Acumula +1 para indicar que sí encontró registro al momento de retornar
        }
    }

    return devuelve; // Si no encontró ningun registro devuelve -1
}


int ArchivoVehiculos::consultaVehiculoEnTaller() {
    Vehiculo reg;
    ArchivoVehiculos archiVehiculos;
    int devuelve = -1;

    // Recorro el archivo de vehiculos y muestro el registro que está activo
    int cantidadRegistros = archiVehiculos.contarRegistros();
    for(int i = 0; i < cantidadRegistros; i++){
        reg = archiVehiculos.leerRegistro(i);
        if(reg.getEstado() == true){
            reg.Mostrar();
            devuelve++; // Acumula +1 para indicar que sí encontró registro al momento de retornar
        }
    }

    return devuelve; // Si no encontró ningun registro devuelve -1
}



/// ------------------------- L I S T A D O S -------------------------

int ArchivoVehiculos::listadoVehiculosPorMarca() {
    ArchivoVehiculos archiVehiculos;

    int cantidadRegistros = archiVehiculos.contarRegistros();
    if (cantidadRegistros <= 0) {return -1;} // No hay reparaciones cargadas

    Vehiculo* vec = new Vehiculo[cantidadRegistros]; // Creamos un arreglo dinámico de objetos para ordenar por marca
    int cantMemDinamica = 0; // Va a tener la cantidad total de registros de la memoria dinámica

    for(int i = 0; i < cantidadRegistros; i++) {
        Vehiculo reg = archiVehiculos.leerRegistro(i);
        // VALIDAMOS QUE LA REPARACION ESTE ACTIVA
        if (reg.getEstado()==true) {
            vec[cantMemDinamica] = reg; // Guardamos el registro solo si está activo
            cantMemDinamica++;
        }
    }

    // Ordenamos el archivo en memoria dinámica por cuit
    // i -> Posición de registro / x -> Posición de su siguiente registro
    for (int i = 0; i < cantidadRegistros - 1; i++){
        // Recorremos el vector posicionandonos en el siguiente registro
        for (int x = i + 1; x < cantidadRegistros; x++){
            if (strcmp(vec[i].getMarca(), vec[x].getMarca()) > 0){ // > 0 entonces la primer cadena es mayor a la segunda
                // Si el primer registro es mayor, se intercambian
                Vehiculo aux = vec[i];
                vec[i] = vec[x];
                vec[x] = aux;
            }
        }
    }

    // Mostramos todos los registros del archivo
    for (int i = 0; i < cantidadRegistros; i++) {
        vec[i].Mostrar();
    }

    delete[] vec;
}


int  ArchivoVehiculos::listadoVehiculosPorTipoDeVehiculo() {
    ArchivoVehiculos archiVehiculos;
    int cantidadRegistros = archiVehiculos.contarRegistros();
    if (cantidadRegistros <= 0) {return -1;} // No hay reparaciones cargadas

    Vehiculo* vec = new Vehiculo[cantidadRegistros]; // Creamos un arreglo dinámico de objetos para ordenar por tipo de vehículo
    int cantMemDinamica = 0; // Va a tener la cantidad total de registros de la memoria dinámica

    for (int i = 0; i < cantidadRegistros; i++) {
        Vehiculo reg = archiVehiculos.leerRegistro(i);
        // VALIDAMOS QUE LA REPARACION ESTE ACTIVA
        if (reg.getEstado()==true){
            vec[cantMemDinamica] = reg; // Guardamos el registro solo si está activo
            cantMemDinamica++;
        }
    }

    // Ordenamos el archivo en memoria dinámica por tipo de vehiculo
    // i -> Posición de registro / x -> Posición de su siguiente registro
    for (int i = 0; i < cantMemDinamica - 1; i++) {
        for (int x = i + 1; x < cantMemDinamica; x++) {
            if (vec[i].getTipoVehiculo() > vec[x].getTipoVehiculo()) {
                Vehiculo aux = vec[i];
                vec[i] = vec[x];
                vec[x] = aux;
            }
        }
    }

    // Mostramos todos los registros del archivo
    for (int i = 0; i < cantMemDinamica; i++) {
            vec[i].Mostrar();
    }

    delete[] vec;
}

