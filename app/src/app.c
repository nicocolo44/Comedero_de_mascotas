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

   HX711_Init(T_FIL1, T_COL2);
   printf("Comenzando lecturas");
   int32_t data; // Variable para almacenar el dato leído
   int8_t leyo;
   gpioWrite(LED1, HIGH);
   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE ) {
      leyo = HX711_Read(&data);
      if (leyo) {
         printf("Valor leído: %ld\n", data);
      }
      printf("Leyo: %hhd\n", leyo); 
      gpioToggle(LED1);
      delay(1000);
      
   }

   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
   // directamenteno sobre un microcontroladore y no es llamado por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}
