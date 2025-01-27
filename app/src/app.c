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
   /*
   encoderInit(ENET_TXEN,GPIO2,GPIO4,3);
   mefInit();
   mefUpdate(0,0,0);
   //botonInit(GPIO4,20);
   uint8_t sentido=0;
   uint8_t boton=0;
   while( TRUE ) {
      sentido=encoderRead(&boton);
      if(sentido != 0 || boton != 0){
         mefUpdate(sentido,boton,0);
      }
      
      delay(1);
   }
   */
   Board_EEPROM_init();
   uint8_t* hora="14:00";
   uint8_t i;
   for(i=0;i<5;i++){
      Board_EEPROM_writeByte(0x10+i,hora[i]);//FORMATO HH:MM
   }
   
   while(TRUE){
      }
   return 0;
}