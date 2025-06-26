#pragma once
#include "clsReparacion.h"
#include "string.h"
#include "clsFecha.h"

class ArchivoReparaciones{
    private:
        char nombre[30];
        int tamanioRegistro;
    public:
        ArchivoReparaciones(const char *n="Reparaciones.dat"){
            strcpy(nombre, n);
            tamanioRegistro=sizeof(Reparacion);
        }
        int agregarRegistro(Reparacion reg);
        bool bajaLogica(int idReparacion, Fecha fechaBaja);
        int modificarRegistro(Reparacion reg, int pos);
        int contarRegistros();
        int buscarPosicion(int idReparacion);
        Reparacion leerRegistro(int pos);
        bool existePatenteActiva(const char* nroPatente);

        int listadoReparacionesPorId();
        int listadoReparacionesPorCliente();
        int listadoReparacionesPorVehiculo();
        int listadoReparacionesPorImporte();

        int consultaReparacionPorId(int idReparacion);
        int consultaReparacionPorCliente(const char* cuil);
        int consultaReparacionPorVehiculo(const char* nroPatente);
        int consultaReparacionPorRango(float importeUno, float importeDos);
        int consultaReparacionPorFecha(Fecha fechaUno, Fecha fechaDos);
        int consultaReparacionEnTaller();
};


