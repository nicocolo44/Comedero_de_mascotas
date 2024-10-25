/*============================================================================
 * Autor:
 * Licencia:
 * Fecha:
 *===========================================================================*/

// DEPENDENCIAS

#include "app.h"         // <= Su propia cabecera (opcional)
#include "sapi.h"        // <= Biblioteca sAPI
#include "chip.h"
#include "sapi_esp8266.h"
#include "sapi_lcd.h"

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
   // ---------- CONFIGURACIONES ------------------------------

   // Inicializar y configurar la plataforma
   boardConfig();
   // Crear varias variables del tipo booleano
   bool_t buttonValue = OFF;
   lcdInit(16,2,5,8);
   lcdGoToXY(0,0);
   int x=0;
   lcdSendStringRaw("Cargando...     ");
   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE ) {
      if(x < 16){
         lcdGoToXY(x,1);
         lcdSendStringRaw("+");
         x++;
      }
      else{
         lcdClear();
         lcdGoToXY(0,0);
         lcdSendStringRaw("Funciona bien pa");
         lcdGoToXY(0,1);
         lcdSendStringRaw("................");
      }
      delay(500);
   }

   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
   // directamenteno sobre un microcontroladore y no es llamado por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}
