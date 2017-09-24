#ifndef _RX_SPI_H_
#define _RX_SPI_H_

#include <stdint.h>
#include <Arduino.h>

#define GIO_GET()   (digitalRead(GIOSTATUS))

#define GIOSTATUS 9

//MOSI
#define DATAOUT 11
//MISO
#define DATAIN  12
//sck
#define SPICLOCK  13
//ss
#define SLAVESELECT 10


void spiInit();
uint8_t spiTransferByte (uint8_t data);
uint8_t spiWriteByte (uint8_t data);
uint8_t spiWriteCommand (uint8_t command, uint8_t data);
uint8_t spiWriteCommandMulti (uint8_t command, const uint8_t *data, uint8_t length);
uint8_t spiReadCommand (uint8_t command, uint8_t commandData);
uint8_t spiReadCommandMulti (uint8_t command, uint8_t commandData, uint8_t *data, uint8_t length);

#endif // _RX_SPI_H_
