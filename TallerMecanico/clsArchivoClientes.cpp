#include <iostream>
#include <cstring>
#include "clsArchivoClientes.h"
#include "clsCliente.h"

using namespace std;


int ArchivoClientes::agregarRegistro(Cliente reg){
    FILE *pArchivo;
    pArchivo = fopen(nombre,"ab");
    if(pArchivo==nullptr){return -5;} // No pudo abrir el archivo

    int registrosEscritos = fwrite(&reg, sizeof(reg), 1, pArchivo);
    fclose(pArchivo);
    return registrosEscritos; // Devuelve 1 si escribi� correctamente, devuelve 0 si no escribi�
}


bool ArchivoClientes::bajaLogica(const char* cuit){
    Cliente reg;
    ArchivoClientes archiClientes;

    int pos = archiClientes.buscarPosicion(cuit); // Buscamos la posici�n
    if(pos == -1) return false; // No encontr� el cuit en el archivo
    reg = archiClientes.leerRegistro(pos); // Leemos el registro en la posici�n que le pasamos
    reg.setEstado(false); // Cambiamos el estado a 'false' para dar de baja
    return archiClientes.modificarRegistro(reg, pos); // Sobrescribimos el registro
}


int ArchivoClientes::modificarRegistro(Cliente reg, int pos){
    FILE *pArchivo;
    pArchivo = fopen(nombre,"rb+");
    if(pArchivo==nullptr){return -5;} // No pudo abrir el archivo

    fseek(pArchivo, pos*tamanioRegistro, SEEK_SET); // nos posicionamos en el registro deseado
    int registrosEscritos=fwrite(&reg, tamanioRegistro,1,pArchivo);

    fclose(pArchivo);
    return registrosEscritos; // El valor va a ser 1 si escribi� correctamente o 0 si no escribi�
}


int ArchivoClientes::contarRegistros() {
    FILE* pArchivo;
    pArchivo = fopen(nombre, "rb");
    if (pArchivo==nullptr){return -5;} // No pudo abrir el archivo

    fseek(pArchivo, 0, SEEK_END); // Nos posicionamos al final del registro
    int tamanioArchivo = ftell(pArchivo); // Cantidad de bytes desde el inicio del archivo hasta el puntero
    fclose(pArchivo);

    int cantRegistros = (tamanioArchivo/tamanioRegistro);
    return cantRegistros;
}


Cliente ArchivoClientes::leerRegistro(int pos) {
    Cliente reg;
    FILE* pArchivo;
    pArchivo = fopen(nombre, "rb");
    if (pArchivo==nullptr){return reg;} // Devolvemos sus atributos con los valores iniciales del constructor.

    fseek(pArchivo, pos * tamanioRegistro, SEEK_SET);
    fread(&reg, tamanioRegistro, 1, pArchivo);

    fclose(pArchivo);
    return reg;
}


int ArchivoClientes::buscarPosicion(const char* cuit) {
    FILE *pArchivo;
    pArchivo = fopen(nombre, "rb");
    if (pArchivo == nullptr) {return -5;} // No pudo abrir el archivo

    int cantidadRegistros = contarRegistros();
    Cliente reg;

    for (int i = 0; i < cantidadRegistros; i++) {
        fseek(pArchivo, i * tamanioRegistro, SEEK_SET); // Nos posicionamos al principio
        if (fread(&reg, tamanioRegistro, 1, pArchivo) != 1) {
            fclose(pArchivo);
            return -2; // No pudo leer el registro
        }
        if (strcmp(reg.getCuit(), cuit) == 0) {
            fclose(pArchivo);
            return i; // Si la encuentra, retorna la posici�n
        }
    }
    fclose(pArchivo);
    return -1; // No encontr� el cuit en el archivo
}



/// ------------------------- C O N S U L T A S -------------------------

int ArchivoClientes::consultaClientesPorCuil(const char* cuit){
    Cliente reg;
    ArchivoClientes archiClientes;
    int devuelve = -1;

    // Recorro el archivo de clientes y si lo encuentro muestro el registro por cuit
    int cantidadRegistros = archiClientes.contarRegistros();
    for(int i = 0; i < cantidadRegistros; i++){
        reg = archiClientes.leerRegistro(i);
        if(strcmp(reg.getCuit(), cuit) == 0){
            reg.Mostrar();
            devuelve++; // Acumula +1 para indicar que s� encontr� registro al momento de retornar
        }
    }

    return devuelve; // Si no encontr� ningun registro devuelve -1
}


int ArchivoClientes::consultaClientesPorTipo(int tipo){
    Cliente reg;
    ArchivoClientes archiClientes;
    int devuelve = -1;

    // Recorro el archivo de clientes y si lo encuentro muestro el registro por tipo
    int cantidadRegistros = archiClientes.contarRegistros();
    for(int i = 0; i < cantidadRegistros; i++){
        reg = archiClientes.leerRegistro(i);
        if(reg.getTipoCliente() == tipo){
            reg.Mostrar();
            devuelve++; // Acumula +1 para indicar que s� encontr� registro al momento de retornar
        }
    }

    return devuelve; // Si no encontr� ningun registro devuelve -1
}



/// ------------------------- L I S T A D O S -------------------------

int ArchivoClientes::listadoClientesPorCuit() {
    ArchivoClientes archiClientes;

    int cantidadRegistros = archiClientes.contarRegistros();
    if (cantidadRegistros <= 0) {return -1;} // No hay reparaciones cargadas

    Cliente* vec = new Cliente[cantidadRegistros]; // Creamos un arreglo din�mico de objetos para ordenar por cuit
    int cantMemDinamica = 0; // Va a tener la cantidad total de registros de la memoria din�mica

    for (int i = 0; i < cantidadRegistros; i++){
        Cliente reg = archiClientes.leerRegistro(i);
        // VALIDAMOS QUE LA REPARACION ESTE ACTIVA
        if (reg.getEstado()) {
                vec[cantMemDinamica] = reg; // Guardamos el registro solo si est� activo
                cantMemDinamica++;
        }
    }

    // Ordenamos el archivo en memoria din�mica por cuit
    // i -> Posici�n de registro / x -> Posici�n de su siguiente registro
    for(int i = 0; i < cantMemDinamica - 1; i++){
        // Recorremos el vector posicionandonos en el siguiente registro
        for(int x = i + 1; x < cantMemDinamica; x++){
            if(strcmp(vec[i].getCuit(), vec[x].getCuit()) > 0){ // > 0 entonces la primer cadena es mayor a la segunda
                // Si el primer registro es mayor, se intercambian
                Cliente aux = vec[i];
                vec[i] = vec[x];
                vec[x] = aux;
            }
        }
    }

    // Mostramos todos los registros del archivo
    for(int i = 0; i < cantMemDinamica; i++){
        vec[i].Mostrar();
    }

    delete[] vec;
}


int ArchivoClientes::listadoClientesPorApellido() {
    ArchivoClientes archiClientes;

    int cantidadRegistros = archiClientes.contarRegistros();
    if (cantidadRegistros <= 0) {return -1;} // No hay reparaciones cargadas

    Cliente* vec = new Cliente[cantidadRegistros]; // Creamos un arreglo din�mico de objetos para ordenar por apellido
    int cantMemDinamica = 0; // Va a tener la cantidad total de registros de la memoria din�mica

    for (int i = 0; i < cantidadRegistros; i++) {
        Cliente reg = archiClientes.leerRegistro(i);
        // VALIDAMOS QUE LA REPARACION ESTE ACTIVA
        if (reg.getEstado()) {
            vec[cantMemDinamica] = reg;  // Guardamos el registro solo si est� activo
            cantMemDinamica++;
        }
    }

    // Ordenamos el archivo en memoria din�mica (con empresa) por nombre
    // i -> Posici�n de registro / x -> Posici�n de su siguiente registro
    for (int i = 0; i < cantMemDinamica - 1; i++) {
        for (int x = i + 1; x < cantMemDinamica; x++) {
            if (strcmp(vec[i].getApellido(), vec[x].getApellido()) > 0) {
                Cliente aux = vec[i];
                vec[i] = vec[x];
                vec[x] = aux;
            }
        }
    }

    // Mostramos todos los registros del archivo (tipo particular)
    for (int i = 0; i < cantMemDinamica; i++) {
        vec[i].Mostrar();
    }

    delete[] vec;
}


int ArchivoClientes::listadoClientesPorTipo() {
    ArchivoClientes archiClientes;
    int cantidadRegistros = archiClientes.contarRegistros();
    if (cantidadRegistros <= 0) {return -1;} // No hay reparaciones cargadas

    Cliente* vec = new Cliente[cantidadRegistros]; // Creamos un arreglo din�mico de objetos para ordenar por tipo
    int cantMemDinamica = 0; // Va a tener la cantidad total de registros de la memoria din�mica

    for (int i = 0; i < cantidadRegistros; i++) {
        Cliente reg = archiClientes.leerRegistro(i);
        // VALIDAMOS QUE LA REPARACION ESTE ACTIVA
        if (reg.getEstado()==true) {
            vec[cantMemDinamica] = reg; // Guardamos el registro solo si est� activo
            cantMemDinamica++;
        }
    }

    // Ordenamos el archivo en memoria din�mica por tipo de cliente
    // i -> Posici�n de registro / x -> Posici�n de su siguiente registro
    for (int i = 0; i < cantMemDinamica - 1; i++) {
        for (int x = i + 1; x < cantMemDinamica; x++) {
            if (vec[i].getTipoCliente() > vec[x].getTipoCliente()) {
                Cliente aux = vec[i];
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
