#include "utils.h"

void dar_comida(){
    float pesoADispensar = 690000;
    int32_t lectura;
    int delayBuzzer = 0;

    HX711_plato_Read(&lectura);
    float peso = HX711_plato_GetWeight(lectura);
   int i;
    while (pesoADispensar > lectura) {
       gpioToggle(LED1);
        for (i = 0; i < 10; i++) {
            motorOn();
            delay(2);
        }
        if (++delayBuzzer > 33) {
           gpioToggle(LED2);
            Buzzer_Toggle();
            delayBuzzer = 0;
        }
        HX711_plato_Read(&lectura);
        peso = HX711_plato_GetWeight(lectura);
    }
    Buzzer_Off();
}


void procesarRespuesta(char *data){
   char time[6];
    int darComida, gramosAServir;
   sscanf(data, "%5[^,],%d,%d", time, &gramosAServir, &darComida);
   uartWriteString(UART_USB, data);
   
   if(darComida)
         dar_comida();
   eepromWriteGramos(gramosAServir);
   eepromWriteHora(time);
}
