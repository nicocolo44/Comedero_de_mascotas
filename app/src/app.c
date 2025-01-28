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
   HX711_plato_Init(); //faltan las entradas de los pines
   HX711_tarro_Init(); //faltan las entradas de los pines

   // Hacer el Tare
   HX711_plato_Tare(10);
   HX711_tarro_Tare(10);

   //quiero mandar un mensaje a la terminal serie
   uartConfig(UART_USB, 115200); //falta el baudrate

   while(!gpioRead(TEC1)); //no se que penes es TEC1 pero lo puso copilot, habria que chequearlo
   hx711_plato_Calibrate(1000); //hay que ver de cuantos gramos es esto o que le ponemos
   while(!gpioRead(TEC1));
   hx711_tarro_Calibrate(1000); //hay que ver de cuantos gramos es esto o que le ponemos

   printf("Valor base plato: %d\n", HX711_plato_GetValorBase());
   printf("Factor de conversion plato: %d\n", HX711_plato_GetFactorConversion());
   printf("Valor base tarro: %d\n", HX711_tarro_GetValorBase());
   printf("Factor de conversion tarro: %d\n", HX711_tarro_GetFactorConversion());
   //No me acuerdo si nos funcionaba asi o simplemente imprimimos el valor y no un string

   
   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE ) {
      
   }

   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
   // directamenteno sobre un microcontroladore y no es llamado por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}
