#include "boton.h"

static uint8_t BOTON_PIN;
static uint8_t tiempo;
void botonInit(uint8_t pin,uint8_t time){
   BOTON_PIN=pin;
   tiempo= time;
   gpioConfig(BOTON_PIN,GPIO_INPUT_PULLUP);
}
   
uint8_t botonRead(){
   static uint8_t estadoAnt=0;
   static uint8_t cambiandoEstado=0;
   static uint8_t estadoAct=0;
   static uint8_t tiempoActual=0;
   /*
   if(++tiempoActual >= tiempo){
       estadoAct = gpioRead(BOTON_PIN);
       if(cambiandoEstado && estadoAct == estadoAnt){
           cambiandoEstado = 0;
           if(!estadoAct)
                     return 1;
           else
              return 0;
       }
       else{
           if(estadoAct != estadoAnt){
               estadoAnt = estadoAct;
               tiempoActual = 0;
               cambiandoEstado = 1;
            }
      }
   }
   */
   estadoAct = gpioRead(BOTON_PIN);
   if(cambiandoEstado || estadoAct!=estadoAnt){
      cambiandoEstado=1;
       if(++tiempoActual>=tiempo && estadoAct == estadoAnt){
         cambiandoEstado = 0;
         tiempoActual=0;
         if(!estadoAct){
            return 1;}
         else {
            return 0;}
       }
    }
   return 0;
}
