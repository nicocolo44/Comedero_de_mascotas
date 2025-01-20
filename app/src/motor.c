#include "motor.h"

static uint8_t pos;
static uint8_t PINK_PIN,YELLOW_PIN,ORANGE_PIN,RED_PIN;
static uint8_t paso[4][4] ={{1,1,0,0}
                     ,{0,1,1,0}
                     ,{0,0,1,1}
                     ,{1,0,0,1}};

void motorInit(uint8_t red,uint8_t orange,uint8_t yellow,uint8_t pink){
   RED_PIN=red;
   ORANGE_PIN=orange;
   YELLOW_PIN=yellow;
   PINK_PIN=pink;
   gpioConfig(pink,GPIO_OUTPUT);
   gpioConfig(yellow,GPIO_OUTPUT);
   gpioConfig(orange,GPIO_OUTPUT);
   gpioConfig(red,GPIO_OUTPUT);
   pos=0;
}

void motorOn(){
   gpioWrite(RED_PIN,(paso[pos][0]));
   gpioWrite(ORANGE_PIN,(paso[pos][1]));
   gpioWrite(YELLOW_PIN,(paso[pos][2]));
   gpioWrite(PINK_PIN,(paso[pos][3]));
   pos++;
   if(pos==4)
      pos=0;
}