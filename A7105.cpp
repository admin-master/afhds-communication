#include "A7105.h"

#include "avr_spi.h"

void A7105_Init (void)
{
    spiInit();
}

void A7105_SoftReset (void)
{
    spiWriteCommand (A7105_00_MODE, 0x00);
}

void A7105_SetupSPI4 (void)
{
    spiWriteCommand(0x0c, 6<<2|1);
}

uint8_t A7105_ReadReg (a7105_reg_t reg)
{
	const auto WRITE_COMMAND = 0x40;
    return spiReadCommand( reg | WRITE_COMMAND, 0xFF);
}

void A7105_WriteReg (a7105_reg_t reg, uint8_t data)
{
    spiWriteCommand (reg, data);
}


void A7105_Strobe (a7105_state_t st)
{
    spiWriteByte (st);
}


void A7105_WriteID(uint32_t id)
{
    uint8_t data[4];
    data[0] = (id >> 24) & 0xFF;
    data[1] = (id >> 16) & 0xFF;
    data[2] = (id >> 8) & 0xFF;
    data[3] = (id >> 0) & 0xFF;
    spiWriteCommandMulti (A7105_06_ID_DATA, &data[0], sizeof(data));
}


uint32_t A7105_ReadID (void)
{
    uint8_t data[4];
    spiReadCommandMulti ( A7105_06_ID_DATA | 0x40, 0xFF, &data[0], sizeof(data));
    return  (data[0]*0xFF*0xFF*0xFF | data[1]*0xFF*0xFF  | data[2]*0xFF | data[3] << 0);
}


void A7105_ReadFIFO (uint8_t *data, uint8_t num)
{
    if(num > 64) num = 64;
    A7105_Strobe(A7105_RST_RDPTR);	// reset read pointer
    spiReadCommandMulti (A7105_05_FIFO_DATA | 0x40, 0xFF, data, num);
}


void A7105_WriteFIFO (uint8_t *data, uint8_t num)
{
    if(num > 64) num = 64;
    A7105_Strobe(A7105_RST_WRPTR);	// reset write pointer
    spiWriteCommandMulti(A7105_05_FIFO_DATA, data, num);
}

uint8_t A7105_RX_TX_Finished (void)
{
    return (GIO_GET() == 0) ? 0xFF : 0x00;
}
