#pragma once
#include "clsCliente.h"
#include "string.h"

class ArchivoClientes{
    private:
        char nombre[30];
        int tamanioRegistro;
    public:
        ArchivoClientes(const char* n="Clientes.dat"){
            strcpy(nombre, n);
            tamanioRegistro=sizeof(Cliente);
        }
        int agregarRegistro(Cliente reg);
        bool bajaLogica(const char* cuil);
        int modificarRegistro(Cliente reg, int pos);
        int contarRegistros();
        Cliente leerRegistro(int pos);
        int buscarPosicion(const char* cuit);

        int listadoClientesPorCuit();
        int listadoClientesPorApellido();
        int listadoClientesPorTipo();

        int consultaClientesPorCuil(const char* cuil);
        int consultaClientesPorTipo(int tipo);
};


