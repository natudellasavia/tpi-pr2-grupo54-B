#include <iostream>
#include <cstring>
#include "clsVehiculo.h"
#include "funciones.h"
#include "clsArchivoVehiculos.h"
using namespace std;


/// CONSTRUCTOR POR OMISION
Vehiculo::Vehiculo() {
    strcpy(_nroPatente, "");
    strcpy(_marca, "");
    _tipoVehiculo = 0;
    _estado = true;
}


/// SETTERS
void Vehiculo::setNroPatente(const char* nroPatente){strncpy(_nroPatente, nroPatente, sizeof(_nroPatente));}
void Vehiculo::setMarca(const char* marca){strncpy(_marca, marca, sizeof(_marca));}
void Vehiculo::setTipoVehiculo(int tipoVehiculo){_tipoVehiculo = tipoVehiculo;}
void Vehiculo::setEstado(bool estado){_estado = estado;}


/// GETTERS
const char* Vehiculo::getNroPatente(){return _nroPatente;}
const char* Vehiculo::getMarca(){return _marca;}
int Vehiculo::getTipoVehiculo(){return _tipoVehiculo;}
bool Vehiculo::getEstado(){return _estado;}


/// MÉTODOS
bool Vehiculo::Cargar(){
    ArchivoVehiculos archiVehiculos;
    bool patenteValida = false;
    while(!patenteValida){
        cout << "PATENTE (INGRESE 0 PARA VOLVER ATRAS): ";
        cargarCadena(_nroPatente, sizeof(_nroPatente));
        pasarAMayusculas(_nroPatente); // Para comparar en la modificación y ordenar en los listados
        if(strcmp(_nroPatente, "0") == 0){
            return false; // Si retorna 'false' en el menú NO va a entrar en la consulta de "estás seguro que desea cargar?"
        }else if(*_nroPatente == '\0'){
            cout << "ERROR: La patente no puede estar vacia." << endl << endl; // Validamos que la patente no esté vacía
            system("pause");
            return false;
        }

        // Validamos si ya existe la patente
        if(archiVehiculos.existePatente(_nroPatente)){
            cout << "ERROR: Ya existe un vehiculo con la patente '" << _nroPatente << "'." << endl << endl;
            system("pause");
            return false;
        }else{patenteValida = true;} // La patente es única, cambiamos a true para salir del bucle
    }
    cout << "MARCA: ";
    cargarCadena(_marca, sizeof(_marca));
    pasarAMayusculas(_marca); // Para comparar en la modificación y ordenar en los listados
    int tipo;
    bool tipoValido = false;
    // Validamos el tipo de vehículo
    while(!tipoValido){
        cout << "TIPO DE VEHICULO (1-Auto / 2-Camioneta / 3-Camion / 4-Micro Omnibus): ";
        cin >> tipo;
        if (tipo < 1 || tipo > 4) {
            cout << "ERROR: Entrada inválida. Por favor, ingrese un número entre 1 y 4." << endl << endl;
            system("pause");
            system("cls");
            cout << "PATENTE: " << _nroPatente << endl;
            cout << "MARCA: " << _marca << endl;
        } else {
            _tipoVehiculo = tipo;
            tipoValido = true; // Si es correcto el tipo salimos del bucle
        }
    }
    setEstado(true);
}


void Vehiculo::Mostrar(){
    cout << "PATENTE: " << _nroPatente;
    cout << "   MARCA: " << _marca;
    cout << "   TIPO DE VEHICULO: ";
    switch (_tipoVehiculo) {
        case 1: cout << "Auto"; break;
        case 2: cout << "Camioneta"; break;
        case 3: cout << "Camion"; break;
        case 4: cout << "Micro Omnibus"; break;
        default: cout << "Error, volver a ingresar"; break;
    }
    cout << "   ESTADO: ";
    if (_estado){
        cout << "ACTIVO" << endl << endl;
    }else{
        cout << "INACTIVO" << endl << endl;
    }
}
