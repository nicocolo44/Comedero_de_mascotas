#ifndef EEPROMUTIL_H
#define EEPROMUTIL_H

#include "eeprom.h"

#define DIR_GRAMOS 0x0
#define DIR_HORA 0x1


// Declaración de funciones
void eepromLeerGramos(uint8_t *);
void eepromLeerHora(uint8_t *);

#endif  // EEPROMUTIL_H
