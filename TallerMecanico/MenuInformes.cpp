#include <iostream>
#include <cstring>
#include <clocale>
#include "MenuInformes.h"
#include "clsArchivoClientes.h"
#include "clsArchivoVehiculos.h"
#include "clsArchivoReparaciones.h"
#include "clsCliente.h"
#include "clsReparacion.h"
#include "clsFecha.h"
#include "funciones.h"
using namespace std;

int menuInformes(){
    setlocale(LC_ALL, "Spanish");
	int opc;
    while(true){
        system("cls");
        cout << "--------- INFORMES -----------" << endl;
        cout << "1. RECAUDACI�N ANUAL Y CANTIDAD DE REPARACIONES EFECTUADAS" << endl;
        cout << "2. RECAUDACI�N POR TIPO DE CLIENTE Y A�O" << endl;
        cout << "3. CANTIDAD DE REPARACIONES POR TIPO DE VEH�CULO" << endl;
        cout << "4. CANTIDAD DE REPARACIONES ANUALES POR MARCA DE VEH�CULO" << endl;
        cout << "5. CLIENTE M�S FRECUENTE" << endl;
        cout << endl;
        cout << "0. VOLVER AL MENU PRINCIPAL" << endl;
        cout << "------------------------------" << endl;
        cout << "SELECCIONAR OPCION: ";
        cin>>opc;
        system("cls");
        switch(opc){
            case 1: informeUno();
                    break;
            case 2: informeDos();
                    break;
            case 3: informeTres();
                    break;
            case 4: informeCuatro();
                    break;
            case 5: informeCinco();
                    break;
            case 0: return 0;
                    break;
            default: cout << "ERROR: La selecci�n no es correcta." << endl;
                     system("pause");
        }
    }
    return 0;
}


/// ---------- U N O ----------
void informeUno(){
    system("cls");
    int anioIngresado;
    float recaudacionMensual[12] = {0}; // Almacenar� la suma de importes por cada mes
    int cantidadMensual[12] = {0}; // Almacenar� el conteo de reparaciones por cada mes
    float recaudacionAnualTotal = 0;
    int cantidadAnualTotal = 0;

    Reparacion reg;
    FILE *pArchivo;
    pArchivo = fopen("Reparaciones.dat", "rb");
    if (pArchivo == nullptr) {
        cout << "ERROR: No se pudo abrir el archivo de reparaciones." << endl;
        system("pause");
        return;
    }

    cout << "--- INFORME ANUAL DE RECAUDACION Y REPARACIONES ---" << endl;
    cout << "INGRESE EL ANIO A CONSULTAR (INGRESE 0 PARA VOLVER ATRAS): ";
    cin >> anioIngresado;
    if (anioIngresado == 0) {
        fclose(pArchivo);
        return; // Si ingresan 0 vuelve para atr�s
    }

    // Recorrido del archivo de reparaciones
    while (fread(&reg, sizeof(Reparacion), 1, pArchivo) == 1){
        if (reg.getFechaEntrada().getAnio() == anioIngresado){
            int mes = reg.getFechaEntrada().getMes();
            // Asegura que el mes sea v�lido
            if (mes >= 1 && mes <= 12) {
                // (mes - 1 se usa porque los arrays son base 0)
                recaudacionMensual[mes - 1] += reg.getImporte(); // Acmula el importe al total de ese mes.
                cantidadMensual[mes - 1]++; // Incrementa el contador de reparaciones para ese mes.
                // Suma el importe x mes y acumula las reparaciones.
                recaudacionAnualTotal += reg.getImporte();
                cantidadAnualTotal++;
            }
        }
    }
    fclose(pArchivo);

    // Mostramos los resultados
    cout << endl  <<"RECAUDACION ANUAL Y CANTIDAD DE REPARACIONES EFECTUADAS EN EL " << anioIngresado << endl << endl;

    // Si hay datos, entonces seguimos.
    cout << "     MES     |      IMPORTE       |      CANTIDAD      " << endl;
    cout << "------------------------------------------------------- " << endl;
    for (int i = 0; i < 12; i++) {
        switch (i+1) {
            case 1: cout << "ENERO"; break;
            case 2: cout << "FEBRERO"; break;
            case 3: cout << "MARZO"; break;
            case 4: cout << "ABRIL"; break;
            case 5: cout << "MAYO"; break;
            case 6: cout << "JUNIO"; break;
            case 7: cout << "JULIO"; break;
            case 8: cout << "AGOSTO"; break;
            case 9: cout << "SEPTIEMBRE"; break;
            case 10: cout << "OCTUBRE"; break;
            case 11: cout << "NOVIEMBRE"; break;
            case 12: cout << "DICIEMBRE"; break;
        }

        if (i == 0) cout << "        | ";
        else if (i == 1) cout << "      | ";
        else if (i == 2) cout << "        | ";
        else if (i == 3) cout << "        | ";
        else if (i == 4) cout << "         | ";
        else if (i == 5) cout << "        | ";
        else if (i == 6) cout << "        | ";
        else if (i == 7) cout << "       | ";
        else if (i == 8) cout << "   | ";
        else if (i == 9) cout << "      | ";
        else if (i == 10) cout << "    | ";
        else if (i == 11) cout << "    | ";

        cout << "$" << recaudacionMensual[i];
        for(int j=0; j<20;j++){
            cout << " "; // Espacios para la columna importe
        }
        cout << cantidadMensual[i] << endl;
    }
    cout << "-------------------------------------------------------"<< endl;

    cout << "TOTAL:              $" << recaudacionAnualTotal << "                   " << cantidadAnualTotal << endl << endl;
    system("pause");
}


/// ---------- D O S ----------
void informeDos(){
    system("cls");
    ArchivoReparaciones archiReparaciones;
    ArchivoClientes archiClientes;
    Reparacion regR;
    Cliente regC;

    int cantidadReparaciones = archiReparaciones.contarRegistros();
    if (cantidadReparaciones == 0) {
        cout << "No hay reparaciones registradas." << endl; // Si no hay reparaciones sale de la funci�n
        system("pause");
        return;
    }

    // Recorremos las reparaciones para saber cual es el a�o menor inactivo
    int anioMenor; // Voy a guardar el a�o menor encontrado en el registro reparaciones
    for(int i = 0; i < cantidadReparaciones; i++){
        regR = archiReparaciones.leerRegistro(i);

        // VALIDAMOS QUE HAYA SALIDO DEL TALLER (ESTADO INACTIVO)
        if(!regR.getEstadovehiculo()){
        Fecha fechaReparacion = regR.getFechaSalida();
        int anioReparacion = fechaReparacion.getAnio(); // Obtenemos el a�o del registro

        if(i == 0){
            anioMenor = anioReparacion; // Nos guardamos el primer a�o y a partir de ah� comenzamos a comparar
        }

        // Comparamos cu�l es menor entre la fecha del registro y anioMenor
        if(anioReparacion < anioMenor){
            anioMenor = anioReparacion; // Nos guardamos el a�o reparaci�n como nuevo menor
        }
        }
    }

    // Recorremos las reparaciones para saber cual es el a�o mayor inactivo
    int anioMayor; // Voy a guardar el a�o mayor encontrado en el registro reparaciones
    for(int i = 0; i < cantidadReparaciones; i++){
        regR = archiReparaciones.leerRegistro(i);

        // Necesitamos las reparaciones que hayan finalizado (inactivas))
        if(!regR.getEstadovehiculo()){
            Fecha fechaReparacion = regR.getFechaSalida();
            int anioReparacion = fechaReparacion.getAnio(); // Obtenemos el a�o del registro

            if(i == 0){
                anioMayor = anioReparacion; // Nos guardamos el primer a�o y a partir de ah� comenzamos a comparar
            }

            // Comparamos cu�l es mayor entre la fecha del registro y anioMenor
            if(anioReparacion > anioMayor){
                anioMayor = anioReparacion; // Nos guardamos el a�o reparaci�n como nuevo mayor
            }
        }
    }

    int cantidadAnios = anioMayor - anioMenor + 1; // Calculamos cu�ntos a�os en total se trabaj�
    int* vecAnios = new int[cantidadAnios]; // Creamos un arreglo din�mico
    // Creamos un arreglo dinamico inicializado en 0 para cada tipo de cliente para acumular los importes
    float* vecTipoUno = new float[cantidadAnios]();
    float* vecTipoDos = new float[cantidadAnios]();

    // Recorremos el vector de a�os y le asignamos los a�os (usando anioMayor)
    for(int i = 0; i < cantidadAnios; i++){
        vecAnios[i] = anioMayor - i;
    }


    // VALIDAMOS QUE SE HAYAN CARGADO CORRECTAMENTE LOS A�OS
    if(vecAnios[cantidadAnios-1] != anioMenor){
        cout << "ERROR: Hubo un problema con la identificaci�n de los a�os." << endl << endl;
        system("pause");
        return;
    }else{
        // Recorremos los a�os
        for(int i = 0; i < cantidadAnios; i++){

            // Recorremos las reparaciones y las comparamos con el a�o i (s�lo si est�n inactivas)
            for(int x = 0; x < cantidadReparaciones; x++){
                regR = archiReparaciones.leerRegistro(x);

                // Necesitamos las reparaciones que hayan finalizado (inactivas)
                if(!regR.getEstadovehiculo()){
                    Fecha fechaReparacion = regR.getFechaSalida();
                    int anioReparacion = fechaReparacion.getAnio(); // Obtenemos el a�o del registro

                    // Si es el mismo a�o usamos el cuit del registro para ir a archivo clientes
                    if(vecAnios[i] == anioReparacion){
                        int cantidadClientes = archiClientes.contarRegistros();

                        // Recorremos el archivo clientes para conseguir el tipo de cliente
                        for(int j = 0; j < cantidadClientes; j++){
                            regC = archiClientes.leerRegistro(j);
                            if(strcmp(regR.getCuit(), regC.getCuit()) == 0){

                                // En el vector seg�n el tipo de cliente acumulamos el importe de la reparaci�n
                                if(regC.getTipoCliente() == 1){
                                    vecTipoUno[i] += regR.getImporte(); // i es el a�o
                                }else{
                                    vecTipoDos[i] += regR.getImporte(); // i es el a�o
                                }
                            }
                        }
                    }
                }
            }
        }

        float totalTipoUno = 0; // Acumulamos el total del tipo 1
        for(int i = 0; i < cantidadAnios; i++){
            totalTipoUno += vecTipoUno[i];
        }

        float totalTipoDos = 0; // Acumulamos el total del tipo 2
        for(int i = 0; i < cantidadAnios; i++){
            totalTipoDos += vecTipoDos[i];
        }

        cout << "--- RECAUDACI�N POR TIPO DE CLIENTE Y A�O ---" << endl << endl;
        cout << "- PARTICULAR -" << endl;
        cout << "-------------------" << endl;
        cout << "A�O  |  RECAUDACION " << endl;
        cout << "-------------------" << endl;
        for(int i = 0; i < cantidadAnios; i++){
            cout << vecAnios[i] << " |  $ " << vecTipoUno[i] << endl;
        }
        cout << "-------------------" << endl;
        cout << "TOTAL   $ " << totalTipoUno << endl << endl;

        cout << "- EMPRESA -" << endl;
        cout << "-------------------" << endl;
        cout << "A�O  |  RECAUDACION " << endl;
        cout << "-------------------" << endl;
        for(int i = 0; i < cantidadAnios; i++){
            cout << vecAnios[i] << " |  $ " << vecTipoDos[i] << endl;
        }
        cout << "-------------------" << endl;
        cout << "TOTAL   $ " << totalTipoDos << endl << endl;

        delete[] vecAnios; // Liberamos memoria
        delete[] vecTipoUno; // Liberamos memoria
        delete[] vecTipoDos; // Liberamos memoria

        system("pause");
    }
}


/// ---------- T R E S ----------
void informeTres(){
    system("cls");
    ArchivoVehiculos archiVehiculos;
    Vehiculo regV;
    Reparacion regR;

    FILE *pArchivoReparaciones = fopen("Reparaciones.dat", "rb");
    if (pArchivoReparaciones == nullptr) {
        cout << "ERROR: No se pudo abrir el archivo de reparaciones." << endl;
        system("pause");
        return;
    }

    int conteoTiposVehiculo[4] = {0}; // Inicializa todos los contadores a cero

    cout << "--- CANTIDAD DE REPARACIONES POR TIPO DE VEHICULO ---" << endl << endl;

    // Bucle para leer cada registro del archivo de reparaciones
    while(fread(&regR, sizeof(Reparacion), 1, pArchivoReparaciones) == 1){
        int posVehiculo = archiVehiculos.buscarPosicion(regR.getPatente()); // Busca la posici�n del veh�culo en su archivo usando la patente de la reparaci�n
        if (posVehiculo >= 0) {
            regV = archiVehiculos.leerRegistro(posVehiculo); // Me traigo la informaci�n del veh�culo
            int tipoVehiculo = regV.getTipoVehiculo();

            // VERIFICAMOS QUE EL TIIPO DE VEHICULO EST� ENTRE 1 Y 4
            if (tipoVehiculo >= 1 && tipoVehiculo <= 4) {
                conteoTiposVehiculo[tipoVehiculo-1]++;
            }
        }
    }
    fclose(pArchivoReparaciones);

    cout << " TIPO DE VEHICULO  |  CANTIDAD " << endl;
    cout << "------------------------------" << endl;
    char nombreTipoChar[15];

    for (int i = 0; i < 4; ++i) {
            cout << " ";
            // Se le asigna el nombre de texto al 'nombreTipoChar' seg�n el tipo de veh�culo (i)
            switch (i) {
                case 0: strcpy(nombreTipoChar, "AUTO"); break;
                case 1: strcpy(nombreTipoChar, "CAMIONETA"); break;
                case 2: strcpy(nombreTipoChar, "CAMION"); break;
                case 3: strcpy(nombreTipoChar, "MICRO OMNIBUS"); break;
            }
            cout << " " << nombreTipoChar;

            if (i == 0) cout << "             | "; // Para Auto
            else if (i == 1) cout << "        | "; // Para Camioneta
            else if (i == 2) cout << "           | "; // Para Camion
            else if (i == 3) cout << "    | "; // Para Micro Omnibus

            cout << " " << conteoTiposVehiculo[i];
            cout << endl;
    }

    cout << endl;
    system("pause");
}


/// ---------- C U A T R O ----------
void informeCuatro() {
    system("cls");
    ArchivoVehiculos archiVehiculos;
    Vehiculo regV;
    Reparacion regR;
    int conteoMarcas[10] = {}; // Acumulamos
    const char* marcaVehiculo[] = {
        "FORD",
        "MERCEDES BENZ",
        "CHEVROLET",
        "TOYOTA",
        "PEUGEOT",
        "VOLVO",
        "VOLKSWAGEN",
        "HONDA",
        "AUDI",
        "RENAULT"
    };

    FILE *pArchivoReparaciones = fopen("Reparaciones.dat", "rb");
    if (pArchivoReparaciones == nullptr) {
        cout << "ERROR: No se pudo abrir el archivo de reparaciones." << endl;
        system("pause");
        return;
    }

    int anioBuscado;
    cout << "--- CANTIDAD DE REPARACIONES ANUALES POR MARCA DE VEHICULO ---" << endl << endl;
    cout << "INGRESE A�O: ";
    cin >> anioBuscado;

    // Entramos en reparaci�n para conseguir la patente y usarla en archivo vehiculos para ver la marca y acumular
    while (fread(&regR, sizeof(Reparacion), 1, pArchivoReparaciones) == 1) {
        int anioReparacion = regR.getFechaEntrada().getAnio(); // A�o del registro
        if (anioReparacion == anioBuscado) { // Si coinciden los a�os

            int posVehiculo = archiVehiculos.buscarPosicion(regR.getPatente()); // Obtenemos la patente
            if (posVehiculo >= 0) {
                regV = archiVehiculos.leerRegistro(posVehiculo); // Conseguimos los datos del registro

                for(int i=0; i<10; i++){
                    if(strcmp(regV.getMarca(), marcaVehiculo[i]) == 0){
                        conteoMarcas[i]++;
                    }
                }
            }
        }
    }
    fclose(pArchivoReparaciones);

    // Mostramos la informaci�n
    cout << endl << "CANTIDAD DE REPARACIONES POR MARCA DE VEHICULO EN EL A�O " << anioBuscado << endl << endl;
    cout << "MARCA            |  CANTIDAD " << endl;
    cout << "-----------------------------" << endl;

    for (int i = 0; i < 10; ++i) {
        cout << marcaVehiculo[i];

        if (i == 0) cout << "             | ";
        else if (i == 1) cout << "    | ";
        else if (i == 2) cout << "        | ";
        else if (i == 3) cout << "           | ";
        else if (i == 4) cout << "          | ";
        else if (i == 5) cout << "            | ";
        else if (i == 6) cout << "       | ";
        else if (i == 7) cout << "            | ";
        else if (i == 8) cout << "             | ";
        else if (i == 9) cout << "          | ";
        cout << conteoMarcas[i];
        cout << endl;
    }
    cout << endl;

    system("pause");
}


/// ---------- C I N C O ----------
void informeCinco(){
    system("cls");
    int anioIngresado;
    ArchivoClientes archiClientes;
    ArchivoReparaciones archiReparaciones;
    Cliente regC;
    Reparacion regR;

    cout << "--- CLIENTE M�S FRECUENTE ---" << endl;
    cout << "INGRESE ANIO (INGRESE 0 PARA VOLVER ATRAS): ";
    cin >> anioIngresado;
    if (anioIngresado == 0) {
        return; // Si ingresan 0 vuelve para atr�s
    }
    cout << endl;

    int cantidadReparaciones = archiReparaciones.contarRegistros();
    int cantidadClientes = archiClientes.contarRegistros();
    int* vec = new int[cantidadClientes](); // Creamos un arreglo din�mico en 0
    Cliente* vecCliente = new Cliente[cantidadClientes]; // Creamos un arreglo din�mico de objetos para ordenar

    // Recorremos cada cliente para buscarlo en las reparaciones y acumular si lo encontramos
    for(int i=0; i<cantidadClientes; i++){
        regC = archiClientes.leerRegistro(i); // Traemos la informaci�n del registro de cliente
        vecCliente[i] = regC;

        for(int x=0; x<cantidadReparaciones; x++){
            regR = archiReparaciones.leerRegistro(x); // Traemos la informaci�n del registro de reparaci�n
            Fecha fechaRegistro = regR.getFechaEntrada();

            if(fechaRegistro.getAnio() == anioIngresado){ // Comparamos que sea el mismo a�o
                if(strcmp(regC.getCuit(), regR.getCuit()) == 0){ // Comparamos el cuit del cliente en el archivo reparaciones
                    vec[i]++; // Si encontramos el cuit del cliente en el registro acumulamos 1
                }
            }
        }
    }

    // Calculamos cu�l es el cliene m�s recurrente (mayor)
    // i -> Posici�n de registro / x -> Posici�n de su siguiente registro
    for(int i = 0; i < cantidadClientes - 1; i++){
        for(int x = i+1; x < cantidadClientes; x++){
            if(vec[i] < vec[x]){
                Cliente auxCliente = vecCliente[i];
                int aux = vec[i];
                vec[i] = vec[x];
                vecCliente[i] = vecCliente[x];
                vec[x] = aux;
                vecCliente[x] = auxCliente;
            }
        }
    }

    cout << "EL CLIENTE MAS FRECUENTE DEL A�O " << anioIngresado << endl;
    cout << "--------------------------------------" << endl;
    cout << vecCliente[0].getCuit() << " | " << vecCliente[0].getApellido() << " " << vecCliente[0].getNombre() << " | " << vec[0] << " REPARACIONES" << endl << endl;

    delete[] vecCliente; // Liberamos memoria
    delete[] vec; // Liberamos memoria
    system("pause");
}



