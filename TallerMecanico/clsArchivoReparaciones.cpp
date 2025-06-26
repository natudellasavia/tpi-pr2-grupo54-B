#include <iostream>
#include <cstring>
#include "clsReparacion.h"
#include "clsArchivoReparaciones.h"
#include "funciones.h"
using namespace std;

int ArchivoReparaciones::agregarRegistro(Reparacion reg){
    FILE *pArchivo;
    pArchivo=fopen(nombre,"ab");
    if(pArchivo == nullptr){return -5;} // No pudo abrir el archivo

    // ID autoincrementable:
    fseek(pArchivo, 0, SEEK_END); // Me posiciono al final del archivo para ver cual es el �ltimo id
    int posPuntero = ftell(pArchivo);
    int idReparaciones = (posPuntero/tamanioRegistro) + 1; // Consigo el id del �ltimo registro y lo incremento en 1
    reg.setIDReparaciones(idReparaciones); // Le asigno el id autoincrementado al registro que voy a cargar

    int registrosEscritos = fwrite(&reg, tamanioRegistro, 1, pArchivo);
    fclose(pArchivo);
    return registrosEscritos; // 1 si escribi� correctamente, 0 si no escribi�
}


bool ArchivoReparaciones::bajaLogica(int idReparacion, Fecha fechaBaja){
    Reparacion reg;
    ArchivoReparaciones archiReparaciones;

    int pos = archiReparaciones.buscarPosicion(idReparacion);
    reg = archiReparaciones.leerRegistro(pos); // Traemos la informaci�n del registro
    reg.setEstadovehiculo(false); // Damos de baja l�gica cambiando el estado a falso
    reg.setFechaSalida(fechaBaja); // Cargamos en el registro la fecha de salida

    return archiReparaciones.modificarRegistro(reg, pos); // Sobrescribimos el registro
}


int ArchivoReparaciones::modificarRegistro(Reparacion reg, int pos){
    FILE *pArchivo;
    pArchivo=fopen(nombre,"rb+");
    if(pArchivo == nullptr){return -5;} // No pudo abrir el archivo

    fseek(pArchivo, pos*tamanioRegistro, SEEK_SET); // nos posicionamos en el registro deseado
    int registrosEscritos = fwrite(&reg, tamanioRegistro, 1, pArchivo);

    fclose(pArchivo);
    return registrosEscritos; // El valor va a ser 1 si escribi� correctamente o 0 si no escribi�
}


int ArchivoReparaciones::contarRegistros(){
    FILE *pArchivo;
    pArchivo=fopen(nombre,"rb");
    if(pArchivo == nullptr){return -5;} // No pudo abrir el archivo

    fseek(pArchivo, 0, SEEK_END); // Posicionarse al final del archivo
    int tamanioArchivo = ftell(pArchivo); // Cantidad de bytes desde el inicio del archivo hasta el puntero
    fclose(pArchivo);

    int cantRegistros = tamanioArchivo/tamanioRegistro;
    return cantRegistros;
}


int ArchivoReparaciones::buscarPosicion(int idReparacion){
    FILE *pArchivo;
    pArchivo = fopen(nombre, "rb");
    if (pArchivo == nullptr) {return -5;} // No pudo abrir el archivo

    int cantidadRegistros = contarRegistros();
    Reparacion reg;

    for (int i = 0; i < cantidadRegistros; i++) {
        fseek(pArchivo, i * tamanioRegistro, SEEK_SET); // Posicionarse en el registro
        if (fread(&reg, tamanioRegistro, 1, pArchivo) != 1) {
            fclose(pArchivo);
            return -2; // No pudo leer el registro
        }
        if (reg.getIDReparaciones() == idReparacion) {
            fclose(pArchivo);
            return i; // Si la encuentra, retorna la posici�n
        }
    }

    fclose(pArchivo);
    return -1; // No encontr� el ID en el archivo.
}


Reparacion ArchivoReparaciones::leerRegistro(int pos){
    Reparacion reg;
    FILE *pArchivo;
    pArchivo=fopen(nombre,"rb");
    if(pArchivo == nullptr){return reg;} // Devolvemos sus atributos con los valores iniciales del constructor.

    fseek(pArchivo, pos*tamanioRegistro, SEEK_SET);
    fread(&reg, tamanioRegistro, 1, pArchivo);

    fclose(pArchivo);
    return reg;
}


bool ArchivoReparaciones::existePatenteActiva(const char* nroPatente) {
    Reparacion reg;
    FILE *pArchivo = fopen(nombre, "rb");
    if (pArchivo == nullptr) {return false;} // false si no pudo abrir el archivo.

    while (fread(&reg, tamanioRegistro, 1, pArchivo) == 1) {
        // Si el n�mero de patente es igual y el estado es activo
        if (strcmp(reg.getPatente(), nroPatente) == 0 && reg.getEstadovehiculo() == true) {
            fclose(pArchivo);
            return true; // Patente encontrada
        }
    }

    fclose(pArchivo);
    return false; // Patente no encontrada
}



/// ------------------------- C O N S U L T A S -------------------------

int ArchivoReparaciones::consultaReparacionPorId(int idReparacion){
    Reparacion reg;
    ArchivoReparaciones archiReparaciones;
    int devuelve = -1;

    // Recorro el archivo de reparaciones y muestro el registro por id
    int cantidadRegistros = archiReparaciones.contarRegistros(); // Cantidad total de registros del archivo
    for(int i = 0; i < cantidadRegistros; i++){
        reg = archiReparaciones.leerRegistro(i);
        if(reg.getIDReparaciones() == idReparacion){
            reg.Mostrar();
            devuelve++; // Acumula +1 para indicar que s� encontr� registro al momento de retornar
        }
    }

    return devuelve; // Si no encontr� ningun registro devuelve -1
}


int ArchivoReparaciones::consultaReparacionPorCliente(const char* cuil){
    Reparacion reg;
    ArchivoReparaciones archiReparaciones;
    int devuelve = -1;

    // Recorro el archivo de reparaciones y muestro el registro por cuit
    int cantidadRegistros = archiReparaciones.contarRegistros();
    for(int i = 0; i < cantidadRegistros; i++){
        reg = archiReparaciones.leerRegistro(i);
        if(strcmp(reg.getCuit(), cuil) == 0){
            reg.Mostrar();
            devuelve++; // Acumula +1 para indicar que s� encontr� registro al momento de retornar
        }
    }

    return devuelve; // Si no encontr� ningun registro devuelve -1
}


int ArchivoReparaciones::consultaReparacionPorVehiculo(const char* nroPatente){
    Reparacion reg;
    ArchivoReparaciones archiReparaciones;
    int devuelve = -1;

    int cantidadRegistros = archiReparaciones.contarRegistros();
    for(int i = 0; i < cantidadRegistros; i++){
        reg = archiReparaciones.leerRegistro(i);
        if (strcmp(reg.getPatente(), nroPatente) == 0){
            reg.Mostrar();
            devuelve++; // Acumula +1 para indicar que s� encontr� registro al momento de retornar
        }
    }

    return devuelve; // Si no encontr� ningun registro devuelve -1
}


int ArchivoReparaciones::consultaReparacionPorRango(float importeUno, float importeDos){
    Reparacion reg;
    ArchivoReparaciones archiReparaciones;
    int imprimio = -1; // Lo voy a usar para controlar que al menos se haya impreso 1 registro

    // Recorro el archivo de reparaciones y comparo si el importe del registro est� entre los dos ingresados por teclado
    int cantidadRegistros = archiReparaciones.contarRegistros();
    for(int i = 0; i < cantidadRegistros; i++){
        reg = archiReparaciones.leerRegistro(i);
        if(importeUno <= reg.getImporte() && reg.getImporte() <= importeDos){
            reg.Mostrar();
            imprimio++; // Lo voy a usar para controlar que al menos se haya impreso 1 registro
        }
    }

    return imprimio; // Si no encontr� ningun registro devuelve -1
}


int ArchivoReparaciones::consultaReparacionPorFecha(Fecha fechaUno, Fecha fechaDos){
    // fechaUno es FECHA DESDE (por teclado) / fechaDos es FECHA HASTA (por teclado)
    Reparacion reg;
    ArchivoReparaciones archiReparaciones;
    int imprimio = -1; // Lo voy a usar para controlar que al menos se haya impreso 1 registro

    // Recorro el archivo de reparaciones y comparo que la fechaIngreso del reg sea posterior o igual a fechaDos y anterior o igual a fechaUno
    int cantidadRegistros = archiReparaciones.contarRegistros();
    for(int i = 0; i < cantidadRegistros; i++){
        reg = archiReparaciones.leerRegistro(i);
        Fecha fechaEntrada = reg.getFechaEntrada(); // Obtengo la fecha del registro que estoy leyendo

        // VALIDAMOS QUE LA FECHA DEL REGISTRO SEA IGUAL O MAYOR A FECHA DESDE E IGUAL O MENOR A FECHA HASTA
        if(fechaMayorIgual(fechaEntrada, fechaUno) && fechaMenorIgual(fechaEntrada, fechaDos)){
            reg.Mostrar();
            imprimio++; // Lo voy a usar para controlar que al menos se haya impreso 1 registro
        }
    }

    return imprimio; // Si no encontr� ningun registro devuelve -1
}


int ArchivoReparaciones::consultaReparacionEnTaller(){
    Reparacion reg;
    ArchivoReparaciones archiReparaciones;
    int devuelve = -1;

    // Recorro el archivo de reparaciones y muestro el registro que est� activo
    int cantidadRegistros = archiReparaciones.contarRegistros();
    for(int i = 0; i < cantidadRegistros; i++){
        reg = archiReparaciones.leerRegistro(i);
        if(reg.getEstadovehiculo() == true){
            reg.Mostrar();
            devuelve++; // Acumula +1 para indicar que s� encontr� registro al momento de retornar
        }
    }

    return devuelve; // Si no encontr� ningun registro devuelve -1
}



/// ------------------------- L I S T A D O S -------------------------

int ArchivoReparaciones::listadoReparacionesPorId() {
    ArchivoReparaciones archiReparaciones;

    int cantidadRegistros = archiReparaciones.contarRegistros();
    if (cantidadRegistros <= 0) {return -1;} // No hay reparaciones cargadas

    Reparacion* vec = new Reparacion[cantidadRegistros]; // Creamos un arreglo din�mico de objetos para ordenar por cuit
    int cantMemDinamica = 0; // Va a tener la cantidad total de registros de la memoria din�mica

    for (int i = 0; i < cantidadRegistros; i++) {
        Reparacion reg = archiReparaciones.leerRegistro(i);
        // VALIDAMOS QUE LA REPARACION ESTE ACTIVA
        if (reg.getEstadovehiculo()) {
            vec[cantMemDinamica] = reg; // Guardamos el registro solo si est� activo
            cantMemDinamica++;
        }
    }

    // Ordenamos el archivo en memoria din�mica por n�mero de ID
    // i -> Posici�n de registro / x -> Posici�n de su siguiente registro
    for (int i = 0; i < cantMemDinamica - 1; i++) {
        // Recorremos el vector posicionandonos en el siguiente registro
        for (int x = i + 1; x < cantMemDinamica; x++) {
            // Si el primer registro es mayor, se intercambian
            if (vec[i].getIDReparaciones() > vec[x].getIDReparaciones()) {
                Reparacion aux = vec[i];
                vec[i] = vec[x];
                vec[x] = aux;
            }
        }
    }

    // Mostramos todos los registros del archivo
    for (int i = 0; i < cantMemDinamica; i++) {
        vec[i].Mostrar();
    }

    delete[] vec; // Liberamos memoria
}


int ArchivoReparaciones::listadoReparacionesPorCliente(){
    ArchivoReparaciones archiReparaciones;

    int cantidadRegistros = archiReparaciones.contarRegistros();
    if (cantidadRegistros <= 0) {return -1;} // No hay reparaciones cargadas

    Reparacion* vec = new Reparacion[cantidadRegistros]; // Creamos un arreglo din�mico de objetos para ordenar por cuit
    int cantMemDinamica = 0; // Va a tener la cantidad total de registros de la memoria din�mica

    for (int i = 0; i < cantidadRegistros; i++) {
        Reparacion reg = archiReparaciones.leerRegistro(i);
        // VALIDAMOS QUE LA REPARACION ESTE ACTIVA
        if (reg.getEstadovehiculo()) {
            vec[cantMemDinamica] = reg; // Guardamos el registro solo si est� activo
            cantMemDinamica++;
        }
    }

    // Ordenamos el archivo en memoria din�mica por n�mero de ID
    // i -> Posici�n de registro / x -> Posici�n de su siguiente registro
    for (int i = 0; i < cantMemDinamica - 1; i++) {
        // Recorremos el vector posicionandonos en el siguiente registro
        for (int x = i + 1; x < cantMemDinamica; x++) {
            // Si el primer registro es mayor, se intercambian
            if (strcmp(vec[i].getCuit(), vec[x].getCuit()) > 0) { // > 0 entonces la primer cadena es mayor a la segunda
                Reparacion aux = vec[i];
                vec[i] = vec[x];
                vec[x] = aux;
            }
        }
    }

    // Mostramos todos los registros del archivo
    for (int i = 0; i < cantMemDinamica; i++) {
        vec[i].Mostrar();
    }

    delete[] vec; // Liberamos memoria
}


int ArchivoReparaciones::listadoReparacionesPorVehiculo(){
    ArchivoReparaciones archiReparaciones;

    int cantidadRegistros = archiReparaciones.contarRegistros();
    if (cantidadRegistros <= 0) {return -1;} // No hay reparaciones cargadas

    Reparacion* vec = new Reparacion[cantidadRegistros]; // Creamos un arreglo din�mico de objetos para ordenar por cuit
    int cantMemDinamica = 0; // Va a tener la cantidad total de registros de la memoria din�mica

    for (int i = 0; i < cantidadRegistros; i++) {
        Reparacion reg = archiReparaciones.leerRegistro(i);
        // VALIDAMOS QUE LA REPARACION ESTE ACTIVA
        if (reg.getEstadovehiculo()) {
            vec[cantMemDinamica] = reg; // Guardamos el registro solo si est� activo
            cantMemDinamica++;
        }
    }

    // Ordenamos el archivo en memoria din�mica por n�mero de ID
    // i -> Posici�n de registro / x -> Posici�n de su siguiente registro
    for (int i = 0; i < cantMemDinamica - 1; i++) {
        // Recorremos el vector posicionandonos en el siguiente registro
        for (int x = i + 1; x < cantMemDinamica; x++) {
            if (strcmp(vec[i].getPatente(), vec[x].getPatente()) > 0) { // > 0 entonces la primer cadena es mayor a la segunda
                // Si el primer registro es mayor, se intercambian
                Reparacion aux = vec[i];
                vec[i] = vec[x];
                vec[x] = aux;
            }
        }
    }

    // Mostramos todos los registros del archivo
    for (int i = 0; i < cantMemDinamica; i++) {
        vec[i].Mostrar();
    }

    delete[] vec; // Liberamos memoria
}


int ArchivoReparaciones::listadoReparacionesPorImporte(){
    Reparacion reg;
    ArchivoReparaciones archiReparaciones;

    int cantidadRegistros = archiReparaciones.contarRegistros();
    if (cantidadRegistros <= 0) {return -1;} // No hay reparaciones cargadas

    Reparacion* vec = new Reparacion[cantidadRegistros]; // Creamos un arreglo din�mico de objetos para ordenar por cuit
    int cantMemDinamica = 0; // Va a tener la cantidad total de registros de la memoria din�mica

    for (int i = 0; i < cantidadRegistros; i++) {
        Reparacion reg = archiReparaciones.leerRegistro(i);
        // VALIDAMOS QUE LA REPARACION ESTE ACTIVA
        if (reg.getEstadovehiculo()) {
            vec[cantMemDinamica] = reg; // Guardamos el registro solo si est� activo
            cantMemDinamica++;
        }
    }

    // Ordenamos el archivo en memoria din�mica por n�mero de ID
    // i -> Posici�n de registro / x -> Posici�n de su siguiente registro
    for (int i = 0; i < cantMemDinamica - 1; i++) {
        // Recorremos el vector posicionandonos en el siguiente registro
        for (int x = i + 1; x < cantMemDinamica; x++) {
            // Si el primer registro es mayor, se intercambian
            if (vec[i].getImporte() > vec[x].getImporte()) {
                Reparacion aux = vec[i];
                vec[i] = vec[x];
                vec[x] = aux;
            }
        }
    }

    // Mostramos todos los registros del archivo
    for (int i = 0; i < cantMemDinamica; i++) {
        vec[i].Mostrar();
    }

    delete[] vec; // Liberamos memoria
}
