#include <iostream>
#include <cstring>
#include <cctype>
#include "clsCliente.h"
#include "clsArchivoClientes.h"
#include "funciones.h"
using namespace std;

/// CONSTRUCTOR POR OMISION
Cliente::Cliente(){
    strcpy(_cuit, "");
    strcpy(_nombre, "");
    strcpy(_apellido, "");
    strcpy(_celular, "");
    strcpy(_email, "");
    strcpy(_direccion, "");
    _tipoCliente = 1; // 1=PARTICULAR 2=EMPRESA
    _estado = true;
}


/// SETTERS
void Cliente::setCuit(const char* cuit){strcpy(_cuit, cuit);}
void Cliente::setNombre(const char* nombre){strcpy(_nombre, nombre);}
void Cliente::setApellido(const char* apellido){strcpy(_apellido, apellido);}
void Cliente::setCelular(const char* celular){strcpy(_celular, celular);}
void Cliente::setEmail(const char* email){strcpy(_email, email);}
void Cliente::setDireccion(const char* direccion){strcpy(_direccion, direccion);}
void Cliente::setTipoCliente(int tipoCliente){
    if (tipoCliente != 1 && tipoCliente != 2) {
        cout << "Tipo de cliente inválido. Debe ser 1 o 2."<<endl;
        return;
    }
    _tipoCliente = tipoCliente;
}
void Cliente::setEstado(bool estado){_estado = estado;}


/// GETTERS
const char* Cliente::getCuit(){return _cuit;}
const char* Cliente::getNombre(){return _nombre;}
const char* Cliente::getApellido(){return _apellido;}
const char* Cliente::getCelular(){return _celular;}
const char* Cliente::getEmail(){return _email;}
const char* Cliente::getDireccion(){return _direccion;}
int Cliente::getTipoCliente(){return _tipoCliente;}
bool Cliente::getEstado(){return _estado;}


/// MÉTODOS
bool Cliente::Cargar() {
    ArchivoClientes archiClientes; // Abrimos el archivo clientes para validar el cuit
    bool cuitValido = false; // Lo usamos para el bucle de validación del cuit
    //const char esCero[15] = {};

    while (!cuitValido){
        cout << "INGRESE CUIT (INGRESE 0 PARA VOLVER ATRAS): ";
        cargarCadena(_cuit, sizeof(_cuit)-1);
        if(strcmp(_cuit, "0") == 0){
            return false; // Si retorna 'false' en el menú NO va a entrar en la consulta de "estás seguro que desea cargar?"
        }else if(*_cuit == '\0'){
            cout << "ERROR: El CUIT no puede estar vacio." << endl; // Validamos que el cuit no esté vacío
            return false;
        }

        int pos = archiClientes.buscarPosicion(_cuit);
        if(pos >= 0){
            Cliente reg = archiClientes.leerRegistro(pos);

            // VALIDAMOS EL ESTADO DEL CLIENTE EXISTENTE
            if(reg.getEstado() == true){
                cout << "ERROR: Ya existe un cliente con el cuit '" << _cuit << "'. Intente nuevamente." << endl << endl;
            }else{
                bool seleccionCorrecta = false;
                while(!seleccionCorrecta){

                    cout << "El cliente con CUIT '" << _cuit << "' esta dado de baja. Desea activarlo? 1->SI / 2->NO : ";
                    int opc;
                    cin >> opc;
                    switch(opc){
                        case 1: {reg.setEstado(true);
                                archiClientes.modificarRegistro(reg, pos);
                                cout << "Cliente reactivado exitosamente." << endl << endl;
                                seleccionCorrecta = true;
                                system("pause");
                                return false;
                                break;}
                        case 2: seleccionCorrecta = true;
                                return false;
                                break;
                        default: cout << "ERROR: La seleccion no es correcta." << endl << endl;
                                 system("pause");
                                 system("cls");
                                 break;
                    }
                }
            }
        }else{cuitValido = true;} // El cuit existe, cambiamos a true para salir del bucle
    }
    cout << "NOMBRE: ";
    cargarCadena(_nombre, 29);
    pasarAMayusculas(_nombre); // Para comparar en la modificación y ordenar en los listados
    cout << "APELLIDO: ";
    cargarCadena(_apellido, 29);
    pasarAMayusculas(_apellido); // Para comparar en la modificación y ordenar en los listados
    cout << "CELULAR: ";
    cargarCadena(_celular, 14);
    cout << "EMAIL: ";
    cargarCadena(_email, 29);
    pasarAMayusculas(_email); // Para comparar en la modificación
    cout << "DIRECCION: ";
    cargarCadena(_direccion, 49);
    pasarAMayusculas(_direccion); // Para comparar en la modificación
    cout << "TIPO DE CLIENTE (1->Particular, 2->Empresa): ";
    cin >> _tipoCliente;
    setEstado(true);

    return true;
}


void Cliente::Mostrar(){
    cout << "CUIT: " << _cuit;
    cout << "   APELLIDO Y NOMBRE: " << _apellido;
    cout << ", " << _nombre;
    cout << "   CELULAR: " << _celular;
    cout <<"     EMAIL: " << _email;
    cout << "     DIRECCION: " << _direccion;
    cout << "     TIPO DE CLIENTE: " << _tipoCliente;
    if (_tipoCliente==1){
       cout << "-Particular";}
    else{
        cout<<"-Empresa";
    };
    cout << "     ESTADO: ";

    if (_estado){
        cout << "Activo" << endl << endl;
    }else{
        cout << "Inactivo" << endl << endl;
    }
}
