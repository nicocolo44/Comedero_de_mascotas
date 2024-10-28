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
   /*
   lcdInit(16,2,5,8);
   lcdGoToXY(0,0);
   int x=0;
   lcdSendStringRaw("Cargando...     ");
   // ---------- LCD --------------------------
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
   */
   //----------------------------- ENCODER--------------------------
   /*
   gpioConfig(TX_EN,GPIO_INPUT);
   gpioConfig(GPIO2,GPIO_INPUT);
   gpioConfig(GPIO4,GPIO_INPUT);
   uint8_t ultEst=gpioRead(TX_EN);
   uint8_t est;
   while( TRUE ) {
      est= gpioRead(TX_EN);
      if(ultEst != est){
         if(est != gpioRead(GPIO2)){
            gpioWrite(LED1,1);
            gpioWrtie(LED2,0);
         }
         else{
            gpioWrite(LED1,0);
            gpioWrtie(LED2,1);
         }
      }
      ultEst=est;
      delay(10);
   }
   */
  
   // ---------- ENCODER + LCD--------------------------
   /*
   gpioConfig(TX_EN,GPIO_INPUT);
   gpioConfig(GPIO2,GPIO_INPUT);
   gpioConfig(GPIO4,GPIO_INPUT);
   lcdInit(16,2,5,8);
   lcdGoToXY(0,0);
   lcdClear();
   uint8_t d=48;
   uint8_t ultEst=gpioRead(TX_EN);
   uint8_t est;
   while( TRUE ) {
      est= gpioRead(TX_EN);
      if(ultEst != est){
         if(est != gpioRead(GPIO2)){
            d++;
            lcdData(d);
         }
         else{
            if(d>1)
               d--;
            lcdData(d);
         }
         lcdClear();
      }
      ultEst=est;
      delay(10);
   }
   */
   
   return 0;
}
