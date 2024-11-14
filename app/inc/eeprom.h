#include "eeprom_18xx_43xx.h"
#include "chip.h"
/**
 * @brief       Write a byte in EEPROM memory
 * @param       addr : Address relative to eeprom start (0x0000 to 0x3F7F)
 * @param       value : Byte to be written in specified address
 * @return      0: OK, -1: invalid address
 */
int32_t Board_EEPROM_writeByte(uint32_t addr,uint8_t value);

/**
 * @brief       Read a byte from EEPROM memory
 * @param       addr : Address relative to eeprom start (0x0000 to 0x3F7F)
 * @return      byte value read or -1 if address is invalid
 */
int32_t Board_EEPROM_readByte(uint32_t addr);


void Board_EEPROM_init(void);
/**
 * @brief       Initializes SPI Module in Master mode
 * @return      void
 */