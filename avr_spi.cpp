#include "avr_spi.h"

#include "SPI.h"

#define CS_ACTIVE() do { digitalWrite(SLAVESELECT,LOW);  } while(0)
#define CS_INACTIVE() do { digitalWrite(SLAVESELECT,HIGH); } while(0)


void spiInit ()
{
    pinMode(DATAOUT, OUTPUT);
    pinMode(DATAIN, INPUT);
    pinMode(GIOSTATUS, INPUT);
    pinMode(SPICLOCK,OUTPUT);
    pinMode(SLAVESELECT,OUTPUT);
    digitalWrite(SLAVESELECT,HIGH);
    SPI.beginTransaction({1000000, MSBFIRST, SPI_MODE0});
    SPI.begin();
}

uint8_t spiTransferByte(uint8_t data)
{
    return SPI.transfer(data);
}


uint8_t spiWriteByte(uint8_t data)
{
    CS_ACTIVE();
    const uint8_t ret = spiTransferByte(data);
    CS_INACTIVE();
    return ret;
}


uint8_t spiWriteCommand(uint8_t command, uint8_t data)
{
    CS_ACTIVE();
    const uint8_t ret = spiTransferByte(command);
    spiTransferByte(data);
    CS_INACTIVE();
    return ret;
}

uint8_t spiWriteCommandMulti(uint8_t command, const uint8_t *data, uint8_t length)
{
    CS_ACTIVE();
    const uint8_t ret = spiTransferByte(command);
    for (auto i = 0; i < length; ++i) {
        spiTransferByte(data[i]);
    }
    CS_INACTIVE();
    return ret;
}

uint8_t spiReadCommand(uint8_t command, uint8_t data)
{
    CS_ACTIVE();
    spiTransferByte(command);
    const uint8_t ret = spiTransferByte(data);
    CS_INACTIVE();
    return ret;
}
uint8_t spiReadCommandMulti(uint8_t command, uint8_t commandData, uint8_t *data, uint8_t length)
{
    CS_ACTIVE();
    const uint8_t ret = spiTransferByte(command);
    for (auto i = 0; i < length; ++i) {
        data[i] = spiTransferByte(commandData);
    }
    CS_INACTIVE();
    return ret;
}
