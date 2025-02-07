#ifndef MEF_H
#define MEF_H

#include <stdint.h>
#include "sapi.h"
#include "utils.h"
#include <string.h>
#include "eepromUtil.h"
#include "hx711_tarro.h"
typedef enum {PRINCIPAL,OPCION_COMIDA,ELEGIR_CANTIDAD_COMIDA,OPCION_HORA,DEFINIR_HORA,DAR_COMIDA,DAR_COMIDA2,DISPENSANDO}estadosMef;

void mefInit();

void mefUpdate(uint8_t sentido ,uint8_t boton ,uint8_t cancelar);

void mefDarComida();

#endif