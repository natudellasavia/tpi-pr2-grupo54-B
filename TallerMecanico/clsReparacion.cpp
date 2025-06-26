#include <iostream>
#include <cstring>
#include "clsReparacion.h"
#include "funciones.h"
#include "clsArchivoVehiculos.h"
#include "clsArchivoClientes.h"
#include "clsArchivoReparaciones.h"
using namespace std;

/// CONSTRUCTOR POR OMISION
Reparacion::Reparacion(){
    _idReparaciones = 0;
    strcpy(_cuit, "");
    strcpy(_nroPatente, "");
    strcpy(_descripcionFalla, "");
    _importeReparacion = 0;
    _fechaIngreso;
    _fechaEntrega;
    _estado = true;
}


/// SETTERS
void Reparacion::setIDReparaciones(int idReparaciones){_idReparaciones = idReparaciones;}
void Reparacion::setCuit(const char* cuit){strncpy(_cuit, cuit, sizeof(_cuit));}
void Reparacion::setPatente(const char* nroPatente){strncpy(_nroPatente, nroPatente, sizeof(_nroPatente));}
void Reparacion::setFalla(const char* descripcionFalla){strncpy(_descripcionFalla, descripcionFalla, sizeof(_descripcionFalla));}
void Reparacion::setImporte(float importeReparacion){_importeReparacion = importeReparacion;}
void Reparacion::setFechaEntrada(Fecha fechaIngreso){_fechaIngreso = fechaIngreso;}
void Reparacion::setFechaSalida(Fecha fechaEngreso){_fechaEntrega = fechaEngreso;}
void Reparacion::setEstadovehiculo(bool estado){_estado = estado;}


/// GETTERS
int Reparacion::getIDReparaciones(){return _idReparaciones;}
const char* Reparacion::getCuit(){return _cuit;}
const char* Reparacion::getPatente(){return _nroPatente;}
const char* Reparacion::getFalla(){return _descripcionFalla;}
float Reparacion::getImporte(){return _importeReparacion;}
Fecha Reparacion::getFechaEntrada(){return _fechaIngreso;}
Fecha Reparacion::getFechaSalida(){return _fechaEntrega;}
bool Reparacion::getEstadovehiculo(){return _estado;}


/// MÉTODOS
bool Reparacion::Cargar(){
    ArchivoClientes archiClientes; // Abrimos el archivo clientes para validar el cuit
    bool cuitValido = false; // Lo usamos para el bucle de validación del cuit
    while (!cuitValido){
        cout << "INGRESE CUIT (INGRESE 0 PARA VOLVER ATRAS): ";
        cargarCadena(_cuit, sizeof(_cuit)-1);

        if (strcmp(_cuit, "0") == 0){return false;} // Si retorna 'false' en el menú NO va a entrar en la consulta de "estás seguro que desea cargar?"
        if (archiClientes.buscarPosicion(_cuit) == -1) {
            cout << "ERROR: No existe un cliente con el cuit '" << _cuit << "'." << endl << endl;
            system("pause");
            return false; // Si retorna 'false' en el menú NO va a entrar en la consulta de "estás seguro que desea cargar?"
        }else{
            cuitValido = true; // El cuit existe, cambiamos a true para salir del bucle
        }
    }

    ArchivoVehiculos archiVehiculos; // Abrimos el archivo vehiculos para validar la patente
    bool patenteValida = false; // Lo usamos para el bucle de validación de la patente
        cout << "INGRESE PATENTE: ";
        cargarCadena(_nroPatente, sizeof(_nroPatente)-1);
        pasarAMayusculas(_nroPatente);

        // VALIDAMOS QUE EXISTA UN VEHÍCULO CON ESA PATENTE
        if (archiVehiculos.existePatente(_nroPatente)){
            // VALIDAMOS QUE NO EXISTA UNA REPARACIÓN ACTIVA CON ESA PATENTE
            ArchivoReparaciones archiReparaciones;
            if(archiReparaciones.existePatenteActiva(_nroPatente)){
                cout << "ERROR: Ya existe una reparación activa con la patente '" << _nroPatente << "'." << endl << endl;
                system("pause");
                return false;
            }
        } else {
            cout << "ERROR: No existe un vehiculo con la patente '" << _nroPatente << "'." << endl << endl;
            system("pause");
            return false;
        }
    cout << "DESCRIPCION FALLA: ";
    cargarCadena(_descripcionFalla, sizeof(_descripcionFalla)-1);
    pasarAMayusculas(_descripcionFalla);
    bool importeCorrecto = false; // Para validar que el importe sea mayor a 0
    while(!importeCorrecto){
        cout << "IMPORTE REPARACIÓN: ";
        cin >> _importeReparacion;
        if(_importeReparacion > 0){
            importeCorrecto = true;
                cout << "FECHA INGRESO" << endl;
                if(_fechaIngreso.Cargar()){
                    _estado = true;
                }else{
                    return false;
                }
        }
    }
    return true;
}


void Reparacion::Mostrar(){
    cout << "ID: " << _idReparaciones;
    cout << "   CUIT: " << _cuit;
    cout << "   PATENTE: " << _nroPatente;
    cout << "   IMPORTE REPARACIÓN: " << _importeReparacion;
    cout << "   DESCRIPCION FALLA: " << _descripcionFalla;
    cout << "   FECHA INGRESO: ";
    _fechaIngreso.Mostrar();
    cout << "   FECHA ENTREGA: ";
    _fechaEntrega.Mostrar();
    cout << "   ESTADO: ";
    if (_estado){
        cout << "ACTIVO" << endl << endl;
    }else{
        cout << "INACTIVO" << endl << endl;
    }
}
