#ifndef _BSP_H_
#define _BSP_H_

#include <stdint.h>
#include <Arduino.h>

uint8_t CheckJumper()
{
    pinMode(2, INPUT_PULLUP);
    return digitalRead(2);
}

uint32_t GetCPUID()
{
    // generate some number here
    return 0x0112;
}



#endif // _BSP_H_
