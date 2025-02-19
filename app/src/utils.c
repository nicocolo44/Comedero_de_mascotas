#include "utils.h"
#include "mef.h"
#define TIMEOUT 5000
#define PROG 1


void dar_comida(){
   lcdGoToXY(1,2);
   lcdSendStringRaw("                ");
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
   uint8_t pesoADispensar = eepromReadGramos();
   int32_t lectura;
   int delayBuzzer = 0;
   uint8_t botonCancelar = 0;
   uint16_t time = 0;
   int16_t peso = 0;
   if(HX711_plato_Read(&lectura))
      peso = HX711_plato_GetWeight(lectura);
   lcdGoToXY(1,2);
   int i;
   int j=1;
   uint8_t barraProgreso = pesoADispensar/16;
    while (pesoADispensar > peso) {
        for (i = 0; i < 10; i++) {
            motorOn();
            delay(3);
        }
        botonCancelar = botonRead();
        if(botonCancelar || ++time >= TIMEOUT){
           gpioWrite(LED1, HIGH);
           gpioWrite(LED2, HIGH);
           gpioWrite(LED3, HIGH);
           break;
        }
        gpioWrite(LED1, HIGH);
        
        if(peso>(barraProgreso*j)){
           lcdData(PROG);
           j++;
         }
        
        if (++delayBuzzer > 33) {
           
            Buzzer_Toggle();
            delayBuzzer = 0;
        }
        if(HX711_plato_Read(&lectura))
         peso = HX711_plato_GetWeight(lectura);
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
   mefUpdate(0,0,0);
}

void inicializarRtc(){
   rtc_t rtc;

   // Extraer fecha de compilación (ejemplo: "Feb 13 2025")
   char mesStr[4];
   sscanf(__DATE__, "%s %d %d", mesStr, &rtc.mday, &rtc.year);

   // Convertir el nombre del mes a número
   const char* meses[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", 
                          "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
   for (int i = 0; i < 12; i++) {
       if (strcmp(mesStr, meses[i]) == 0) {
           rtc.month = i + 1;
           break;
       }
   }

   // Extraer hora de compilación (ejemplo: "14:05:30")
   sscanf(__TIME__, "%d:%d:%d", &rtc.hour, &rtc.min, &rtc.sec);

   rtc.wday = 0; // Si necesitas el día de la semana, deberías calcularlo.

   rtcInit(&rtc);
   rtcWrite(&rtc);
}