#include "esp.h"

uint8_t index = 0;
char receivedByte;

void espInit(uint32_t transmissionSpeed)
{
    uartConfig(UART_232, transmissionSpeed);
}

void espSendData(char *hora, uint8_t gramosAServir, int32_t pesoPlato, int32_t pesoTarro)
{
   char buffer[100];
   int n = sprintf(buffer, "%03ld,%03ld,%s,%03d*", pesoPlato, pesoTarro, hora, gramosAServir);

    if (n < 0) {
       printf("Cantidad de caracteres escritos: %d\n", n);
        uartWriteString(UART_USB, "andando mal");
        return;
    }
   uartWriteString(UART_232, buffer);
}

uint8_t espReceiveData(char *buffer, int bufferSize)
{
   
    if (uartReadByte(UART_232, &receivedByte))
    {
       uartWriteString(UART_USB, "leyendo");
        if (index < bufferSize - 1)
        {
            buffer[index++] = receivedByte;
            if (receivedByte == '*')
            {
                buffer[index - 1] = '\0';
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
