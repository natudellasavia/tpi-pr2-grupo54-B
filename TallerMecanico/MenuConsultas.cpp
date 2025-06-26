#include <iostream>
#include <clocale>
#include "MenuConsultas.h"
#include "clsFecha.h"
#include "clsArchivoReparaciones.h"
#include "clsArchivoVehiculos.h"
#include "clsArchivoClientes.h"
#include "funciones.h"
#include "clsReparacion.h"
#include "clsVehiculo.h"

using namespace std;

int menuConsultas(){
    setlocale(LC_ALL, "Spanish");
	int opc;
    while(true){
        system("cls");
        cout << "-------------- CONSULTAS ---------------" << endl;
        cout << "  CLIENTES" << endl;
        cout << "1. POR NÚMERO DE CUIL" << endl;
        cout << "2. POR TIPO DE CLIENTE" << endl;
        cout << endl;
        cout << "  VEHICULOS" << endl;
        cout << "3. POR PATENTE" << endl;
        cout << "4. POR TIPO DE VEHÍCULO" << endl;
        cout << "5. ACTUALMENTE SE ENCUENTRAN EN TALLER" << endl;
        cout << endl;
        cout << "  REPARACIONES" << endl;
        cout << "6. POR ID" << endl;
        cout << "7. POR CLIENTE" << endl;
        cout << "8. POR VEHÍCULO" << endl;
        cout << "9. POR RANGO DE IMPORTES" << endl;
        cout << "10. POR RANGO DE FECHAS" << endl;
        cout << "11. ACTUALMENTE SE ESTÁN LLEVANDO A CABO" << endl;
        cout << endl;
        cout << "0. VOLVER AL MENU PRINCIPAL" << endl;
        cout << "----------------------------------------" << endl;
        cout << "SELECCIONAR OPCION: ";
        cin>>opc;
        system("cls");
        switch(opc){
            case 1: consultaClientesCuil();
                    break;
            case 2: consultaClientesTipo();
                    break;
            case 3: consultaVehiculosPatente();
                    break;
            case 4: consultaVehiculosTipo();
                    break;
            case 5: consultaVehiculosTaller();
                    break;
            case 6: consultaReparacionesId();
                    break;
            case 7: consultaReparacionesCliente();
                    break;
            case 8: consultaReparacionesVehiculo();
                    break;
            case 9: consultaReparacionesRango();
                    break;
            case 10: consultaReparacionesFecha();
                    break;
            case 11: consultaReparacionesTaller();
                    break;
            case 0: return 0;
                    break;
            default: cout << "ERROR: La selección no es correcta." << endl;
                     system("pause");
        }
    }
    return 0;
}


/// ---------- C L I E N T E S ----------

void consultaClientesCuil(){
    system("cls");
    ArchivoClientes archiClientes;
    char cuitBuscado[15];
    cout << "--- CONSULTA CLIENTE POR NUMERO DE CUIT ---" << endl;
    cout << "INGRESE EL CUIT (INGRESE 0 PARA VOLVER ATRAS): ";
    cargarCadena(cuitBuscado, sizeof(cuitBuscado) - 1);
    if(strcmp(cuitBuscado, "0") == 0){return;} // Si ingresan 0 vuelve para atrás
    cout << endl;

    // Ejecuta consultaClientesPorCuil y si encuentra el cuit lo muestra y devuelve !=-1, sino devuelve -1
    if(archiClientes.consultaClientesPorCuil(cuitBuscado) == -1){
        cout << "ERROR: No se encontro un cliente con cuit '" << cuitBuscado << "'." << endl << endl;
    }

    system("pause");
}


void consultaClientesTipo(){
    ArchivoClientes archiClientes;
    int tipoBuscado;

    int seleccionCorrecta = false;
    while(!seleccionCorrecta){
        system("cls");
        cout << "--- CONSULTA CLIENTE POR TIPO DE CLIENTE ---" << endl;
        cout << "INGRESE EL TIPO DE CLIENTE (1-Particular / 2-Empresa / 0-Volver atras): ";
        cin >> tipoBuscado;
        cout << endl;
        if(tipoBuscado == 0){
                return; // Si ingresan 0 vuelve para atrás
        }else if(tipoBuscado == 1 || tipoBuscado == 2){
            // Ejecuta consultaClientesPorTipo y si encuentra el tipo lo muestra y devuelve !=-1, sino devuelve -1
            if(archiClientes.consultaClientesPorTipo(tipoBuscado) == -1){
                cout << "ERROR: No se encontro ningun cliente del tipo '" << tipoBuscado << "'." << endl << endl;
            }
            seleccionCorrecta = true;
        }else{
            cout << "ERROR: La selección no es correcta." << endl << endl;
            system("pause");
        }
    }

    system("pause");
}


/// ---------- V E H I C U L O S ----------

void consultaVehiculosPatente(){
    system("cls");
    ArchivoVehiculos archivoVehiculos;
    char patenteBuscada[8];
    cout << "--- CONSULTA VEHICULOS POR PATENTE ---" << endl;
    cout <<"INGRESE LA PATENTE DEL VEHICULO (INGRESE 0 PARA VOLVER ATRAS): ";
    cargarCadena(patenteBuscada, sizeof(patenteBuscada) - 1);
    pasarAMayusculas(patenteBuscada);
    if(strcmp(patenteBuscada, "0") == 0){return;} // Si ingresan 0 vuelve para atrás
    cout << endl;

    // Ejecuta consultaClientesPorCuil y si encuentra el cuit lo muestra y devuelve !=-1, sino devuelve -1
    if(archivoVehiculos.consultaVehiculoPorPatente(patenteBuscada) == -1){
        cout << "ERROR: No se encontro un vehiculo con patente '" << patenteBuscada << "'." << endl << endl;
    }

    system("pause");
}


void consultaVehiculosTipo(){
    ArchivoVehiculos archiVehiculos;
    int tipoBuscado;

    int seleccionCorrecta = false;
    while(!seleccionCorrecta){
        system("cls");
        cout << "--- CONSULTA VEHICULO POR TIPO DE VEHICULO ---" << endl;
        cout << "INGRESE EL TIPO DE CLIENTE (1-Auto / 2-Camioneta / 3-Camion / 4-Micro Omnibus / 0-Volver atras): ";
        cin >> tipoBuscado;
        cout << endl;
        if(tipoBuscado == 0){
                return; // Si ingresan 0 vuelve para atrás
        }else if(tipoBuscado == 1 || tipoBuscado == 2 || tipoBuscado == 3 || tipoBuscado == 4){
            // Ejecuta consultaVehiculoPorTipo y si encuentra el tipo lo muestra y devuelve !=-1, sino devuelve -1
            if(archiVehiculos.consultaVehiculoPorTipo(tipoBuscado) == -1){
                cout << "ERROR: No se encontro ningun vehiculo del tipo '" << tipoBuscado << "'." << endl << endl;
            }
            cout << endl;
            seleccionCorrecta = true;
        }else{
            cout << "ERROR: La selección no es correcta." << endl << endl;
            system("pause");
        }
    }

    system("pause");
}


void consultaVehiculosTaller(){
    system("cls");
    ArchivoVehiculos archivoVehiculos;
    cout << "--- CONSULTA VEHICULOS EN TALLER ---" << endl << endl;;

    // Ejecuta consultaVehiculoEnTaller y si encuentra vehiculos los muestra y devuelve !=-1, sino devuelve -1
    if(archivoVehiculos.consultaVehiculoEnTaller() == -1){
        cout << "ERROR: No hay vehiculos en taller." << endl << endl;
    }

    system("pause");
}



/// ---------- R E P A R A C I O N E S ----------

void consultaReparacionesId(){
    system("cls");
    ArchivoReparaciones archiReparaciones;
    int idBuscado;
    cout << "--- CONSULTA REPARACIONES POR ID ---" << endl;
    cout << "INGRESE EL ID (INGRESE 0 PARA VOLVER ATRAS): ";
    cin >> idBuscado;
    if(idBuscado == 0){return;} // Si ingresan 0 vuelve para atrás
    cout << endl;

    // Ejecuta consultaReparacionPorId y si encuentra el tipo lo muestra y devuelve !=-1, sino devuelve -1
    if(archiReparaciones.consultaReparacionPorId(idBuscado) == -1){
        cout << "ERROR: No se encontraron reparaciones con el id '" << idBuscado << "'." << endl << endl;
    }

    system("pause");
}


void consultaReparacionesCliente(){
    system("cls");
    ArchivoReparaciones archiReparaciones;
    char cuitBuscado[15];
    cout << "--- CONSULTA REPARACIONES POR CLIENTE ---" << endl;
    cout << "INGRESE EL CUIT (INGRESE 0 PARA VOLVER ATRAS): ";
    cargarCadena(cuitBuscado, sizeof(cuitBuscado) - 1);
    if(strcmp(cuitBuscado, "0") == 0){return;} // Si ingresan 0 vuelve para atrás
    cout << endl;

    // Ejecuta consultaReparacionPorCliente y si encuentra el id lo imprime y devuelve 1, sino devuelve -1
    if(archiReparaciones.consultaReparacionPorCliente(cuitBuscado) == -1){
        cout << "ERROR: No se encontraron reparaciones para el cliente con el cuit '" << cuitBuscado << "'." << endl << endl;
    }

    system("pause");
}


void consultaReparacionesVehiculo(){
    system("cls");
    ArchivoReparaciones archiReparaciones;
    char patenteBuscada[8];
    cout << "--- CONSULTA REPARACIONES POR VEHÍCULO ---" << endl;
    cout << "INGRESE LA PATENTE (INGRESE 0 PARA VOLVER ATRAS): ";
    cargarCadena(patenteBuscada, sizeof(patenteBuscada) - 1);
    pasarAMayusculas(patenteBuscada);
    if(strcmp(patenteBuscada, "0") == 0){return;} // Si ingresan 0 vuelve para atrás
    cout << endl;

    // Ejecuta consultaReparacionPorVehiculo y si encuentra la patente la muestra y devuelve !=-1, sino devuelve -1
    if(archiReparaciones.consultaReparacionPorVehiculo(patenteBuscada) == -1){
        cout << "ERROR: No se encontraron reparaciones para el vehiculo con la patente '" << patenteBuscada << "'." << endl << endl;
    }

    system("pause");
}


void consultaReparacionesRango(){
    ArchivoReparaciones archiReparaciones;
    float importeDesde, importeHasta;
    bool importeValido = false;
    // Trabajamos dentro de un bucle para la validación que 'importe hasta' sea mayor que 'importe desde'
    while (!importeValido){
        system("cls");
        cout << "--- CONSULTA REPARACIONES POR RANGO DE IMPORTES ---" << endl;
        cout << "INGRESE 0-VOLVER ATRAS / 1-CONTINUAR: ";
        int opc;
        cin >> opc;
        cout << endl;
        if(opc == 0){
            return; // Si ingresan 0 vuelve para atrás
        }else if(opc == 1){
            cout << "IMPORTE DESDE: ";
            cin >> importeDesde; // Tiene que ser mayor a 0
            if(importeDesde > 0){
                cout << "IMPORTE HASTA: ";
                cin >> importeHasta;
                if(importeHasta >= importeDesde){
                    importeValido = true; // Si es mayor, pongo importeValido en true para salir del bucle
                }else{
                    cout << endl << "'IMPORTE HASTA' debe ser mayor o igual a 'IMPORTE DESDE'." << endl << endl;
                    system("pause");
                }
            }
        }else{
            cout << "ERROR: La eleccion no es correcta." << endl << endl;
            system("pause");
        }
    }

    // Ejecuta consultaReparacionPorRango y si encuentra registros entre los importes los muestra y devuelve !=-1, sino devuelve -1
    if(archiReparaciones.consultaReparacionPorRango(importeDesde, importeHasta) == -1){
        cout << "ERROR: No se encontraron reparaciones con monto entre '" << importeDesde << "' y '" << importeHasta << "'." << endl << endl;
    }

    system("pause");
}


void consultaReparacionesFecha(){
    Fecha fechaDesde;
    Fecha fechaHasta;
    ArchivoReparaciones archiReparaciones;

    bool fechaValida = false;
    while (!fechaValida){
        system("cls");
        cout << "--- CONSULTA POR RANGO DE FECHAS ---" << endl;
        cout << "INGRESE 0-VOLVER ATRAS / 1-CONTINUAR: ";
        int opc;
        cin >> opc;
        cout << endl;
        if(opc == 0){
            return; // Si ingresan 0 vuelve para atrás
        }else if(opc == 1){
            cout << endl << "FECHA DESDE: " << endl;
            fechaDesde.Cargar();
            cout << endl << "FECHA HASTA: " << endl;
            fechaHasta.Cargar(); // tiene que ser mayor que fechaDesde

            // VALIDAMOS QUE LA FECHA HASTA SEA IGUAL O POSTERIOR A FECHA DESDE
            if(fechaHasta.getAnio() >= fechaDesde.getAnio() && fechaHasta.getMes() >= fechaDesde.getMes() && fechaHasta.getDia() >= fechaDesde.getDia()){
                fechaValida = true; // Si es igual o posterior
            }else{
                cout << endl << "ERROR: 'FECHA HASTA' debe ser igual o posterior a 'FECHA DESDE'." << endl << endl;
                system("pause");
            }
        }else{
            cout << "ERROR: La eleccion no es correcta." << endl << endl;
            system("pause");
        }
    }

    system("cls"); // Acá limpiamos la pantalla y volvemos a mostrar para que quede la fecha en formado dd/mm/aaaa
    cout << "--- CONSULTA POR RANGO DE FECHAS ---" << endl;
    cout << "FECHA DESDE: ";
    fechaDesde.Mostrar();
    cout << endl << "FECHA HASTA: ";
    fechaHasta.Mostrar();
    cout << endl;

    // Ejecuta consultaReparacionPorFecha y si encuentra registros entre las fechas los muestra y devuelve !=-1, sino devuelve -1
    if(archiReparaciones.consultaReparacionPorFecha(fechaDesde, fechaHasta) == -1){
        cout << "ERROR: No se encontraron reparaciones entre las fechas '";
        fechaDesde.Mostrar();
        cout << "' y '";
        fechaHasta.Mostrar();
        cout << "'." << endl << endl;
    }

    system("pause");
}


void consultaReparacionesTaller(){
    system("cls");
    ArchivoReparaciones archiReparaciones;
    cout << "--- CONSULTA REPARACIONES ACTUALMENTE SE ESTÁN LLEVANDO A CABO ---" << endl;
    cout << endl;

    // Ejecuta consultaReparacionEnTaller y si encuentra reparaciones las muestra y devuelve !=-1, sino devuelve -1
    if(archiReparaciones.consultaReparacionEnTaller() == -1){
        cout << "ERROR: No hay reparaciones que se esten llevando a cabo." << endl << endl;
    }

    system("pause");
}

