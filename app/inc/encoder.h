#ifndef ENCODER_H
#define ENCODER_H

#include <stdint.h>
#include "sapi.h"

void encoderInit(uint8_t,uint8_t,uint8_t,uint8_t);

uint8_t encoderRead(uint8_t*); //giro y boton


#endif