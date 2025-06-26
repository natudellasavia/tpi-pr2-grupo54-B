#pragma once

class Fecha{
    private:
        int _dia;
        int _mes;
        int _anio;
    public:
        Fecha(int d=0, int m=0, int a=0000);
        void setDia(int d);
        void setMes(int m);
        void setAnio(int a);
        int getDia();
        int getMes();
        int getAnio();
        bool Cargar();
        void Mostrar();
};
