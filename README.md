# XtsGamingSystem
Cross Platform Gaming System

(work in progress...)

### on GG#2

**not working**

- NO Keyb USB mounted
- will never be able to have RX2/ttyS3 because of SPI/CS

**working**

- screen
- LED
- all btns
- Wifi (.1.46)
- USB eth (pins wired)

**Ideas**  

- use a 328P 3.3v 8MHz to drive SX1509 (0x3E on I2c) ?

  - then plug it in Serial to Arietta

  - could easily plug it onto RX1-TX1/ttyS2

    - Serial0 will not have kernel timeout control (no failures messages)
    - **Serial0 is used in /etc/inttab & gpio.dts** for kernel dbug ??? (@ 115200 ProMini 3.3v can't do that)
    - will have to wire DFPlayer to a tty too ! (ttyS2 / Serial1)
      - 328p as I2c master + SoftwareSerial to drive DFPlayer & take its place on ttyS2
        - according to DFSoundCard.cpp can be TXOnly (or use TX2/ttyS3 ?)
        - CHECK that opening ttyS3 doesn't makes Screen CS hangs !!!!!!

    - have to thing to IPC Vs port data consuming
    - when lua runs a native : should kill lua + add a flag to restart it (save state ?)

