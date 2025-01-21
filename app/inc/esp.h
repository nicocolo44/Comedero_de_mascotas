#ifndef ESP_H
#define ESP_H

#include <stdint.h>
#include "sapi.h"


void espInit(uint32_t transmissionSpeed);

void espSendData(char* data);

void espReceiveData(char* data);

#endif

