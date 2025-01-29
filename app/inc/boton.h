#ifndef BOTON_H
#define BOTON_H

#include <stdint.h>
#include "sapi.h"

void botonInit(uint8_t,uint8_t); // pin y tiempo de anti rebote

uint8_t botonRead();

#endif