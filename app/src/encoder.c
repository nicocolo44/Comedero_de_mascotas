#include "encoder.h"

static uint8_t CLK_PIN;
static uint8_t DT_PIN;
static uint8_t SW_PIN;
static uint8_t SENS;
static uint8_t ultEst;
void encoderInit(uint8_t clk,uint8_t dt,uint8_t sw,uint8_t sens){
   CLK_PIN=clk;
   DT_PIN=dt;
   SW_PIN=sw;
   SENS=sens;
   gpioConfig(CLK_PIN,GPIO_INPUT);
   gpioConfig(DT_PIN,GPIO_INPUT);
   gpioConfig(SW_PIN,GPIO_INPUT_PULLUP);
   ultEst=gpioRead(CLK_PIN);
}

uint8_t encoderRead(uint8_t* estadoBoton){
   static uint8_t cont1=0;
   static uint8_t cont2=0;
   static uint8_t tiempo=0;
   static uint8_t estadoAnt=0;
   static uint8_t estadoAct=0;
   static uint8_t cambiandoEstado=0;
   
   uint8_t giro;
   uint8_t est = gpioRead(CLK_PIN);
   if(ultEst != est){
      if(est != gpioRead(DT_PIN)){
         cont1++;
         cont2=0;
      }
      else{
         cont2++;
         cont1=0;
      }
   }
   ultEst=est;
   
   if(++tiempo >= 20){
       estadoAct = gpioRead(SW_PIN);
       if(cambiandoEstado && estadoAct == estadoAnt){
           //*estadoBoton = !estadoAct;
           cambiandoEstado = 0;
           if(!estadoAct)
                     *estadoBoton=1;
           else 
              *estadoBoton=0;
       }
       else{
           if(estadoAct != estadoAnt){
               estadoAnt = estadoAct;
               tiempo = 0;
               cambiandoEstado = 1;
            }
      }
   }
   else *estadoBoton=0;
      if(cont1==SENS){
         cont1=0;
         return 1;
      }
      if(cont2==SENS){
         cont2=0;
         return 2;         
      }
      return 0;
      
}