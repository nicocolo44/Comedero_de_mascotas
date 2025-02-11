#include "mef.h"
#include <string.h>
#include "eepromUtil.h"
#include "esp.h"

static estadosMef estado;
static uint8_t gramos;
static uint8_t hora[6];
static uint8_t i=0;
const uint8_t* arregloHoras[]={"14:00","16:00","20:00","21:00"};
void mefInit(){
   estado = PRINCIPAL;
   lcdInit(16,2,5,8);
   eepromInit();
}

void mefUpdate(uint8_t sentido,uint8_t boton ,uint8_t cancelar){

   switch(estado){
      case PRINCIPAL:
                     if(sentido==1)
                        estado=OPCION_COMIDA;
                     else if(sentido==2)
                        estado=DAR_COMIDA;
                     break;
      case OPCION_COMIDA:
                     if(boton){
                        estado=ELEGIR_CANTIDAD_COMIDA; 
                        gramos=eepromReadGramos();
                        }
                     else if(sentido==1)
                        estado=OPCION_HORA;
                     else if(sentido==2)
                        estado=PRINCIPAL;
                     break;
      case ELEGIR_CANTIDAD_COMIDA:
                     if(boton){
                        estado=OPCION_COMIDA;
                        espSendGramosAServir(gramos);
                        eepromWriteGramos(gramos);
                     }
                     else if(cancelar)
                        estado=OPCION_COMIDA;
                     else if(sentido==1)
                        gramos++;
                     else if(sentido==2){
                        gramos--;
                     }
                     break;
      case OPCION_HORA:
                     if(boton){
                        estado=DEFINIR_HORA;
                        eepromReadHora(hora);
                        }
                     else if(sentido==1)
                        estado=DAR_COMIDA;
                     else if(sentido==2)
                        estado=OPCION_COMIDA;
                     break;
      case DEFINIR_HORA:
                     if(boton){
                        estado=OPCION_HORA;
                        //Guardo hora de comida en eeprom
                        espSendHora(hora);
                        eepromWriteHora(hora);
                     }
                     else if(cancelar){
                        estado=OPCION_HORA;}
                     
                     break;
      case DAR_COMIDA:
                     if(boton)
                        estado=DAR_COMIDA2;
                     else if(sentido==1)
                        estado=PRINCIPAL;
                     else if(sentido==2)
                        estado=OPCION_HORA;
                     break;
      case DAR_COMIDA2:
                     if(boton){
                        lcdGoToXY(1,1);
                        lcdSendStringRaw("Dispensando...  ");
                        lcdGoToXY(1,2);
                        lcdSendStringRaw("Espere por favor");
                        dar_comida();
                        estado=PRINCIPAL;
                        }
                     else if(cancelar)
                        estado=DAR_COMIDA;
                     break;
      default:
         lcdGoToXY(1,1);
         lcdSendStringRaw("Error           ");
         lcdGoToXY(1,2);
         lcdSendStringRaw("Espere por favor");
         break;
   }  
   
   //***********************************************************************
   switch (estado) {
      uint8_t bufferG[4];
        case PRINCIPAL:
            lcdGoToXY(1, 1);
            lcdSendStringRaw("HH:MM           "); // Simula la hora
            lcdGoToXY(1, 2);
            lcdSendStringRaw("Porcentaje comida");
            break;

        case OPCION_COMIDA:
            lcdGoToXY(1, 1);
            lcdSendStringRaw("Eleg cant comida");
            lcdGoToXY(1, 2);
            lcdSendStringRaw("                ");
            break;

        case ELEGIR_CANTIDAD_COMIDA:
            lcdGoToXY(1,1);
            //Mostrar opcion
            lcdSendStringRaw("Eleg cant comida");
            lcdGoToXY(1,2);
            //MOSTRAR GRAMOS
            sprintf(bufferG,"%d",gramos);
            lcdSendStringRaw(bufferG);
            lcdSendStringRaw(" gramos      ");
            break;

        case OPCION_HORA:
            lcdGoToXY(1,1);
            //Mostrar opcion
            lcdSendStringRaw("Elegir hora     ");
            lcdGoToXY(1,2);
            lcdSendStringRaw("                ");
            break;

        case DEFINIR_HORA:
            lcdGoToXY(1,1);
            //Mostrar opcion
            lcdSendStringRaw("Elegir hora     ");
            lcdGoToXY(1,2);
            //MOSTRAR HORAS
            if(sentido==1){
               //aumento hora
               if(++i==4)
                  i=0;
               strcpy(hora,arregloHoras[i]);
               }
            else if(sentido==2){
               //Disminuyo hora
               if(--i==255)
                  i=3;
               strcpy(hora,arregloHoras[i]);
            }
            lcdSendStringRaw(hora);
            lcdSendStringRaw("           ");
            break;

        case DAR_COMIDA:
            lcdGoToXY(1,1);
            //Mostrar opcion
            lcdSendStringRaw("Dar comida");
            lcdGoToXY(1,2);
            lcdSendStringRaw("                ");
            break;

        case DAR_COMIDA2:
            lcdGoToXY(1,1);
            //Mostrar opcion
            lcdSendStringRaw("Dar comida");
            lcdGoToXY(1,2);
            lcdSendStringRaw("Confirmar?      ");
            break;
        default:
            lcdGoToXY(1, 1);
            lcdSendStringRaw("Error           ");
            lcdGoToXY(1, 2);
            lcdSendStringRaw("Espere por favor");
            break;
    }
   
}