#include "mef.h"
#include <string.h>

static estadosMef estado;
static uint8_t gramos;
static uint8_t i=0;
const uint8_t* arregloHoras[]={"14:00","16:00","20:00","21:00"};
void mefInit(){
      estado = PRINCIPAL;
      lcdInit(16,2,5,8);
}

void mefUpdate(uint8_t sentido,uint8_t boton ,uint8_t cancelar){
   static uint8_t* hora ="     ";

   switch(estado){
      case PRINCIPAL:
                     if(sentido==1)
                        estado=OPCION_COMIDA;
                     else if(sentido==2)
                        estado=DAR_COMIDA;
                     break;
      case OPCION_COMIDA:
                     if(boton)
                        estado=ELEGIR_CANTIDAD_COMIDA;
                     else if(sentido==1)
                        estado=OPCION_HORA;
                     else if(sentido==2)
                        estado=PRINCIPAL;
                     break;
      case ELEGIR_CANTIDAD_COMIDA:
                     //Leer gramos de eeprom y guardarlos en variable gramos
                     if(boton){
                        estado=OPCION_COMIDA;
                        //Guardo gramos de comida en eeprom?
                     }
                     else if(cancelar)
                        estado=OPCION_COMIDA;
                     else if(sentido==1)
                        gramos++;
                     else if(sentido==2){
                        //if(gramos>0)
                           gramos--;
                     }
                     break;
      case OPCION_HORA:
                     if(boton)
                        estado=DEFINIR_HORA;
                     else if(sentido==1)
                        estado=DAR_COMIDA;
                     else if(sentido==2)
                        estado=OPCION_COMIDA;
                     break;
      case DEFINIR_HORA:
                     if(boton){
                        estado=OPCION_HORA;
                        //Guardo hora de comida en eeprom?
                     }
                     else if(cancelar){
                        estado=OPCION_HORA;}
                     else if(sentido==1){
                        //aumento hora
                        if(++i==4)
                           i=0;
                        strcpy(hora,arregloHoras[i]);}
                     else if(sentido==2){
                        //Disminuyo hora
                        if(--i==255)
                           i=3;
                        strcpy(hora,arregloHoras[i]);
                     }
                     
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
                     if(boton)
                        estado=DISPENSANDO;
                     else if(cancelar)
                        estado=DAR_COMIDA;
                     break;
      case DISPENSANDO:
         //Habria que ver como hacer para que no haga nada hasta que deje de dispensar
         if(cancelar)
            estado=PRINCIPAL;
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

        case DISPENSANDO:
            lcdGoToXY(1,1);
            lcdSendStringRaw("Dispensando...  ");
            lcdGoToXY(1,2);
            lcdSendStringRaw("Espere por favor");
            break;

        default:
            lcdGoToXY(1, 1);
            lcdSendStringRaw("Error           ");
            lcdGoToXY(1, 2);
            lcdSendStringRaw("Espere por favor");
            break;
    }
   
}