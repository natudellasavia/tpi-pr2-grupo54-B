#include <iostream>
#include "clsFecha.h"
using namespace std;


///CONSTRUCTOR POR OMISION
Fecha::Fecha(int d, int m, int a){
    _dia = d;
    _mes = m;
    _anio = a;
}


///SETTERS
void Fecha::setDia(int d){_dia = d;}
void Fecha::setMes(int m){_mes = m;}
void Fecha::setAnio(int a){_anio = a;}


/// GETTERS
int Fecha::getDia(){return _dia;}
int Fecha::getMes(){return _mes;}
int Fecha::getAnio(){return _anio;}


/// MÉTODOS
bool Fecha::Cargar(){
    int d, m, a;

        cout << "DIA: ";
        cin >> d;
        if(d > 0 && d <= 31){
            _dia = d;
            cout << "MES: ";
            cin >> m;
            if(m > 0 && m <= 12){
                _mes = m;
                cout << "ANIO: ";
                cin >> a;
                if(a > 0){
                    _anio = a;
                    return true;
                }else{
                    cout << "ERROR: Fecha incorrecta." << endl;
                    system("pause");
                    system("cls");
                    return false;
                }
            }else{
                cout << "ERROR: Fecha incorrecta." << endl;
                system("pause");
                system("cls");
                return false;
            }
        }else{
            cout << "ERROR: Fecha incorrecta." << endl;
            system("pause");
            system("cls");
            return false;
        }
}

void Fecha::Mostrar(){
    cout << _dia << "/" << _mes << "/" << _anio;
}
