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

// Realiza la tara del HX711
void HX711_Tare(int8_t muestras);

// Calibra el HX711
int32_t HX711_Calibrate(int32_t peso_conocido)

#endif // HX711_H