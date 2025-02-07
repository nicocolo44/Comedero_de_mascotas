#include "mef.h"
#include <string.h>
#include "eepromUtil.h"
#include "esp.h"

static estadosMef estado;
static uint8_t gramos;
static uint8_t hora[6];
static uint8_t i=0;
const uint8_t* arregloHoras[] = {
    "00:00", "00:30", "01:00", "01:30", "02:00", "02:30",
    "03:00", "03:30", "04:00", "04:30", "05:00", "05:30",
    "06:00", "06:30", "07:00", "07:30", "08:00", "08:30",
    "09:00", "09:30", "10:00", "10:30", "11:00", "11:30",
    "12:00", "12:30", "13:00", "13:30", "14:00", "14:30",
    "15:00", "15:30", "16:00", "16:30", "17:00", "17:30",
    "18:00", "18:30", "19:00", "19:30", "20:00", "20:30",
    "21:00", "21:30", "22:00", "22:30", "23:00", "23:30"
};
void mefInit(){
   estado = PRINCIPAL;
   lcdInit(16,2,5,8);
   eepromInit();
}

void mefUpdate(uint8_t sentido,uint8_t boton ,uint8_t cancelar){
   rtc_t rtc;
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
      int32_t data;
      uint8_t bufferG[17];
      uint8_t bufferH[17];
        case PRINCIPAL:
            rtcRead(&rtc);
            sprintf(bufferH, "%02d:%02d           ", rtc.hour, rtc.min);
            HX711_tarro_Read(&data);
            sprintf(bufferG, "%d gramos disp   ", (uint8_t)HX711_tarro_GetWeight(data)); // NOSE SI SE PUEDE CASTEAR ASI xd
            lcdGoToXY(1, 1);
            lcdSendStringRaw(bufferH); // Hora en formato HH:MM
            lcdGoToXY(1, 2);
            lcdSendStringRaw(bufferG);
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
            sprintf(bufferG,"%d gramos        ",gramos);
            lcdSendStringRaw(bufferG);
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
               if(++i==48)
                  i=0;
               strcpy(hora,arregloHoras[i]);
               }
            else if(sentido==2){
               //Disminuyo hora
               if(--i==255)
                  i=47;
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

void mefDarComida(){
   estado = DAR_COMIDA2;
   mefUpdate(0,1,0);
}
