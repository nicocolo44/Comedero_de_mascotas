#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include "sapi.h"
#include <stdbool.h>
#include "hx711_plato.h"
#include "buzzer.h"
#include "motor.h"
#include "eepromUtil.h"
#include "boton.h"
#include "mef.h"



// Dar comida
void dar_comida(void);

void procesarRespuesta(char *data);

void inicializarRtc();
#endif // UTLIS_H