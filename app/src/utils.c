#include "utils.h"

#define TIMEOUT 1340 //APROXIMADAMENTE 40 SEGUNDOS

void dar_comida(){
   float pesoADispensar = 690000;
   int32_t lectura;
   int delayBuzzer = 0;
   uint8_t botonCancelar = 0;
   uint16_t time = 0;

    //HX711_plato_Read(&lectura);
    //float peso = HX711_plato_GetWeight(lectura);
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
        if (++delayBuzzer > 33) {
           gpioToggle(LED2);
            Buzzer_Toggle();
            delayBuzzer = 0;
        }
        //HX711_plato_Read(&lectura);
        //peso = HX711_plato_GetWeight(lectura);
        lectura = 0;
    }
    Buzzer_Off();
    gpioWrite(LED2, LOW);
}


void procesarRespuesta(char *data){
   char time[6];
   int darComida, gramosAServir;
   char buffer[100];
   if (sscanf(data, "%5[^,],%d,%d", time, &gramosAServir, &darComida) != 3) {
        return; // Descarta el mensaje si no cumple con el formato esperado
    }

   if(darComida){
      gpioWrite(LED3,HIGH);
      mefDarComida();
   }
   sprintf(buffer, "%d", gramosAServir);
   
   uartWriteString(UART_USB, buffer);
   eepromWriteGramos(gramosAServir);
   eepromWriteHora(time);
}

void inicializarRtc(){
   rtc_t rtc;
   // Completar estructura RTC
   rtc.year = 2025;
   rtc.month = 2;
   rtc.mday = 5;
   rtc.wday = 0;//lo deje en 0 porque ni idea que es
   rtc.hour = 14;
   rtc.min = 00;
   rtc.sec= 0;
   rtcInit(&rtc);
   rtcWrite( &rtc );   
}