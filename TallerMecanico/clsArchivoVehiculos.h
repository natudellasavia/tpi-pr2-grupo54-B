#pragma once
#include "clsVehiculo.h"
#include "string.h"

class ArchivoVehiculos{
    private:
        char nombre[30];
        int tamanioRegistro;

    public:
        ArchivoVehiculos(const char *n="Vehiculos.dat"){
            strcpy(nombre, n);
            tamanioRegistro=sizeof(Vehiculo);
        }
        int agregarRegistro(Vehiculo reg);
        bool bajaLogica(const char* nroPatente);
        int contarRegistros();
        int buscarPosicion(const char* nroPatente);
        int modificarRegistro(Vehiculo reg, int pos);
        bool modificarVehiculoEnArchivo();
        bool darDeBajaVehiculoEnArchivo();
        Vehiculo leerRegistro(int pos);
        bool existePatente(const char* nroPatente);

        int listadoVehiculosPorMarca();
        int listadoVehiculosPorTipoDeVehiculo();

        int consultaVehiculoPorPatente(const char* nroPatente);
        int consultaVehiculoPorTipo(int tipoVehiculo);
        int consultaVehiculoEnTaller();

};


