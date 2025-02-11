#include "utils.h"

#define TIMEOUT 1340 //APROXIMADAMENTE 40 SEGUNDOS

void dar_comida(){
   gpioWrite(LED2, HIGH);
    float pesoADispensar = 690000;
    int32_t lectura;
    int delayBuzzer = 0;
    uint8_t botonCancelar = 0;
   uint16_t time = 0;

    HX711_plato_Read(&lectura);
    float peso = HX711_plato_GetWeight(lectura);
   lectura = 0;
   int i;
    while (pesoADispensar > lectura) {
        for (i = 0; i < 10; i++) {
            motorOn();
            delay(3);
        }
        botonCancelar = botonRead();
        if(botonCancelar || ++time >= TIMEOUT){
           break;
        }
        gpioWrite(LED1, HIGH);
        if (++delayBuzzer > 33) {
           gpioToggle(LED2);
            Buzzer_Toggle();
            delayBuzzer = 0;
        }
        HX711_plato_Read(&lectura);
        peso = HX711_plato_GetWeight(lectura);
        lectura = 0;
    }
    Buzzer_Off();
    gpioWrite(LED2, LOW);
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
