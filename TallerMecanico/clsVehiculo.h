#pragma once

class Vehiculo {
    private:
        char _nroPatente[8];
        char _marca[31];
        int _tipoVehiculo;
        bool _estado;
    public:
        /// CONSTRUCTOR POR OMISION
        Vehiculo();

        /// SETTERS
        void setNroPatente(const char* nroPatente);
        void setMarca(const char* marca);
        void setTipoVehiculo(int tipoVehiculo);
        void setEstado(bool estado);

        /// GETTERS
        const char* getNroPatente();
        const char* getMarca();
        int getTipoVehiculo();
        bool getEstado();

        /// MÉTODOS
        bool Cargar();
        void Mostrar();
        void Modificar();
};

