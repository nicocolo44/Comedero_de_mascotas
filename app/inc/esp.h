#ifndef ESP_H
#define ESP_H

#include <stdint.h>
#include "sapi.h"
#include "sapi_uart.h"

void espInit(uint32_t transmissionSpeed);

void espSendData(int32_t pesoPlato, int32_t pesoTarro);

void espSendHora(char* hora);

void espSendGramosAServir(int8_t gramosAServir);

uint8_t espReceiveData(char *buffer, int bufferSize);

#endif
