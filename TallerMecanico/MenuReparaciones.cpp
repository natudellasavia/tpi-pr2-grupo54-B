#include <iostream>
#include <clocale>
#include "clsArchivoReparaciones.h"
#include "clsArchivoVehiculos.h"
#include "MenuReparaciones.h"
#include "clsReparacion.h"
using namespace std;

int menuReparaciones(){
    setlocale(LC_ALL, "Spanish");
	int opc;
    while(true){
        system("cls");
        cout << "--------- REPARACIONES ----------" << endl;
        cout << "1. ALTA REPARACION" << endl;
        cout << "2. BAJA REPARACION" << endl;
        cout << "3. MODIFICAR REPARACION" << endl;
        cout << endl;
        cout << "0. VOLVER AL MENU PRINCIPAL" << endl;
        cout << "---------------------------------" << endl;
        cout << "SELECCIONAR OPCION: ";
        cin>>opc;
        system("cls");
        switch(opc){
            case 1: altaReparacion();
                    break;
            case 2: bajaReparacion();
                    break;
            case 3: modificarReparacion();
                    break;
            case 0: return 0;
                    break;
            default: cout<<"LA SELECCION NO ES CORRECTA"<<endl;
            system("pause");
        }
    }
    return 0;
}


void altaReparacion(){
    cout << "--- ALTA REPARACION ---" << endl;
    Reparacion reg;
    bool bandera = reg.Cargar();
    ArchivoReparaciones archiReparaciones;

    int opc;
    while(bandera){
        cout << endl << "�Est� seguro que desea de dar de alta? 1->SI / 2->NO : ";
        cin >> opc;
        if(opc == 1){
            int agrego = archiReparaciones.agregarRegistro(reg); // Guardamos el resultado de la funci�n agregarRegistro para saber que pas�
                switch(agrego){
                    case -5: cout << "ERROR: No se pudo encontrar el archivo." << endl << endl;
                             break;
                    case 0: cout << "ERROR: No se pudo cargar la reparaci�n." << endl << endl;
                            break;
                    case 1: cout << "Reparaci�n cargada exitosamente." << endl << endl;
                            break;
                }
            bandera = false; // Cambia a false para salir del bucle
        }else if(opc == 2){
            bandera = false; // Cambia a false para salir del bucle
        }
        system("pause");
    }
}


void bajaReparacion(){
    ArchivoReparaciones archiReparaciones;
    ArchivoVehiculos archiVehiculos;
    Reparacion regR;
    Vehiculo regV;

    cout << "--- BAJA DE REPARACION ---" << endl;
    cout << "INGRESE EL ID DE LA REPARACION A DAR DE BAJA (INGRESE 0 PARA VOLVER ATRAS): " ;
    int idBaja;
    cin >> idBaja;
    if (idBaja == 0){return;} // Si ingresan 0 vuelve para atr�s
    cout << endl;

    // VALIDAMOS QUE EL ID EXISTA EN EL ARCHIVO
    int pos = archiReparaciones.buscarPosicion(idBaja); // -1 no encontr� el id / -2 no pudo leer el registro
    if(pos == -1 || pos == -2){
        cout << "ERROR: No existe una reparaci�n con el id: " << idBaja << endl << endl;
    }else{
        regR = archiReparaciones.leerRegistro(pos); // Nos guardamos los valores del registro reparacion
        char patente[8] = {};
        strcpy(patente, regR.getPatente()); // Nos traemos la patente del registro veh�culo

        // VALIDAMOS QUE NO EST� DADA DE BAJA LA REPARACI�N
        if(regR.getEstadovehiculo() == true){
            cout << "INGRESE LA FECHA QUE SALIO DEL TALLER: " << endl;
            Fecha fechaBaja;
            bool fechaCorrecta = fechaBaja.Cargar();
            if(!fechaCorrecta){return;}

            bool seleccionCorrecta = false;
            while(!seleccionCorrecta){
                int confirmacion;
                system("cls");
                cout << "--- BAJA DE REPARACION ID: '" << idBaja << "' ---" << endl;
                cout << endl << "Est� seguro que desea dar de baja esta reparaci�n? 1->SI / 2->NO : ";
                cin >> confirmacion;
                switch(confirmacion){
                    case 1:{
                            bool dioBajaReparacion;
                            bool dioBajaVehiculo;
                            dioBajaReparacion = archiReparaciones.bajaLogica(idBaja, fechaBaja); // Realizamos la baja en el archivo Reparaciones
                            dioBajaVehiculo = archiVehiculos.bajaLogica(patente); // Realizamos la baja en el archivo Vehiculos
                            if(dioBajaReparacion == true && dioBajaVehiculo == true){
                                cout << "Se di� de baja con �xito la reparaci�n id '" << idBaja << "'" << endl;
                                cout << "Se di� de baja con �xito el veh�culo patente '" << patente << "'" << endl<< endl;
                            }else{
                                cout << "ERROR: No se pudo dar de baja la reparaci�n '" << idBaja << "'" << endl;
                                cout << "ERROR: No se pudo dar de baja el veh�culo '" << patente << "'" << endl<< endl;
                            }
                            seleccionCorrecta = true;
                            break;}
                    case 2: cout << "Operaci�n de baja cancelada." << endl << endl;
                            seleccionCorrecta = true;
                            break;
                    default: cout << "ERROR: La selecci�n no es correcta." << endl << endl;
                            system("pause");
                            break;
                }
            }
        }else{
            cout << endl << "ERROR: La reparaci�n con el id '" << idBaja << "' ya hab�a sido dada de baja anteriormente." << endl;
            cout << "ERROR: El veh�culo con la patente '" << patente << "' ya hab�a sido dado de baja anteriormente." << endl << endl;
        }
    }
    system("pause");
}


void modificarReparacion(){
    ArchivoReparaciones archiReparaciones;
    Reparacion reg;
    int idAModificar;
    bool bandera = false;
    while(!bandera){
        system("cls");
        cout << "--- MODIFICAR REPARACION ---" << endl;
        cout << "INGRESE EL ID DE LA REPARACION A MODIFICAR (INGRESE 0 PARA VOLVER ATRAS): ";
        cin >> idAModificar;
        if(idAModificar == 0){return;} // Salimos de la opci�n modificar de reparaci�n

        // VALIDAMOS QUE EL ID EXISTA EN EL ARCHIVO
        int pos = archiReparaciones.buscarPosicion(idAModificar); // Devuelve -1 no encontr� el id y -2 no pudo leer el registro
        if(pos == -1 || pos == -2){
            cout << "ERROR: No existe una reparaci�n con el id: " << idAModificar << ". Intente nuevamente." << endl << endl;
            system("pause");
        }else{
            bandera = true; // Salimos del bucle
        }
    }

    // VALIDAMOS QUE LA REPARACI�N EST� ACTIVA
    int pos = archiReparaciones.buscarPosicion(idAModificar); // Conseguimos la posici�n (sabemos que va a encontrarla porque ya lo hizo antes)
    reg = archiReparaciones.leerRegistro(pos); // Traemos la informaci�n del registro
    if(reg.getEstadovehiculo() == false){
        cout << "ERROR: La reparaci�n fue dada de baja, no se pueden realizar modificaciones." << endl << endl;
        system("pause");
        return;
    }

    // SI LAS VALIDACIONES EST�N OK SE PASA AL SIGUIENTE MEN�
    int opc;
    int salir = 1;
    while(salir != 0){
        system("cls");
        cout << "--- MODIFICAR DE REPARACION ---" << endl;
        cout << "ID: " << idAModificar << " | CUIT: " << reg.getCuit() << " | PATENTE: " << reg.getPatente() << endl;
        cout << "1. MODIFICAR DESCRIPCI�N DE FALLA" << endl;
        cout << "2. MODIFICAR IMPORTE" << endl;
        cout << "3. MODIFICAR FECHA DE INGRESO" << endl;
        cout << endl;
        cout << "0. VOLVER A MENU REPARACIONES" << endl;
        cout << "-------------------------------" << endl;
        cout << "SELECCIONAR OPCION: ";
        cin >> opc;
        system("cls");

        bool seModifico = false; // Para saber si se realiz� alguna modificaci�n

        switch(opc){
            case 1:{ cout << "--- MODIFICAR DESCRIPCI�N DE FALLA ---" << endl;
                char nuevaDescripcion[1000];
                char descripcionExistente[1000] = {}; // Para traernos la descripci�n del registro
                strcpy(descripcionExistente, reg.getFalla()); // Traemos la descripci�n del registro
                cout << "INGRESE LA NUEVA DESCRIPCION: ";
                cargarCadena(nuevaDescripcion, sizeof(nuevaDescripcion)-1);
                pasarAMayusculas(nuevaDescripcion);
                if(strcmp(nuevaDescripcion, descripcionExistente) != 0){
                    reg.setFalla(nuevaDescripcion); // Guardamos la nueva descripci�n
                    seModifico = true;
                }else{
                    cout << "ATENCION: La descripci�n ingresada es igual a la existente." << endl << endl;
                    system("pause");
                }
                break;}
            case 2:{ cout << "--- MODIFICAR IMPORTE ---" << endl;
                float nuevoImporte;
                bool importeCorrecto = false;
                while(!importeCorrecto){
                    cout << "INGRESE EL NUEVO IMPORTE: $";
                    cin >> nuevoImporte;
                    if(nuevoImporte > 0){
                        if(nuevoImporte != reg.getImporte()){
                            reg.setImporte(nuevoImporte);
                            seModifico = true;

                        }else{
                            cout << "ATENCION: El importe ingresado es igual al existente." << endl << endl;
                            system("pause");
                        }
                        importeCorrecto = true;
                    }else{
                        cout << "ERROR: El importe debe ser mayor a 0. Intente nuevamente." << endl;
                        system("pause");
                        system("cls");
                    }
                }
                break;}
            case 3:{ cout << "--- MODIFICAR FECHA DE INGRESO ---" << endl;
                Fecha nuevaFechaIngreso;
                Fecha fechaExistente = reg.getFechaEntrada(); // Para traernos la fecha del registro
                cout << "INGRESE LA NUEVA FECHA DE INGRESO: " << endl;
                nuevaFechaIngreso.Cargar();
                if(nuevaFechaIngreso.getDia() != fechaExistente.getDia() && nuevaFechaIngreso.getMes() != fechaExistente.getMes() && nuevaFechaIngreso.getAnio() != fechaExistente.getAnio()){
                    reg.setFechaEntrada(nuevaFechaIngreso);
                    seModifico = true;
                }else{
                    cout << "ATENCION: La fecha ingresada es igual a la existente." << endl << endl;
                    system("pause");
                }
                break;}
            case 0: salir = 0;
                    break;
            default: cout << "ERROR: La selecci�n no es correcta." << endl << endl;
                    break;
        }

        if(seModifico){
            int exitoModificacion = archiReparaciones.modificarRegistro(reg, pos);
            if(exitoModificacion == 1){
                cout << "La reparaci�n fue modificada con �xito." << endl << endl;
                system("pause");
            }else{
                cout << "ERROR: No se pudo modificar la reparaci�n en el archivo." << endl << endl;
                system("pause");
            }
        }
    }
}


