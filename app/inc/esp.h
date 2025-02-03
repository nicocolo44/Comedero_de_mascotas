#ifndef ESP_H
#define ESP_H

#include <stdint.h>
#include "sapi.h"
#include "sapi_uart.h"

void espInit(uint32_t transmissionSpeed);

void espSendData(char *hora, uint8_t gramosAServir, int32_t pesoPlato, int32_t pesoTarro);

uint8_t espReceiveData(char *buffer, int bufferSize);

#endif
