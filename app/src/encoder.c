#include "encoder.h"

static uint8_t CLK_PIN;
static uint8_t DT_PIN;
static uint8_t SW_PIN;
static uint8_t SENS;
static uint8_t cont1=0;
static uint8_t cont2=0;
static uint8_t contB=0;
static uint8_t apretado=0;
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
      
      if(apretado || gpioRead(SW_PIN)==0){
         apretado=1;
         contB++;
         if(contB==15){
            if(gpioRead(SW_PIN)==0){
               *estadoBoton=1;
            }
            else{
               *estadoBoton=0;
            }
            contB=0;
            apretado=0;
         }
      }
      
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