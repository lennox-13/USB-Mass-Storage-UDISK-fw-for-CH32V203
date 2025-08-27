/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * File Name          : Lennox
 * Version            : V1.0.0
 * Date               : 2025/08/25
 * Description        : UDISK SPI SD Card reader
*********************************************************************************
*/
#include <SW_UDISK.h>
#include "debug.h"
#include <usb_lib.h>
#include "SPI_SD.h"

extern volatile uint32_t  Udisk_Capability;
extern volatile uint8_t   Udisk_Status;

int main(void){

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    SystemCoreClockUpdate();
    Delay_Init();
    USART_Printf_Init(115200);
    printf("SystemClk:%d\r\n", SystemCoreClock);

    printf("USBD UDISK SPI SD Card Reader\r\nStorage Medium: SPI SD CARD\r\n");

    SD_Port_Init();

    uint32_t sector_count = 0;
    uint16_t sector_size  = 0;
    if (SD_Init(&sector_count, &sector_size) != 0) {
        printf("SD init failed.\r\n");
        while(1);
    }

     /* Print SD capacity in MB (MiB) */
    uint32_t sectors_per_mib = (1024U * 1024U) / sector_size;  
    uint32_t capacity_mib    = (sectors_per_mib ? (sector_count / sectors_per_mib) : 0);
    printf("SD Capacity: %lu MB\r\n", (unsigned long)capacity_mib);

    /* UDISK capacity: 512B sector */
    Udisk_Capability = sector_count;
    Udisk_Status |= DEF_UDISK_EN_FLAG;

    /* USBD init */
    Set_USBConfig();
    USB_Init();
    USB_Interrupts_Config();

    while(1) { ; }
}

