/********************************** (C) COPYRIGHT *******************************
 * File Name          : SPI_SD.c
 * Autor              : Lennox
 * Version            : V1.0.0
 * Date               : 2025/08/25
 * Description        : SPI SD (SPI mode) driver for CH32V20x
 *******************************************************************************/
#include "SPI_SD.h"
#include <debug.h>

/* SD SPI CMDs */
#define SD_CMD0     0x40  /* GO_IDLE_STATE */
#define SD_CMD1     0x41  /* SEND_OP_COND (MMC) */
#define SD_CMD8     0x48  /* SEND_IF_COND */
#define SD_CMD9     0x49  /* SEND_CSD */
#define SD_CMD12    0x4C  /* STOP_TRANSMISSION */
#define SD_CMD16    0x50  /* SET_BLOCKLEN */
#define SD_CMD17    0x51  /* READ_SINGLE_BLOCK */
#define SD_CMD24    0x58  /* WRITE_SINGLE_BLOCK */
#define SD_CMD55    0x77  /* APP_CMD */
#define SD_CMD58    0x7A  /* READ_OCR */
#define SD_ACMD41   0x69  /* SD_SEND_OP_COND (ACMD41) */

#define TOKEN_DATA_START 0xFE

/* Timeouts */
#define SD_INIT_TIMEOUT     100000UL
#define SD_RW_TIMEOUT       100000UL

/* Internals */
static uint8_t  s_is_sdhc = 0;        /* 1 = SDHC/SDXC (LBA), 0 = SDSC (byte) */
static uint32_t s_sector_count = 0;
static uint16_t s_sector_size  = 512; /* SD = 512 B */

static void SD_SPI_ReInit(uint16_t prescaler)
{
    SPI_InitTypeDef  SPI_InitStructure = {0};
    SPI_Cmd(SPI1, DISABLE);

    /* SD SPI Mode 0: CPOL_Low, CPHA_1Edge */
    SPI_InitStructure.SPI_Direction         = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode              = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize          = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL              = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA              = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS               = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = prescaler;
    SPI_InitStructure.SPI_FirstBit          = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial     = 7;

    SPI_Init(SPI1, &SPI_InitStructure);
    SPI_Cmd(SPI1, ENABLE);
}

void SD_SPI_SetSpeed(uint16_t prescaler)
{
    SD_SPI_ReInit(prescaler);
}

void SD_Port_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1 , ENABLE);

    /* CS (PA4) */
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    SD_CS_HIGH();

    /* SCK (PA5), MOSI (PA7) */
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* MISO (PA6) */
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Slow speed for SD Card init: 48 MHz / 256 ¡Ö 187.5 kHz */
    SD_SPI_ReInit(SPI_BaudRatePrescaler_256);
}

static uint8_t SD_SPI_RW(uint8_t v)
{
    while((SPI1->STATR & SPI_I2S_FLAG_TXE) == 0);
    SPI1->DATAR = v;
    while((SPI1->STATR & SPI_I2S_FLAG_RXNE) == 0);
    return (uint8_t)SPI1->DATAR;
}

static void SD_SPI_ClockDummy(uint16_t bytes)
{
    for(uint16_t i=0;i<bytes;i++){ SD_SPI_RW(0xFF); }
}

static uint8_t SD_SendCmd(uint8_t cmd, uint32_t arg, uint8_t crc)
{
    uint8_t r1;
    uint16_t retry = 0xFFFF;

    SD_CS_HIGH();
    SD_SPI_RW(0xFF);
    SD_CS_LOW();
    SD_SPI_RW(0xFF);

    SD_SPI_RW(cmd);
    SD_SPI_RW((uint8_t)(arg >> 24));
    SD_SPI_RW((uint8_t)(arg >> 16));
    SD_SPI_RW((uint8_t)(arg >> 8));
    SD_SPI_RW((uint8_t)(arg));
    SD_SPI_RW(crc);

    do {
        r1 = SD_SPI_RW(0xFF);
    } while ((r1 & 0x80) && --retry);

    return r1;
}

static uint8_t SD_WaitReady(uint32_t to)
{
    uint8_t d;
    do {
        d = SD_SPI_RW(0xFF);
        if (d == 0xFF) return 1;
    } while (to--);
    return 0;
}

static int SD_ReadDataBlock(uint8_t* buf, uint16_t len)
{
    uint32_t timeout = SD_RW_TIMEOUT;
    uint8_t token;

    do {
        token = SD_SPI_RW(0xFF);
    } while ((token == 0xFF) && --timeout);

    if (token != TOKEN_DATA_START) return -1;

    for(uint16_t i=0;i<len;i++) buf[i] = SD_SPI_RW(0xFF);
    SD_SPI_RW(0xFF); SD_SPI_RW(0xFF); /* CRC */
    return 0;
}

static int SD_WriteDataBlock(const uint8_t* buf, uint8_t token)
{
    if (!SD_WaitReady(SD_RW_TIMEOUT)) return -1;

    SD_SPI_RW(token);
    for(uint16_t i=0;i<512;i++) SD_SPI_RW(buf[i]);
    SD_SPI_RW(0xFF); SD_SPI_RW(0xFF); /* CRC */

    uint8_t resp = SD_SPI_RW(0xFF);
    if ((resp & 0x1F) != 0x05) return -2;

    if (!SD_WaitReady(SD_RW_TIMEOUT)) return -3;
    return 0;
}

static int SD_ReadCSD(uint8_t csd[16])
{
    uint8_t r1 = SD_SendCmd(SD_CMD9, 0, 0xFF);
    if (r1 != 0x00) { SD_CS_HIGH(); return -1; }
    int rc = SD_ReadDataBlock(csd, 16);
    SD_CS_HIGH(); SD_SPI_RW(0xFF);
    return rc;
}

static void SD_ComputeCapacityFromCSD(const uint8_t csd[16])
{
    uint8_t csd_structure = (csd[0] >> 6) & 0x03;

    if (csd_structure == 1) {
        /* SDHC/SDXC */
        uint32_t c_size = ((uint32_t)(csd[7] & 0x3F) << 16) | ((uint32_t)csd[8] << 8) | csd[9];
        s_sector_count = (c_size + 1) * 1024UL;
        s_is_sdhc = 1;
        s_sector_size = 512;
    } else {
        /* SDSC */
        uint8_t  read_bl_len = csd[5] & 0x0F;
        uint32_t c_size      = ((uint32_t)(csd[6] & 0x03) << 10) | ((uint32_t)csd[7] << 2) | ((uint32_t)(csd[8] >> 6) & 0x03);
        uint8_t  c_size_mult = ((csd[9] & 0x03) << 1) | ((uint8_t)(csd[10] >> 7) & 0x01);

        uint32_t block_len      = 1UL << read_bl_len;
        uint32_t mult           = 1UL << (c_size_mult + 2);
        uint32_t blocknr        = (c_size + 1) * mult;
        uint32_t capacity_bytes = blocknr * block_len;

        s_sector_count = capacity_bytes / 512UL;
        s_is_sdhc = 0;
        s_sector_size = 512;
    }
}

int SD_Init(uint32_t* sector_count, uint16_t* sector_size)
{
    uint8_t r1;
    uint32_t to;

    /* >= 74 SPI clock s CS=HIGH, MOSI=HIGH */
    SD_CS_HIGH();
    SD_SPI_ClockDummy(10);

    /* CMD0 -> IDLE */
    r1 = SD_SendCmd(SD_CMD0, 0, 0x95);
    if (r1 != 0x01) { SD_CS_HIGH(); return -1; }

    /* CMD8: read version */
    r1 = SD_SendCmd(SD_CMD8, 0x000001AA, 0x87);
    uint8_t v2 = 0;
    if (r1 == 0x01) {
        uint8_t r7[4] = { SD_SPI_RW(0xFF), SD_SPI_RW(0xFF), SD_SPI_RW(0xFF), SD_SPI_RW(0xFF) };
        if (r7[2] == 0x01 && r7[3] == 0xAA) v2 = 1;
    }
    SD_CS_HIGH(); SD_SPI_RW(0xFF);

    /* ACMD41 s HCS for v2, else CMD1 */
    to = SD_INIT_TIMEOUT;
    if (v2) {
        do {
            r1 = SD_SendCmd(SD_CMD55, 0, 0xFF);
            SD_CS_HIGH(); SD_SPI_RW(0xFF);
            r1 = SD_SendCmd(SD_ACMD41, 0x40000000, 0xFF); /* HCS */
            SD_CS_HIGH(); SD_SPI_RW(0xFF);
        } while (r1 != 0x00 && --to);
        if (!to) return -2;

        /* CMD58: OCR (SDHC flag) */
        r1 = SD_SendCmd(SD_CMD58, 0, 0xFF);
        if (r1 != 0x00) { SD_CS_HIGH(); return -3; }
        uint8_t ocr[4] = { SD_SPI_RW(0xFF), SD_SPI_RW(0xFF), SD_SPI_RW(0xFF), SD_SPI_RW(0xFF) };
        SD_CS_HIGH(); SD_SPI_RW(0xFF);
        s_is_sdhc = (ocr[0] & 0x40) ? 1 : 0;
    } else {
        do {
            r1 = SD_SendCmd(SD_CMD1, 0, 0xFF);
            SD_CS_HIGH(); SD_SPI_RW(0xFF);
        } while (r1 != 0x00 && --to);
        if (!to) return -4;
        s_is_sdhc = 0;
    }

    /* SDSC: set 512B block */
    if (!s_is_sdhc) {
        r1 = SD_SendCmd(SD_CMD16, 512, 0xFF);
        SD_CS_HIGH(); SD_SPI_RW(0xFF);
        if (r1 != 0x00) return -5;
    }

    /* CSD -> capacity */
    uint8_t csd[16];
    if (SD_ReadCSD(csd) != 0) return -6;
    SD_ComputeCapacityFromCSD(csd);

    /* High speed SPI after init: 48 MHz / 4 = 12 MHz */
    SD_SPI_SetSpeed(SPI_BaudRatePrescaler_4);

    if (sector_count) *sector_count = s_sector_count;
    if (sector_size)  *sector_size  = s_sector_size;
    return 0;
}

int SD_ReadBlocks(uint32_t lba, uint8_t* buf, uint32_t count)
{
    if (count == 0) return 0;

    while (count--) {
        uint32_t addr = s_is_sdhc ? lba : (lba * 512UL);
        uint8_t r1 = SD_SendCmd(SD_CMD17, addr, 0xFF);
        if (r1 != 0x00) { SD_CS_HIGH(); return -1; }

        if (SD_ReadDataBlock(buf, 512) != 0) { SD_CS_HIGH(); return -2; }
        SD_CS_HIGH(); SD_SPI_RW(0xFF);

        buf += 512;
        lba++;
    }
    return 0;
}

int SD_WriteBlocks(uint32_t lba, const uint8_t* buf, uint32_t count)
{
    if (count == 0) return 0;

    while (count--) {
        uint32_t addr = s_is_sdhc ? lba : (lba * 512UL);
        uint8_t r1 = SD_SendCmd(SD_CMD24, addr, 0xFF);
        if (r1 != 0x00) { SD_CS_HIGH(); return -1; }

        int rc = SD_WriteDataBlock(buf, TOKEN_DATA_START);
        SD_CS_HIGH(); SD_SPI_RW(0xFF);
        if (rc != 0) return -2;

        buf += 512;
        lba++;
    }
    return 0;
}

uint32_t SD_GetSectorCount(void) { return s_sector_count; }
uint16_t SD_GetSectorSize(void)  { return s_sector_size; }