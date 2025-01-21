/*============================================================================
 * Autor:
 * Licencia:
 * Fecha:
 *===========================================================================*/

// DEPENDENCIAS

#include "app.h"         // <= Su propia cabecera (opcional)
#include "sapi.h"        // <= Biblioteca sAPI
#include "encoder.h"
#include "eeprom.h"
// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
   // ---------- CONFIGURACIONES ------------------------------

   // Inicializar y configurar la plataforma
   boardConfig();
   
   encoderInit(ENET_TXEN,GPIO2,GPIO4,3);
   uint8_t sentido=0;
   uint8_t boton=0;
   while( TRUE ) {
      
      sentido=encoderRead(&boton);
      if(sentido==1){
         gpioWrite(LED1,HIGH);
         gpioWrite(LED2,LOW);
         gpioWrite(LED3,LOW);
      }
      else if(sentido==2){
         gpioWrite(LED2,HIGH);
         gpioWrite(LED1,LOW);
         gpioWrite(LED3,LOW);
      }
      if(boton){
         gpioWrite(LED3,HIGH);
      }else
      gpioWrite(LED3,LOW);
      
      delay(1);
   }
   
   
   return 0;
}