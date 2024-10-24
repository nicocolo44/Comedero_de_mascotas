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

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
   // ---------- CONFIGURACIONES ------------------------------

   // Inicializar y configurar la plataforma
   boardConfig();

   // Crear varias variables del tipo booleano
   bool_t buttonValue = OFF;
   bool_t ledValue    = OFF;
   // Crear variable del tipo tick_t para contar tiempo
   tick_t timeCount   = 0;
   Chip_EEPROM_Init(LPC_EEPROM);
   esp8266InitHttpServer("a", "a");
   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE ) {
      
      
      
   }

   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
   // directamenteno sobre un microcontroladore y no es llamado por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}
