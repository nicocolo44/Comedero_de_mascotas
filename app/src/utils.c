#include "utils.h"

#define TIMEOUT 1340 //APROXIMADAMENTE 40 SEGUNDOS
#define PROG 1
void dar_comida(){
   const char progreso[8] = {
   0b00000,
   0b00000,
   0b11111,
   0b11111,
   0b11111,
   0b11111,
   0b00000,
   0b00000
   };
   lcdCreateChar(PROG,progreso);
   gpioWrite(LED2, HIGH);
   float pesoADispensar = 690000;
   int32_t lectura;
   int delayBuzzer = 0;
   uint8_t botonCancelar = 0;
   uint16_t time = 0;
   lcdGoToXY(1,2);
   HX711_plato_Read(&lectura);
   float peso = HX711_plato_GetWeight(lectura);
   lectura = 0;
   int i;
   int j=1;
   float barraProgreso = pesoADispensar/16;
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
        
        if(lectura>(barraProgreso*j)){
           lcdData(PROG);
           j++;
         }
        
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