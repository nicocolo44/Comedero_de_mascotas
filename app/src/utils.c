#include "utils.h"


uint32_t pesoADispensar = 0; //no se si lo leemos de la eeprom o viene como parametro, como quieras

void dar_comida() {
    int32_t lectura;
    HX711_Read(&lectura);
    float peso = HX711_GetWeight(lectura);
    while(pesoADispensar > peso) {
        for(int i = 0; i < 10; i++) { //hago este for para que no este todo el tiempo chequeando, que haga varios pasos y despues chequee
            //dar un paso del motor que no tengo la libreria aca en el main
            delay(3);
        }
        HX711_Read(&lectura);
        peso = HX711_GetWeight(lectura);
    }
}