// Gyroscope

#include <xc.h>
#include <assert.h>
#include <stdbool.h>
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/examples/i2c_master_example.h"
#include "sht40.h"

#define SHT40_ADDR    0x44

uint8_t  writeBuffer[3] = {0x00, 0x00, 0x00};                           // definiert "writeBuffer"
uint8_t  readBuffer[10] = {0x00, 0x00};                                 // definiert "readBuffer" 

void SHT40_Init(void){                                                  // "SHT40_Init"
    I2C_Write1ByteRegister(SHT40_ADDR, 0x00, 0xFD);                     // schreibt "0xFD" in "0x00"     
    __delay_ms(10);                                                     // warte 10ms
}                                                                       // 

void SHT40_Read(void){                                                  // "SHT40_Read"
    uint8_t regist = 0xFD;                                              // definiert "regist"

    I2C_WriteNBytes(SHT40_ADDR, &regist, 1);                            // schreibt "regist" an den Sensor
    __delay_ms(10);                                                     // warte 10ms
    I2C_ReadNBytes(SHT40_ADDR, &readBuffer, 6);                         // liest 6 Byte vom Sensor
}                                                                       // 

float SHT40_temp_GetValue(void){                                        // "SHT40_temp_GetValue"  
    float    tempDataAnz;                                               // definiert "tempDataAnz"
    uint16_t buffer;                                                    // definiert "buffer"
    
    SHT40_Read();                                                       // ruft "SHT40_Read" auf
    buffer = readBuffer[0] * 256 + readBuffer[1];                       // 
    tempDataAnz = buffer;                                               // schreibt inhalt von "buffer" in "tempDataAnz"
    tempDataAnz = -45 + 175 * tempDataAnz/65535;                        // 
    
    return tempDataAnz;                                                 // gibt "tempDataAnz" zurück     
}                                                                       // 

float SHT40_humy_GetValue(void){                                        // "SHT40_humy_GetValue" 
    float    pressDataAnz;                                              // definiert "pressDataAnz"
    uint16_t buffer;                                                    // definiert "buffer"
    
    SHT40_Read();                                                       // ruft "SHT40_Read" auf
    buffer = readBuffer[3] * 256 + readBuffer[4];                       // 
    pressDataAnz = buffer;                                              // schreibt inhalt von "buffer" in "pressDataAnz"
    pressDataAnz = -6 + 125 * pressDataAnz/65535;                       // 
    
    if(pressDataAnz > 100){                                             // wenn "pressDataAnz" größer als "100" ist
        pressDataAnz = 100;                                             // "pressDataAnz" gleich 100
    }                                                                   // 
    if (pressDataAnz < 0){                                              // wenn "pressDataAnz" kleiner als "100" ist
        pressDataAnz = 0;                                               // "pressDataAnz" gleich 0
    }                                                                   // 
    
    return pressDataAnz;                                                // gibt "pressDataAnz" zurück     
}                                                                       // 
