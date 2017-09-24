#include <Arduino.h>
#include "A7105.h"
#include "flysky_A2.h"
#include <EEPROM.h>

uint8_t payload[PACKET_SIZE];
uint16_t rcData[FLYSKY_CHANNEL_COUNT];
rxConfig_t rxConfig;
rxRuntimeConfig_t rxRuntimeConfig;

void setup() {
    Serial.begin(9600);
    while (!Serial) {}

    EEPROM.get(0, rxConfig);
    FlySkyA2Init(&rxConfig, &rxRuntimeConfig);
    Serial.println("Starting...");
}

void loop() {

    tele_meas1 = millis()/2000;
    tele_meas2 = 150;
    rx_spi_received_e result = FlySkyA2DataReceived (payload);

    if (result == RX_SPI_RECEIVED_DATA)
    {
        FlySkyA2SetRcDataFromPayload (rcData, payload);
    }
    else if (result == RX_SPI_RECEIVED_BIND)
    {
        Serial.println("Saving eeprom");
        EEPROM.put(0, rxConfig);
    }

    if (Serial.available() > 0) {
        Serial.read();
    }
}
