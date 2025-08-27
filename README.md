# USB-Mass-Storage-UDISK-fw-for-CH32V203
A minimal USB Mass Storage (UDISK) firmware for WCH CH32V203 that exposes an SPI-connected SD card as a USB flash drive.

It initializes SPI1, detects SDHC/SDSC, computes capacity from CSD, and implements MSC BOT SCSI commands (INQUIRY, READ CAPACITY, READ10/WRITE10, MODE SENSE). 
512-byte sectors are streamed between USB endpoints and the SD card; the SD capacity is printed on UART at boot. 
SPI1 pinout: 
PA4=CS, 
PA5=SCK, 
PA6=MISO, 
PA7=MOSI. 
Flash the firmware, connect USB to a PC, and the SD card appears as a removable drive :)
