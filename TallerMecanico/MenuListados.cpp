#include <iostream>
#include <clocale>
#include "MenuListados.h"
#include "clsArchivoClientes.h"
#include "clsArchivoReparaciones.h"
#include "clsArchivoVehiculos.h"
#include "clsCliente.h"
#include "clsReparacion.h"
#include "clsVehiculo.h"


using namespace std;


int menuListados(){
    setlocale(LC_ALL, "Spanish");
	int opc;

    while(true){
        system("cls");
        cout << "--------- LISTADOS -----------" << endl;
        cout << "  CLIENTES" << endl;
        cout << "1. ORDENADOS POR NÚMERO DE CUIL" << endl;
        cout << "2. ORDENADOS POR APELLIDO" << endl;
        cout << "3. ORDENADOS POR TIPO DE CLIENTE" << endl;
        cout << endl;
        cout << "  VEHICULOS" << endl;
        cout << "4. ORDENADOS POR MARCA" << endl;
        cout << "5. ORDENADOS POR TIPO DE VEHÍCULO" << endl;
        cout << endl;
        cout << "  REPARACIONES" << endl;
        cout << "6. ORDENADAS POR ID REPARACIÓN" << endl;
        cout << "7. ORDENADAS POR CLIENTE" << endl;
        cout << "8. ORDENADAS POR VEHÍCULO" << endl;
        cout << "9. ORDENADAS POR IMPORTE" << endl;
        cout << endl;
        cout << "0. VOLVER AL MENU PRINCIPAL" << endl;
        cout << "------------------------------" << endl;
        cout << "SELECCIONAR OPCION: ";
        cin>>opc;
        system("cls");
        switch(opc){
            case 1: listadoClientesCuit();
                    break;
            case 2: listadoClientesApellido();
                    break;
            case 3: listadoClientesTipo();
                    break;
            case 4: listadoVehiculosMarca();
                    break;
            case 5: listadoVehiculosTipoDeVehiculo();
                    break;
            case 6: listadoReparacionesId();
                    break;
            case 7: listadoReparacionesCliente();
                    break;
            case 8: listadoReparacionesVehiculo();
                    break;
            case 9: listadoReparacionesImporte();
                    break;
            case 0: return 0;
                    break;
            default: cout<<"ERROR: La selección no es correcta."<<endl;
                     system("pause");
        }
    }
    return 0;
}


/// ---------- C L I E N T E S ----------

/// OK NATI
void listadoClientesCuit(){
    system("cls");
    ArchivoClientes archiClientes;
    cout << "--- LISTADO CLIENTES ORDENADO POR CUIT ---" << endl << endl;

    // Ejecuta listadoClientesPorCuit y si encuentra clientes los muestra, sino devuelve -1
    if(archiClientes.listadoClientesPorCuit() == -1){
        cout << "ERROR: No hay clientes existentes." << endl << endl;
    }

    system("pause");
}


/// OK NATI
void listadoClientesApellido(){
    system("cls");
    ArchivoClientes archiClientes;
    cout << "--- LISTADO CLIENTES ORDENADO POR APELLIDO ---" << endl << endl;

    // Ejecuta listadoClientesPorApellido y si encuentra clientes los muestra, sino devuelve -1
    if(archiClientes.listadoClientesPorApellido() == -1){
        cout << "ERROR: No hay clientes existentes." << endl << endl;
    }

    system("pause");
}


/// OK NATI
void listadoClientesTipo(){
    system("cls");
    ArchivoClientes archiClientes;
    cout << "--- LISTADO CLIENTES ORDENADO POR TIPO ---" << endl << endl;

    // Ejecuta listadoClientesPorTipo y si encuentra clientes los muestra, sino devuelve -1
    if(archiClientes.listadoClientesPorTipo() == -1){
        cout << "ERROR: No hay clientes existentes." << endl << endl;
    }

    system("pause");
}



/// ---------- V E H I C U L O S ----------

/// OK NATI
void listadoVehiculosMarca(){
    system("cls");
    ArchivoVehiculos archiVehiculos;
    cout << "--- LISTADO VEHICULOS ORDENADO POR MARCA ---" << endl << endl;

    // Ejecuta listadoVehiculosPorMarca y si encuentra vehiculos las muestra, sino devuelve -1
    if(archiVehiculos.listadoVehiculosPorMarca() == -1){
        cout << "ERROR: No hay vehiculos existentes." << endl << endl;
    }

    system("pause");
}


/// OK NATI
void listadoVehiculosTipoDeVehiculo(){
    system("cls");
    ArchivoVehiculos archiVehiculos;
    cout << "--- LISTADO VEHICULOS ORDENADO POR TIPO DE VEHICULO ---" << endl << endl;

    // Ejecuta listadoVehiculosPorTipoDeVehiculo y si encuentra vehiculos las muestra, sino devuelve -1
    if(archiVehiculos.listadoVehiculosPorTipoDeVehiculo() == -1){
        cout << "ERROR: No hay vehiculos existentes." << endl << endl;
    }

    system("pause");
}



/// ---------- R E P A R A C I O N E S ----------

/// OK NATI
void listadoReparacionesId(){
    system("cls");
    ArchivoReparaciones archiReparaciones;
    cout << "--- LISTADO REPARACIONES ORDENADO POR ID ---" << endl << endl;

    // Ejecuta listadoReparacionesPorId y si encuentra reparaciones las muestra, sino devuelve -1
    if(archiReparaciones.listadoReparacionesPorId() == -1){
        cout << "ERROR: No hay reparaciones existentes." << endl << endl;
    }

    system("pause");
}


/// OK NATI
void listadoReparacionesCliente(){
    system("cls");
    ArchivoReparaciones archiReparaciones;
    cout << "--- LISTADO REPARACIONES ORDENADO POR CUIT ---" << endl << endl;

    // Ejecuta listadoReparacionesPorCliente y si encuentra reparaciones las muestra, sino devuelve -1
    if(archiReparaciones.listadoReparacionesPorCliente() == -1){
        cout << "ERROR: No hay reparaciones existentes." << endl << endl;
    }

    system("pause");
}


/// OK NATI
void listadoReparacionesVehiculo(){
    system("cls");
    ArchivoReparaciones archiReparaciones;
    cout << "--- LISTADO REPARACIONES ORDENADO POR PATENTE ---" << endl << endl;

    // Ejecuta listadoReparacionesPorVehiculo y si encuentra reparaciones las muestra, sino devuelve -1
    if(archiReparaciones.listadoReparacionesPorVehiculo() == -1){
        cout << "ERROR: No hay reparaciones existentes." << endl << endl;
    }

    system("pause");
}


/// OK NATI
void listadoReparacionesImporte(){
    system("cls");
    ArchivoReparaciones archiReparaciones;
    cout << "--- LISTADO REPARACIONES ORDENADO POR IMPORTE ---" << endl << endl;

    // Ejecuta listadoReparacionesPorImporte y si encuentra reparaciones las muestra, sino devuelve -1
    if(archiReparaciones.listadoReparacionesPorImporte() == -1){
        cout << "ERROR: No hay reparaciones existentes." << endl << endl;
    }

    system("pause");
}
