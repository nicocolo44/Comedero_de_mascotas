#ifndef HX711_H
#define HX711_H

#include <stdint.h>
#include <stdbool.h>

// Inicializa el HX711 con los pines SCK y DOUT
void HX711_Init(uint8_t sck_pin, uint8_t dout_pin);

// Lee datos de 24 bits del HX711
int8_t HX711_Read(int32_t* data);

// Obtiene el peso calculado
float HX711_GetWeight(void);

#endif // HX711_H