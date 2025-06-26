#include<iostream>
#include <clocale>
#include "MenuVehiculos.h"
#include "clsArchivoVehiculos.h"
#include "clsArchivoReparaciones.h"
#include "clsVehiculo.h"
#include "funciones.h"
using namespace std;

int menuVehiculos(){
    setlocale(LC_ALL, "Spanish");
	int opc;
    while(true){
        system("cls");
        cout << "--------- VEHICULOS ----------" << endl;
        cout << "1. ALTA VEHICULO" << endl;
        cout << "2. BAJA VEHICULO" << endl;
        cout << "3. MODIFICAR VEHICULO" << endl;
        cout << endl;
        cout << "0. VOLVER AL MENU PRINCIPAL" << endl;
        cout << "------------------------------" << endl;
        cout << "SELECCIONAR OPCION: ";
        cin>>opc;
        system("cls");
        switch(opc){
            case 1: altaVehiculo();
                    break;
            case 2: bajaVehiculo();
                    break;
            case 3: modificarVehiculo();
                    break;
            case 0: return 0;
                    break;
            default: cout << "ERROR: La selección no es correcta." << endl << endl;
            system("pause");
        }
    }
    return 0;
}


void altaVehiculo(){
    cout << "--- ALTA VEHICULO ---" << endl;
    Vehiculo reg;
    bool bandera = reg.Cargar();
    ArchivoVehiculos archiVehiculos;

    int opc;
    while(bandera){
        cout << endl << "¿Está seguro que desea de dar de alta? 1->SI / 2->NO : ";
        cin >> opc;
        if(opc == 1){
            int agrego = archiVehiculos.agregarRegistro(reg); // Guardamos el resultado de la función agregarRegistro para saber que pasó
                switch(agrego){
                    case -5: cout << "ERROR: No se pudo encontrar el archivo." << endl << endl;
                             break;
                    case 0: cout << "ERROR: No se pudo cargar el vehículo." << endl << endl;
                            break;
                    case 1: cout << "Vehículo cargado exitosamente." << endl << endl;
                            break;
                }
            bandera = false; // Cambia a false para salir del bucle
        }else if(opc == 2){
            bandera = false; // Cambia a false para salir del bucle
        }
        system("pause");
    }
}


void bajaVehiculo(){
    Vehiculo regV;
    Reparacion regR;
    ArchivoVehiculos archiVehiculos;
    ArchivoReparaciones archiReparaciones;
    char patenteBaja[8];

        system("cls");
        cout << "--- BAJA DE VEHICULO ---" << endl;
        cout << "INGRESE LA PATENTE DEL VEHICULO A DAR DE BAJA (INGRESE 0 PARA VOLVER ATRAS): " ;

        cargarCadena(patenteBaja, sizeof(patenteBaja)-1);
        pasarAMayusculas(patenteBaja);
        if(strcmp(patenteBaja, "0") == 0){return;} // Si ingresan 0 vuelve para atrás

        // VALIDAMOS QUE LA PATENTE EXISTA EN EL ARCHIVO
        int pos = archiVehiculos.buscarPosicion(patenteBaja); // -1 no encontró la patente / -2 no pudo leer el registro
        if(pos == -1 || pos == -2){
            cout << "ERROR: No existe un vehículo con la patente '" << patenteBaja <<"'." << endl << endl;
        }else{
            regV = archiVehiculos.leerRegistro(pos); // Nos guardamos los valores del registro
            // VALIDAMOS QUE NO ESTÉ DADO DE BAJA EL VEHÍCULO
            if(regV.getEstado() == true){
                // VALIDAMOS QUE EL VEHICULO NO ESTÉ EN UNA REPARACIÓN ACTIVA

                int tamanio = archiReparaciones.contarRegistros(); // Cantidad de registros del archivo reparaciones
                int contador = 0; // Lo usamos para verificar que el cliente no esté en un registro Reparaciones activo
                char patenteComparar[8];
                for(int i = 0; i < tamanio; i++){ // Recorremos el archivo Reparaciones
                    regR = archiReparaciones.leerRegistro(i);
                    strcpy(patenteComparar, regR.getPatente()); // Guardamos la patente del registro de Reparaciones
                    if(strcmp(patenteBaja, patenteComparar) == 0){ // Vemos si las patentes son iguales
                        // Vemos el estado del registro
                        if(regR.getEstadovehiculo() == true){
                            contador++; // La reparación no está dada de baja entonces acumulamos para saber que no podemos dar de baja
                        }
                    }
                }

                if(contador == 0){ // Si es 0 significa que no se encontraron reparaciones de alta con la misma patente
                    bool seleccionCorrecta = false;
                    while(!seleccionCorrecta){
                        system("cls");
                        cout << "--- DATOS DEL VEHICULO A DAR DE BAJA ---" << endl;
                        regV.Mostrar();
                        int confirmacion;
                        cout << endl << "Está seguro que desea dar de baja este vehículo? 1->SI / 2->NO : ";
                        cin >> confirmacion;
                        switch(confirmacion){
                            case 1:{ bool dioBaja;
                                     dioBaja = archiVehiculos.bajaLogica(patenteBaja); // Realizamos la baja en el archivo
                                     if(dioBaja == true){
                                         cout << "Vehículo dado de baja exitosamente." << endl;
                                     }else{
                                         cout << "ERROR: No se pudo guardar la baja del vehículo." << endl;
                                     }
                                     break;}
                            case 2: cout << "Operación de baja cancelada." << endl << endl;
                                    seleccionCorrecta = true;
                                    break;
                            default: cout << "ERROR: La selección no es correcta." << endl << endl;
                                    system("pause");
                                    break;
                        }
                    }
                }else{
                    cout << "ERROR: El vehículo con patente '" << patenteBaja << "' aún está en el taller." << endl << endl;
                }
            }else{
                cout << "ERROR: El vehículo con la patente" << patenteBaja << " ya había sido dado de baja anteriormente." << endl << endl;
            }
        }
        system("pause");
}


void modificarVehiculo(){
    ArchivoVehiculos archiVehiculos;
    Vehiculo reg;
    char patenteAModificar[8] = {};
    bool bandera = false;
    while(!bandera){
        system("cls");
        cout << "--- MODIFICAR VEHICULO ---" << endl;
        cout << "INGRESE LA PATENTE DEL VEHICULO A MODIFICAR (INGRESE 0 PARA VOLVER ATRAS): ";
        cargarCadena(patenteAModificar, sizeof(patenteAModificar)-1);
        pasarAMayusculas(patenteAModificar);
        if(strcmp(patenteAModificar, "0") == 0){return;} // Si ingresan 0 vuelve para atrás

        // VALIDAMOS QUE LA PATENTE EXISTA EN EL ARCHIVO
        int pos = archiVehiculos.buscarPosicion(patenteAModificar); // Devuelve -1 no encontró la patente y -2 no pudo leer el registro
        if(pos == -1 || pos == -2){
            cout << "ERROR: No existe un vehículo con la patente: " << patenteAModificar << ". Intente nuevamente." << endl << endl;
            system("pause");
        }else{
            bandera = true; // Salimos del bucle
        }
    }

    // VALIDAMOS QUE EL VEHICULO ESTÉ ACTIVO
    int pos = archiVehiculos.buscarPosicion(patenteAModificar); // Conseguimos la posición (sabemos que va a encontrarla porque ya lo hizo antes)
    reg = archiVehiculos.leerRegistro(pos); // Traemos la información del registro
    if(reg.getEstado() == false){
        cout << "ERROR: El vehículo fue dado de baja, no se pueden realizar modificaciones." << endl << endl;
        system("pause");
        return;
    }

    // SI LAS VALIDACIONES PATENTE EXISTE Y VEHÍCULO ACTIVO ESTAN OK, SE PASA AL SIGUIENTE MENÚ
    int opc;
    int salir = 1;
    while(salir != 0){
        system("cls");
        cout << "--- MODIFICAR DEL VEHICULO ---" << endl;
        cout << "PATENTE: " << patenteAModificar << endl;
        cout << "1. MODIFICAR MARCA" << endl;
        cout << "2. MODIFICAR TIPO DE VEHICULO" << endl;
        cout << endl;
        cout << "0. VOLVER A MENU VEHICULO" << endl;
        cout << "-------------------------------" << endl;
        cout << "SELECCIONAR OPCION: ";
        cin >> opc;
        system("cls");

        bool seModifico = false; // Para saber si se realizó alguna modificación

        switch(opc){
            case 1:{ cout << "--- MODIFICAR MARCA ---" << endl;
                char nuevaMarca[30];
                char marcaExistente[30] = {}; // Para traernos la marca del registro
                strcpy(marcaExistente, reg.getMarca()); // Traemos la marca del registro
                cout << "INGRESE LA NUEVA MARCA: ";
                cargarCadena(nuevaMarca, sizeof(nuevaMarca)-1);
                pasarAMayusculas(nuevaMarca);
                if(strcmp(nuevaMarca, marcaExistente) != 0){
                    reg.setMarca(nuevaMarca); // Guardamos la nueva marca
                    seModifico = true;
                }else{
                    cout << "ATENCION: La marca ingresada es igual a la existente." << endl << endl;
                    system("pause");
                }
                break;}
            case 2:{
                int nuevoTipo;
                bool tipoCorrecto = false;
                while(!tipoCorrecto){
                    cout << "--- MODIFICAR TIPO DE VEHICULO ---" << endl;
                    cout << "INGRESE EL NUEVO TIPO DE VEHICULO (1:Auto, 2:Camioneta, 3:Camion, 4:Micro Omnibus): ";
                    cin >> nuevoTipo;
                    if(nuevoTipo >= 1 && nuevoTipo <= 4){
                        if(nuevoTipo != reg.getTipoVehiculo()){
                            reg.setTipoVehiculo(nuevoTipo); // Guardamos el nuevo tipo de vehículo
                            seModifico = true;
                            tipoCorrecto = true;
                        }else{
                            cout << "ATENCION: El tipo vehículo ingresado es igual al existente." << endl << endl;
                            tipoCorrecto = true;
                            system("pause");
                        }
                    }else{
                        cout << "ERROR: Entrada invalida. Por favor, ingrese un numero entre 1 y 4." << endl << endl;
                        system("pause");
                        system("cls");
                    }
                }
                break;}
            case 0: salir = 0;
                    break;
            default: cout << "ERROR: La selección no es correcta.";
                    break;
        }

        if(seModifico){
            int exitoModificacion = archiVehiculos.modificarRegistro(reg, pos);
            if(exitoModificacion == 1){
                cout << "El vehículo fue modificado con éxito." << endl << endl;
                system("pause");
            }else{
                cout << "ERROR: No se pudo modificar el vehículo en el archivo." << endl << endl;
                system("pause");
            }
        }
    }
}



