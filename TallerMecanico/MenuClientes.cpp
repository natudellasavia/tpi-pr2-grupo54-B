#include <iostream>
#include <clocale>
#include "MenuClientes.h"
#include "clsCliente.h"
#include "clsArchivoClientes.h"
#include "clsArchivoReparaciones.h"
#include "funciones.h"

using namespace std;

int menuClientes(){
    setlocale(LC_ALL, "Spanish");
	int opc;
    while(true){
        system("cls");
        cout << "--------- CLIENTES -----------" << endl;
        cout << "1. ALTA CLIENTE" << endl;
        cout << "2. BAJA DE CLIENTE" << endl;
        cout << "3. MODIFICAR CLIENTE" << endl;
        cout << endl;
        cout << "0. VOLVER AL MENU PRINCIPAL" << endl;
        cout << "------------------------------" << endl;
        cout << "SELECCIONAR OPCION: ";
        cin>>opc;
        system("cls");
        switch(opc){
            case 1: altaCliente();
                    break;
            case 2: bajaCliente();
                    break;
            case 3: modificarCliente();
                    break;
            case 0: return 0;
                    break;
            default: cout << "ERROR: La selecci�n no es correcta." << endl;
            system("pause");
        }
    }
    return 0;
}


void altaCliente(){
    cout << "--- ALTA CLIENTE ---" << endl;
    Cliente reg;
    bool bandera = reg.Cargar();
    ArchivoClientes archiClientes;

    int opc;
    while(bandera){
        cout << endl << "�Est� seguro que desea de dar de alta? 1->SI / 2->NO : ";
        cin >> opc;
        if(opc == 1){
            int agrego = archiClientes.agregarRegistro(reg); // Guardamos el resultado de la funci�n agregarRegistro para saber que pas�
                switch(agrego){
                    case -5: cout << "ERROR: No se pudo encontrar el archivo." << endl << endl;
                             break;
                    case 0: cout << "ERROR: No se pudo cargar al cliente." << endl << endl;
                            break;
                    case 1: cout << "Cliente cargado exitosamente." << endl << endl;
                            break;
                }
            bandera = false; // Cambia a false para salir del bucle
        }else if(opc == 2){
            bandera = false; // Cambia a false para salir del bucle
        }
        system("pause");
    }
}


void bajaCliente(){
    Cliente regC;
    Reparacion regR;
    ArchivoClientes archiClientes;
    ArchivoReparaciones archiReparaciones;
    char cuitBuscado[15]; // Cargado por teclado

    system("cls");
    cout << "--- BAJA CLIENTE ---" << endl;
    cout << "INGRESE EL CUIT DEL CLIENTE A DAR DE BAJA (INGRESE 0 PARA VOLVER ATRAS): ";
    cargarCadena(cuitBuscado, sizeof(cuitBuscado)-1);
    if(strcmp(cuitBuscado, "0") == 0){return;} // Si ingresan 0 vuelve para atr�s

    // VALIDAMOS QUE EL CUIT EXISTA EN EL ARCHIVO
    int pos = archiClientes.buscarPosicion(cuitBuscado); // -1 no encontr� el id / -2 no pudo leer el registro
    if(pos == -1 || pos == -2){
        cout << "ERROR: No existe un cliente con el cuit: " << cuitBuscado << endl << endl;
    }else{
        regC = archiClientes.leerRegistro(pos); // Nos guardamos los valores del registro cliente
        // VALIDAMOS QUE NO EST� DADO DE BAJA YA EL CLIENTE
        if(regC.getEstado() == true){
            // VALIDAMOS QUE EL CLIENTE NO TENGA VEH�CULOS A�N EN REPARACIONES
            int tamanio = archiReparaciones.contarRegistros(); // Cantidad de registros del archivo reparaciones
            int contador = 0; // Lo usamos para verificar que el cliente no est� en un registro Reparaciones activo
            char cuitComparar[15];
            for(int i = 0; i < tamanio; i++){ // Recorremos el archivo Reparaciones
                regR = archiReparaciones.leerRegistro(i);
                strcpy(cuitComparar, regR.getCuit()); // Guardamos el cuit del registro de Reparaciones
                if(strcmp(cuitBuscado, cuitComparar) == 0){ // Vemos si los cuit son iguales
                    // Vemos el estado del registro
                    if(regR.getEstadovehiculo() == true){
                        contador++; // La reparaci�n no est� dada de baja entonces acumulamos para saber que no podemos dar de baja
                    }
                }
            }

            if(contador == 0){ // Si es 0 significa que no se encontraron reparaciones de alta con el mismo cuit
                bool seleccionCorrecta = false;
                while(!seleccionCorrecta){
                    system("cls");
                    cout << "--- DATOS DEL CLIENTE A DAR DE BAJA ---" << endl;
                    regC.Mostrar();
                    int confirmacion;
                    cout << endl << "Est� seguro que desea dar de baja este cliente? 1->SI / 2->NO : ";
                    cin >> confirmacion;
                    switch(confirmacion){
                        case 1:{ bool dioBaja;
                                 dioBaja = archiClientes.bajaLogica(cuitBuscado); // Realizamos la baja en el archivo
                                 if(dioBaja == true){
                                     cout << "Cliente dado de baja exitosamente." << endl << endl;
                                 }else{
                                     cout << "ERROR: No se pudo guardar la baja del cliente." << endl << endl;
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
                cout << "ERROR: El cliente con cuit '" << cuitBuscado << "' a�n tiene reparaciones en el taller." << endl << endl;
            }
        }else{
            cout << endl << "ERROR: El cliente con cuit '" << cuitBuscado << "' ya hab�a sido dado de baja anteriormente." << endl << endl;
        }
    }
    system("pause");
}


void modificarCliente(){
    ArchivoClientes archiClientes;
    Cliente reg;
    char cuitAModificar[15]; // Cargado por teclado
    bool bandera = false;
    while(!bandera){
        system("cls");
        cout << "--- MODIFICAR CLIENTE ---" << endl;
        cout << "INGRESE EL CUIT DEL CLIENTE A MODIFICAR (INGRESE 0 PARA VOLVER ATRAS): ";
        cargarCadena(cuitAModificar, sizeof(cuitAModificar)-1);
        if(strcmp(cuitAModificar, "0") == 0){return;} // Si ingresan 0 vuelve para atr�s

        // VALIDAMOS QUE EL CUIT EXISTA EN EL ARCHIVO
        int pos = archiClientes.buscarPosicion(cuitAModificar); // Devuelve -1 no encontr� el id y -2 no pudo leer el registro
        if(pos == -1 || pos == -2){
            cout << "ERROR: No existe un cliente con el cuit: " << cuitAModificar << ". Intente nuevamente." << endl << endl;
            system("pause");
        }else{
            bandera = true; // Salimos del bucle
        }
    }

    // VALIDAMOS QUE EL CLIENTE EST� ACTIVO
    int pos = archiClientes.buscarPosicion(cuitAModificar); // Conseguimos la posici�n (sabemos que va a encontrarla porque ya lo hizo antes)
    reg = archiClientes.leerRegistro(pos); // Traemos la informaci�n del registro
    if(reg.getEstado() == false){
        cout << "ERROR: El cliente fue dado de baja, no se pueden realizar modificaciones." << endl << endl;
        system("pause");
        return;
    }

    // SI LAS VALIDACIONES EST�N OK SE PASA AL SIGUIENTE MEN�
    int opc;
    int salir = 1;
    while(salir != 0){
        system("cls");
        cout << "--- MODIFICAR DEL CLIENTE ---" << endl;
        cout << "CUIT: " << cuitAModificar << endl;
        cout << "1. MODIFICAR NUMERO DE TELEFONO" << endl;
        cout << "2. MODIFICAR EMAIL" << endl;
        cout << "3. MODIFICAR DIRECCION" << endl;
        cout << endl;
        cout << "0. VOLVER A MENU CLIENTE" << endl;
        cout << "-------------------------------" << endl;
        cout << "SELECCIONAR OPCION: ";
        cin >> opc;
        system("cls");

        bool seModifico = false; // Para saber si se realiz� alguna modificaci�n

        switch(opc){
            case 1:{ cout << "--- MODIFICAR NUMERO DE TELEFONO ---" << endl;
                char nuevoTelefono[15];
                char telefonoExistente[15] = {}; // Para traernos el tel�fono del registro
                strcpy(telefonoExistente, reg.getCelular()); // Traemos el celular del registro
                cout << "INGRESE EL NUEVO TELEFONO: ";
                cargarCadena(nuevoTelefono, sizeof(nuevoTelefono)-1);
                pasarAMayusculas(nuevoTelefono);
                if(strcmp(nuevoTelefono, telefonoExistente) != 0){
                    reg.setCelular(nuevoTelefono); // Guardamos el nuevo tel�fono
                    seModifico = true;
                }else{
                    cout << "ATENCION: El tel�fono ingresado es igual al existente." << endl << endl;
                    system("pause");
                }
                break;}
            case 2:{ cout << "--- MODIFICAR EMAIL ---" << endl;
                char nuevoEmail[30];
                char emailExistente[30] = {}; // Para traernos el mail del registro
                strcpy(emailExistente, reg.getEmail()); // Traemos el email del registro
                cout << "INGRESE EL NUEVO EMAIL: ";
                cargarCadena(nuevoEmail, sizeof(nuevoEmail)-1);
                pasarAMayusculas(nuevoEmail);
                if(strcmp(nuevoEmail, emailExistente) != 0){
                    reg.setEmail(nuevoEmail); // Guardamos el nuevo email
                    seModifico = true;
                }else{
                    cout << "ATENCION: El email ingresado es igual al existente." << endl << endl;
                    system("pause");
                }
                break;}
            case 3:{ cout << "--- MODIFICAR DIRECCION ---" << endl;
                char nuevaDireccion[50];
                char direccionExistente[50] = {}; // Para traernos la direcci�n del registro
                strcpy(direccionExistente, reg.getDireccion()); // Traemos la direcci�n del registro
                cout << "INGRESE LA NUEVA DIRECCION: ";
                cargarCadena(nuevaDireccion, sizeof(nuevaDireccion)-1);
                pasarAMayusculas(nuevaDireccion);
                if(strcmp(nuevaDireccion, direccionExistente) != 0){
                    reg.setDireccion(nuevaDireccion); // Guardamos la nueva direcci�n
                    seModifico = true;
                }else{
                    cout << "ATENCION: La direcci�n ingresada es igual a la existente." << endl << endl;
                    system("pause");
                }
                break;}
            case 0: salir = 0;
                    break;
            default: cout << "ERROR: La selecci�n no es correcta.";
                    break;
        }

        if(seModifico){
            int exitoModificacion = archiClientes.modificarRegistro(reg, pos);
            if(exitoModificacion == 1){
                cout << "El cliente fue modificado con �xito." << endl << endl;
                system("pause");
            }else{
                cout << "ERROR: No se pudo modificar el cliente en el archivo." << endl << endl;
                system("pause");
            }
        }
    }
}
