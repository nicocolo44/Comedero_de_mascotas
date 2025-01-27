#include "eepromUtil.h"
#include <stdio.h>

void eepromInit(){
   Board_EEPROM_init();
}

uint8_t eepromReadGramos(){
   uint8_t gramos;
   gramos=Board_EEPROM_readByte(DIR_GRAMOS);
   return gramos;
}

void eepromWriteGramos(uint8_t gramos){
   Board_EEPROM_writeByte(DIR_GRAMOS,gramos);
}

void eepromReadHora(uint8_t *hora){
   uint8_t i;
   for(i=0;i<5;i++){
      hora[i]=Board_EEPROM_readByte(DIR_HORA+i);//FORMATO HH:MM
   }
   hora[5]='\0';
}

void eepromWriteHora(uint8_t* hora){
   uint8_t i;
   for(i=0;i<5;i++){
      Board_EEPROM_writeByte(DIR_HORA+i,hora[i]);//FORMATO HH:MM
   }
}

