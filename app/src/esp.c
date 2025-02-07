#include "esp.h"

uint8_t index = 0;
char receivedByte;

void espInit(uint32_t transmissionSpeed)
{
    uartConfig(UART_232, transmissionSpeed);
}

void espSendData(int32_t pesoPlato, int32_t pesoTarro)
{
   char buffer[100];
   int n = sprintf(buffer, "0,%04ld,%04ld*", pesoPlato, pesoTarro);

    if (n < 0) {
       printf("Cantidad de caracteres escritos: %d\n", n);
        uartWriteString(UART_USB, "andando mal");
        return;
    }
   uartWriteString(UART_232, buffer);
}

void espSendHora(char* hora){
   uartWriteString(UART_USB, "mandando hora");
   char buffer[100];
   int n = sprintf(buffer, "1,%s*", hora);

    if (n < 0) {
        uartWriteString(UART_USB, "andando mal");
        return;
    }
   uartWriteString(UART_232, buffer);
    uartWriteString(UART_USB, buffer);
    
}

void espSendGramosAServir(int8_t gramosAServir){
   uartWriteString(UART_USB, "Mandando gramos");
   char buffer[100];
   int n = sprintf(buffer, "2,%d*", gramosAServir);

    if (n < 0) {
        uartWriteString(UART_USB, "andando mal");
        return;
    }
   uartWriteString(UART_232, buffer);
    uartWriteString(UART_USB, buffer);
}

uint8_t espReceiveData(char *buffer, int bufferSize)
{
   
    if (uartReadByte(UART_232, &receivedByte))
    {
        if (index < bufferSize - 1)
        {
            buffer[index++] = receivedByte;
            if (receivedByte == '*')
            {
                buffer[index - 1] = '\0';
               uartWriteString(UART_USB, buffer);
                return true;
            }
        }
        else
        {
            buffer[index] = '\0';
            return true;
        }
    }
    return false;
}
