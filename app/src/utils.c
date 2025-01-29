#include "utils.h"

void dar_comida(){
    uint32_t pesoADispensar = 0; // no se si lo leemos de la eeprom o viene como parametro
    int32_t lectura;
    int8_t delayBuzzer = 0;

    HX711_plato_Read(&lectura);
    float peso = HX711_plato_GetWeight(lectura);

    while (pesoADispensar > peso) {
        for (int i = 0; i < 10; i++) {
            // dar un paso del motor (falta librería en el proyecto principal)
            delay(3);
        }
        if (++delayBuzzer == 333) {
            Buzzer_Toggle();
            delayBuzzer = 0;
        }
        HX711_plato_Read(&lectura);
        peso = HX711_plato_GetWeight(lectura);
    }

    Buzzer_Off();
}
