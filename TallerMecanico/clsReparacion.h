#pragma once
#include "clsFecha.h"
#include "funciones.h"

class Reparacion{
    private:
        int _idReparaciones;
        char _cuit[12];
        char _nroPatente[8];
        char _descripcionFalla[1000];
        float _importeReparacion;
        Fecha _fechaIngreso;
        Fecha _fechaEntrega;
        bool _estado;
    public:
        /// AGREGAR CONSTRUCTOR POR OMISION
        Reparacion();

        ///SETTERS
        void setIDReparaciones(int idReparaciones);
        void setCuit(const char* cuit);
        void setPatente(const char* nroPatente);
        void setFalla(const char* descripcionFalla);
        void setImporte(float importeReparacion);
        void setFechaEntrada(Fecha fechaIngreso);
        void setFechaSalida(Fecha fechaEngreso);
        void setEstadovehiculo(bool estado);

        ///GETTERS
        int getIDReparaciones();
        const char* getCuit();
        const char* getPatente();
        const char* getFalla();
        float getImporte();
        Fecha getFechaEntrada();
        Fecha getFechaSalida();
        bool getEstadovehiculo();

        /// MÉTODOS
        bool Cargar();
        void Mostrar();
};

