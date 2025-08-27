# USB Mass Storage (UDISK) firmware for CH32V203

A minimal USB Mass Storage (UDISK) firmware for the WCH CH32V203 that exposes an SPI‑connected SD card as a USB flash drive.

## What it does
- Initializes SPI1, detects SDHC/SDSC, and computes the capacity from the CSD.
- Implements MSC BOT SCSI: INQUIRY, READ CAPACITY(10), READ(10), WRITE(10), and MODE SENSE(6).
- Streams 512‑byte sectors between the USB endpoints and the SD card.
- Prints the SD capacity on UART1 at boot (115200 8N1).

## Hardware and pinout
SPI1 pins:
- PA4 = CS
- PA5 = SCK
- PA6 = MISO
- PA7 = MOSI

## Usage
1. Flash the firmware.
2. Insert an SD card formatted as FAT32.
3. Connect the board to a computer via the USB device port.
4. A removable drive should appear. On UART1, you should see a line like: `SD Capacity: 971 MB`.

## Tested hardware
Tested on the WCH CH32V203 EVT board.

Connect the board’s USB device port (Type‑A on the left side) to a PC.

<p align="center">
  <img src="EVT board.jpg" alt="WCH CH32V203 EVT board used for testing" width="480">
</p>
