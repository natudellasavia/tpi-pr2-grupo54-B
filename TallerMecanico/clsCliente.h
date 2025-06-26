#pragma once

class Cliente{
    private:
        char _cuit[15];
        char _nombre[30];
        char _apellido[30];
        char _celular[15];
        char _email[30];
        char _direccion[50];
        int _tipoCliente;
        bool _estado;

    public:
        /// CONSTRUCTOR POR OMISION
        Cliente();

        /// SETTERS
        void setCuit(const char* cuit);
        void setNombre(const char* nombre);
        void setApellido(const char* apellido);
        void setCelular(const char* celular);
        void setEmail(const char* email);
        void setDireccion(const char* direccion);
        void setTipoCliente(int tipoCliente);
        void setEstado(bool estado);

        /// GETTERS
        const char* getCuit();
        const char* getNombre();
        const char* getApellido();
        const char* getCelular();
        const char* getEmail();
        const char* getDireccion();
        int getTipoCliente();
        bool getEstado();

        /// MÉTODOS
        bool Cargar();
        void Mostrar();
};
