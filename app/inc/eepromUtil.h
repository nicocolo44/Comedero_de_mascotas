#ifndef EEPROMUTIL_H
#define EEPROMUTIL_H

#include "eeprom.h"

#define DIR_GRAMOS 0x00
#define DIR_HORA 0x10


// Declaración de funciones
void eepromInit();
uint8_t eepromReadGramos();
void eepromWriteGramos(uint8_t);
void eepromReadHora(uint8_t *);
void eepromWriteHora(uint8_t*);

#endif  // EEPROMUTIL_H
