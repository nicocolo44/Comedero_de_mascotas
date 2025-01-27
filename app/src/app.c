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
   lcdInit(16,2,5,8);
   Board_EEPROM_init();
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
   
   uint8_t arr[4]={'1','2','3','\0'};
   uint32_t DIR=0x0;
   uint8_t car;
   lcdGoToXY(1,1);
   Board_EEPROM_writeByte(DIR,arr[0]);
   car=Board_EEPROM_readByte(DIR);
   lcdData(car);
   DIR++;
   Board_EEPROM_writeByte(DIR,arr[1]);
   car=Board_EEPROM_readByte(DIR);
   lcdData(car);
   
   while( TRUE ) {
      
      
      delay(1);
   }
   
   return 0;
}