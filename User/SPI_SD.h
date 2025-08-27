/********************************** (C) COPYRIGHT *******************************
 * File Name          : SPI_SD.h
 * Autor              : Lennox
 * Version            : V1.0.0
 * Date               : 2025/08/25
 * Description        : SPI SD (SPI mode) driver for CH32V20x
 *******************************************************************************/
#ifndef __SPI_SD_H
#define __SPI_SD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ch32v20x.h"
#include <ch32v20x_spi.h>
#include <stdint.h>

/* Pinout SPI1:
   CS   -> PA4
   SCK  -> PA5
   MISO -> PA6
   MOSI -> PA7
*/
#define SD_CS_LOW()     (GPIOA->BCR  = GPIO_Pin_4)
#define SD_CS_HIGH()    (GPIOA->BSHR = GPIO_Pin_4)

/* API */
void     SD_Port_Init(void);
/* SD_Init: init slow speed SPI ~187.5 kHz (48 MHz / 256), if OK switch SPI to high speed (default /4 = 12 MHz) */
int      SD_Init(uint32_t* sector_count, uint16_t* sector_size);
int      SD_ReadBlocks(uint32_t lba, uint8_t* buf, uint32_t count);
int      SD_WriteBlocks(uint32_t lba, const uint8_t* buf, uint32_t count);
uint32_t SD_GetSectorCount(void);
uint16_t SD_GetSectorSize(void);

/* Manual SPI speed setting after init */
void     SD_SPI_SetSpeed(uint16_t prescaler);

#ifdef __cplusplus
}
#endif

#endif /* __SPI_SD_H */