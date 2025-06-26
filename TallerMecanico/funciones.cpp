#include "funciones.h"
#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;


void cargarCadena(char *palabra, int tamanio){
    int i=0;
    fflush(stdin);
    for (i=0; i<tamanio; i++){
        palabra[i] = cin.get();
        if (palabra[i] == '\n'){
            break;
        }
    }
    palabra[i] = '\0';
    fflush(stdin);
}


void pasarAMayusculas(char* cadena) {
    for(int i = 0; cadena[i] != '\0'; i++) {
        cadena[i] = toupper(cadena[i]);
    }
}


bool fechaMenorIgual(Fecha fechaEntrada, Fecha fechaDos){
    if(fechaEntrada.getAnio() < fechaDos.getAnio()){
        return true;
    // Los años son iguales entonces comparo los meses
    }else if(fechaEntrada.getAnio() == fechaDos.getAnio()){
        if(fechaEntrada.getMes() < fechaDos.getMes()){
            return true;
        // Los meses son iguales entonces comparo los días
        }else if(fechaEntrada.getMes() == fechaDos.getMes()){
            if(fechaEntrada.getDia() <= fechaDos.getDia()){
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }
    }else{
        return false;
    }
}


bool fechaMayorIgual(Fecha fechaEntrada, Fecha fechaUno){
    if(fechaEntrada.getAnio() > fechaUno.getAnio()){
        return true;
    // Los años son iguales entonces comparo los meses
    }else if(fechaEntrada.getAnio() == fechaUno.getAnio()){
        if(fechaEntrada.getMes() > fechaUno.getMes()){
            return true;
        // Los meses son iguales entonces comparo los días
        }else if(fechaEntrada.getMes() == fechaUno.getMes()){
            if(fechaEntrada.getDia() >= fechaUno.getDia()){
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }
    }else{
        return false;
    }
}



