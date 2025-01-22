/*============================================================================
 * Autor:
 * Licencia:
 * Fecha:
 *===========================================================================*/

// DEPENDENCIAS

#include "app.h"         // <= Su propia cabecera (opcional)
#include "sapi.h"        // <= Biblioteca sAPI
#include "boton.h"
#include "mef.h"
#include "encoder.h"
#include "eeprom.h"
// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
   // ---------- CONFIGURACIONES ------------------------------

   // Inicializar y configurar la plataforma
   boardConfig();
   //encoderInit(ENET_TXEN,GPIO2,GPIO4,3);
   //mefInit();
   //mefUpdate(0,0,0);
   botonInit(ENET_RXD1,20);
   uint8_t sentido=0;
   uint8_t boton=0;
   while( TRUE ) {
      boton=botonRead();
      if(boton !=0){
         //mefUpdate(sentido,boton,botonRead());
         gpioWrite(LED3,HIGH);
         }
      
      delay(1);
   }
   
   
   return 0;
}