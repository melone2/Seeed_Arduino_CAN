// demo: Use RX0BF and RX1BF as digital outputs
// adlerweb, 2017-06-24
#include <SPI.h>
#include "mcp2515_can.h"
#include "mcp2518fd_can.h"

/*SAMD core*/
#ifdef ARDUINO_SAMD_VARIANT_COMPLIANCE
    #define SERIAL SerialUSB
#else
    #define SERIAL Serial
#endif


#define CAN_2515
// #define CAN_2518FD

// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10

// Set SPI CS Pin according to your hardware
// For Wio Terminal w/ MCP2518FD RPi Hat：
// Channel 0 SPI_CS Pin: BCM 8
// Channel 1 SPI_CS Pin: BCM 7
// Interupt Pin: BCM25
// *****************************************
// For Arduino MCP2515 Hat:
// SPI_CS Pin: D9

#define SPI_CS_PIN 9

#ifdef CAN_2518FD
mcp2518fd CAN(SPI_CS_PIN); // Set CS pin
#endif

#ifdef CAN_2515
mcp2515_can CAN(SPI_CS_PIN); // Set CS pin
#endif


void setup() {
    SERIAL.begin(115200);

#ifdef CAN_2518FD
    while (0 != CAN.begin((byte)CAN_500K_1M)) {            // init can bus : baudrate = 500k
#endif
#ifdef CAN_2515
    while (CAN_OK != CAN.begin(CAN_500KBPS)) {
#endif         // init can bus : baudrate = 500k
        SERIAL.println("CAN init failed, retry");
        delay(100);
    }
    SERIAL.println("CAN init ok");

#ifdef CAN_2518FD
    if (CAN.mcpPinMode(GPIO_PIN_0, GPIO_MODE_INT)) {
#else
    if (CAN.mcpPinMode(MCP_TX2RTS, MCP_PIN_IN)) {
#endif
        SERIAL.println("RX0BF is now an output");
    } else {
        SERIAL.println("Could not switch RX0BF");
    }

#ifdef CAN_2518FD
    if (CAN.mcpPinMode(GPIO_PIN_1, GPIO_MODE_INT)) {
#else
    if (CAN.mcpPinMode(MCP_TX2RTS, MCP_PIN_IN)) {
#endif
        SERIAL.println("RX1BF is now an output");
    } else {
        SERIAL.println("Could not switch RX1BF");
    }
}

void loop() {
    SERIAL.println("10");
#ifdef CAN_2518FD    
    CAN.mcpDigitalWrite(GPIO_PIN_0, GPIO_HIGH);
    CAN.mcpDigitalWrite(GPIO_PIN_1, GPIO_LOW);
#else
    CAN.mcpDigitalWrite(MCP_RX0BF, HIGH);
    CAN.mcpDigitalWrite(MCP_RX1BF, LOW);
#endif

    delay(500);
    SERIAL.println("01");
#ifdef CAN_2518FD
    CAN.mcpDigitalWrite(GPIO_PIN_0, GPIO_LOW);
    CAN.mcpDigitalWrite(GPIO_PIN_1, GPIO_HIGH);
#else
    CAN.mcpDigitalWrite(MCP_RX0BF, LOW);
    CAN.mcpDigitalWrite(MCP_RX1BF, HIGH);
#endif
    delay(500);
}

/*********************************************************************************************************
    END FILE
*********************************************************************************************************/
