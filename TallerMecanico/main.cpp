#include <iostream>
#include "MenuClientes.h"
#include "MenuVehiculos.h"
#include "MenuReparaciones.h"
#include "MenuListados.h"
#include "MenuConsultas.h"
#include "MenuInformes.h"

using namespace std;

int main(){
    setlocale(LC_ALL, "Spanish");

	int opc;
    while(true){
        system("cls");
        cout << "------- MENÚ PRINCIPAL -------" << endl;
        cout << "1. CLIENTES" << endl;
        cout << "2. VEHÍCULOS" << endl;
        cout << "3. REPARACIONES" << endl;
        cout << "4. LISTADOS" << endl;
        cout << "5. CONSULTAS" << endl;
        cout << "6. INFORMES" << endl;
        cout << endl;
        cout << "0. CERRAR EL PROGRAMA" << endl;
        cout << "------------------------------" << endl;
        cout << "SELECCIONAR OPCIÓN: ";
        cin>>opc;
        system("cls");
        switch(opc){
            case 1: menuClientes();
                    break;
            case 2: menuVehiculos();
                    break;
            case 3: menuReparaciones();
                    break;
            case 4: menuListados();
                    break;
            case 5: menuConsultas();
                    break;
            case 6: menuInformes();
                    break;
            case 0: cout << "EL PROGRAMA HA FINALIZADO, GRACIAS" << endl;
                    return 0;
                    break;
            default: cout<<"LA SELECCION NO ES CORRECTA"<<endl;
                    system("pause");
        }
    }
    return 0;
}
