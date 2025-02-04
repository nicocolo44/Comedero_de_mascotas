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
#include "sapi_timer.h"
#include "sapi_uart.h"



#define BUFFER_SIZE 3000
char buffer[BUFFER_SIZE];
char hora[6];
uint8_t gramosAServir;

uint8_t SEND_TO_ESP_FLAG = 0;
uint8_t WHEIGH_PLATE_FLAG = 0;
uint8_t WHEIGH_BUCKET_FLAG = 0;
uint8_t CHECK_TIME_FLAG = 0;


int32_t lecturaTarro;
int32_t pesoTarro;

int32_t lecturaPlato;
int32_t pesoPlato;

uint8_t sentido=0;
uint8_t botonEncoder=0;

uint8_t botonCancelar=0;

void timerCallback(void *param) {
   static uint8_t CHECK_TIME_COUNTER = 0;
   SEND_TO_ESP_FLAG = 1;
   WHEIGH_PLATE_FLAG = 1;
   WHEIGH_BUCKET_FLAG = 1;
   if(++CHECK_TIME_COUNTER == 60){
      CHECK_TIME_FLAG = 1;
   }
}

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main(void)
{
   boardConfig();
   //DEBUG
   uartConfig(UART_USB, 115200);
   //Initialization
   eepromInit();
   eepromWriteGramos(100);
   
   
   
   espInit(115200);
   motorInit(GPIO1,GPIO3,GPIO5,GPIO7);
   //HX711_plato_Init(T_FIL1, T_COL2);
   //HX711_tarro_Init();
   encoderInit(ENET_TXEN,GPIO2,GPIO4,3);
   mefInit();
   mefUpdate(0,0,0);
   //buzzer
   botonInit(ENET_RXD1,20);
   Timer_Init( 0, Timer_microsecondsToTicks( 1000000 ), timerCallback );
   
   gramosAServir = eepromReadGramos();
   eepromReadHora(hora);
   

   while (TRUE)
   {
      if(WHEIGH_BUCKET_FLAG  /*&& HX711_tarro_Read(&lecturaTarro)*/){
         //pesoTarro = HX711_tarro_GetWeight(lecturaTarro);
         WHEIGH_BUCKET_FLAG = 0;
      }
      if(WHEIGH_PLATE_FLAG /*&& HX711_plato_Read(&lecturaPlato)*/){
         //pesoPlato = HX711_plato_GetWeight(lecturaPlato);
         WHEIGH_BUCKET_FLAG = 0;
      }
      if(SEND_TO_ESP_FLAG){
         espSendData(hora, gramosAServir, pesoPlato, pesoTarro);
         gramosAServir = eepromReadGramos();
         eepromReadHora(hora);
         SEND_TO_ESP_FLAG = 0;
      }
      if(CHECK_TIME_FLAG){
         CHECK_TIME_FLAG = 0;
         //leer la hora del RTC y comparar con la actual
         if(0){
            dar_comida();
         }
      }
      
      if (espReceiveData(buffer, BUFFER_SIZE))
      {
         procesarRespuesta(buffer);
      }
      
      sentido=encoderRead(&botonEncoder);
      //leer el otro boton
      botonCancelar = botonRead();
      if(sentido != 0 || botonEncoder != 0 || botonCancelar != 0){
         mefUpdate(sentido,botonEncoder,botonCancelar); 
      }
      
      
       delay(1);
   }

   return 0;
}