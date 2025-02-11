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
#include "HX711_plato.h"


int32_t lectura;
int16_t valor;
// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
   // ---------- CONFIGURACIONES ------------------------------

   // Inicializar y configurar la plataforma
   boardConfig();
   HX711_plato_Init(T_FIL3, T_FIL2); //faltan las entradas de los pines
   //HX711_tarro_Init(); //faltan las entradas de los pines

   // Hacer el Tare
   HX711_plato_Tare(10);
   //HX711_tarro_Tare(10);

   //quiero mandar un mensaje a la terminal serie
   uartConfig(UART_USB, 115200); //falta el baudrate
   gpioWrite(LED1, HIGH);
   delay(10000);
   gpioWrite(LED2, HIGH);
   gpioWrite(LED1, LOW);
   HX711_plato_Calibrate(34); //hay que ver de cuantos gramos es esto o que le ponemos
   //while(!gpioRead(TEC1));
   //hx711_tarro_Calibrate(1000); //hay que ver de cuantos gramos es esto o que le ponemos

   printf("Valor base plato: %d\n", HX711_plato_GetValorBase());
   printf("Factor de conversion plato: %d\n", HX711_plato_GetFactorConversion());
   //printf("Valor base tarro: %d\n", HX711_tarro_GetValorBase());
   //printf("Factor de conversion tarro: %d\n", HX711_tarro_GetFactorConversion());
   //No me acuerdo si nos funcionaba asi o simplemente imprimimos el valor y no un string

   
   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE ) {
      if(HX711_plato_Read(&lectura)){
         gpioWrite(LED1, HIGH);
         valor = HX711_plato_GetWeight(lectura);
         printf("Lectura: %ld\n", lectura);
         printf("valor: %d\n", valor);
      }
      delay(1000);
   }

   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
   // directamenteno sobre un microcontroladore y no es llamado por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}
