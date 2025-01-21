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
   uint8_t estadoBoton=0;
   if(++tiempo >= 20){
       estadoAct = gpioRead(BOTON_PIN);
       if(cambiandoEstado && estadoAct == estadoAnt){
           estadoBoton = !estadoAct;
           cambiandoEstado = 0;
       }
    }
   else{
      if(estadoAct != estadoAnt){
         estadoAnt = estadoAct;
         tiempo = 0;
         cambiandoEstado = 1;
       }
   }
   
   return estadoBoton;
}
