#ifndef BUZZER_H
#define BUZZER_H

#include <stdint.h>
#include "sapi.h"

// Inicializa el buzzer con el pin especificado y lo prende
void Buzzer_Init(uint8_t pin);

// Prende el buzzer
void Buzzer_On(void);

// Apaga el buzzer
void Buzzer_Off(void);

#endif /* BUZZER_H */

