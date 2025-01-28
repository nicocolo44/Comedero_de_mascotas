#ifndef HX711_PLATO_H
#define HX711_PLATO_H

#include <stdint.h>
#include "sapi.h"
#include <stdbool.h>

// Inicializa el HX711 con los pines SCK y DOUT
void HX711_plato_Init(uint8_t sck_pin, uint8_t dout_pin);

// Lee datos de 24 bits del HX711
int8_t HX711_plato_Read(int32_t* data);

// Obtiene el peso calculado
float HX711_plato_GetWeight(void);

// Realiza la tara del HX711
void HX711_plato_Tare(int8_t muestras);

// Calibra el HX711
int32_t HX711_plato_Calibrate(int32_t peso_conocido)

//funciones de debug
int32_t HX711_plato_GetValorBase(void);
int32_t HX711_plato_GetFactorConversion(void);


#endif // HX711_PLATO_H