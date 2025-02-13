/*============================================================================
 * Autor:
 * Licencia:
 * Fecha:
 *===========================================================================*/

// DEPENDENCIAS

#include "app.h"  // <= Su propia cabecera (opcional)
#include "sapi.h" // <= Biblioteca sAPI
#include "boton.h"
#include "mef.h"
#include "encoder.h"
#include "eeprom.h"
#include "motor.h"
#include "esp.h"
#include <string.h>
#include "hx711_plato.h"
#include "hx711_tarro.h"
#include "eepromUtil.h"
#include "utils.h"
#include "chip.h"
#include "sapi_timer.h"// creo que estos dos se pueden sacar
#include "sapi_uart.h" //



#define BUFFER_SIZE 3000
char buffer[BUFFER_SIZE];
char hora[6];
uint8_t gramosAServir;
rtc_t rtc;
volatile uint8_t SEND_TO_ESP_FLAG = 0;
volatile uint8_t WHEIGH_PLATE_FLAG = 0;
volatile uint8_t WHEIGH_BUCKET_FLAG = 0;
volatile uint8_t CHECK_TIME_FLAG = 0;


int32_t lecturaTarro= 0;
int16_t pesoTarro = 0;


int32_t lecturaPlato = 0;
int16_t pesoPlato = 0;

uint8_t sentido=0;
uint8_t botonEncoder=0;

uint8_t botonCancelar=0;

void timerCallback(void *param) {
   static uint8_t CHECK_TIME_COUNTER = 0;
   static uint8_t CHECK_SEND_TO_ESP = 0;
   if(++CHECK_SEND_TO_ESP == 5){
      SEND_TO_ESP_FLAG = 1;
      CHECK_SEND_TO_ESP = 0;
   }
   WHEIGH_PLATE_FLAG = 1;
   WHEIGH_BUCKET_FLAG = 1;
   if(++CHECK_TIME_COUNTER == 60){
      CHECK_TIME_FLAG = 1;
      CHECK_TIME_COUNTER = 0;
   }
}

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main(void)
{
   boardConfig();
   
   inicializarRtc();
   
   //DEBUG
   uartConfig(UART_USB, 115200);
   uartWriteString(UART_USB, "empezando");
   //Initialization
   eepromInit();
   espInit(115200);
   motorInit(GPIO7,GPIO5,GPIO3,GPIO1);
   HX711_plato_Init(T_FIL1, T_COL2);
   HX711_tarro_Init(T_FIL3, T_FIL2);
   encoderInit(ENET_TXEN,GPIO2,GPIO4,3);
   mefInit();
   Buzzer_Init(T_FIL0);
   botonInit(ENET_RXD1,20);
   Timer_Init( 0, Timer_microsecondsToTicks( 1000000 ), timerCallback );
   
   gramosAServir = eepromReadGramos();
   eepromReadHora(hora);
   uint8_t horaRtc[6];

   while (TRUE)
   {
      if(WHEIGH_BUCKET_FLAG  && HX711_tarro_Read(&lecturaTarro)){
         pesoTarro = HX711_tarro_GetWeight(lecturaTarro);
         WHEIGH_BUCKET_FLAG = 0;
      }
      if(WHEIGH_PLATE_FLAG && HX711_plato_Read(&lecturaPlato)){
         pesoPlato = HX711_plato_GetWeight(lecturaPlato);
         WHEIGH_BUCKET_FLAG = 0;
      }
      if(SEND_TO_ESP_FLAG){
         espSendData(pesoPlato, pesoTarro);
         SEND_TO_ESP_FLAG = 0;
      }
      if(CHECK_TIME_FLAG){
         CHECK_TIME_FLAG = 0;
         //leer la hora del RTC y comparar con la actual 
         //rtcRead(&rtc);
         //sprintf(horaRtc, "%02d:%02d", rtc.hour, rtc.min);
         //if((strcmp(horaRtc,hora)==0)){
            //dar_comida();
         //}
      }
      
      if (espReceiveData(buffer, BUFFER_SIZE))
      {
         procesarRespuesta(buffer);
         
      }
      
      sentido=encoderRead(&botonEncoder);
      botonCancelar = botonRead();
      if(sentido != 0 || botonEncoder != 0 || botonCancelar != 0){
         mefUpdate(sentido,botonEncoder,botonCancelar); 
      }
      
      
       delay(1);
   }

   return 0;
}