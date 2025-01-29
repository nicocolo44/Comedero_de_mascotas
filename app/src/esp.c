#include "esp.h"


void espInit(uint32_t transmissionSpeed){
    uartConfig(UART_232, transmissionSpeed);
}

void espSendData(char* data){
    uartWriteString(UART_232, data);
}


void espReceiveData(char* data){
    // Esta función lee hasta 100 caracteres de la UART_232 y los almacena en 'data'
    uartReadString(UART_232, data, 100);
}
