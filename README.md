# General parameters of the Robomow RL-2000 (City 120) robot - user terminal communication
 * 0-5V levels between the PIC in the terminal and the H8S/2000 in the robot
 * 19200 baud 8n1 inverted (UART idles at low)
 * Checksum: sum all bytes then negate
 
 J105 pinout:
 RX1: 4
 TX1: 5
 RX0: 2
 TX0: 3
 GND: 8
 
# Terminal response packets
Terminal sends the following packets periodically (with varying -depending on the traffic from the robot- rate between 10-60ms). 
I never saw traffic on the TX and RX at the same time (the terminal and the robot seems to be handshaking on the bus).

```
* Idle:     0x23 0x00 0x18 0xC4
* Forward:  0x23 0x40 0x18 0x84
* Backward: 0x23 0x80 0x18 0x44
* Left:     0x23 0x10 0x18 0xB4
* Right:    0x23 0x20 0x18 0xA4
* Rabbit:   0x23 0x00 0x19 0xC3
* C:        0x23 0x08 0x18 0xBC
* Go:       0x23 0x80 0x18 0x44
* Stop:     0x23 0x00 0x1A 0xC2
* Factory:  0x23 0x00 0x1C 0xC0
* Up:       0x23 0x01 0x18 0xC3
* Down:     0x23 0x02 0x18 0xC2
```

# HW reverse engineering info

## H8S MCU mode strapping

Strapped to Mode 5
- MD0 VCC
- MD1 GND
- MD2 VCC

## I2C EEPROM
SDA - P53
SCL - P52

## External RAM
64KByte

# Firmware reversing info

## RAM

### Internal RAM
2K on chip RAM present between 0xFFF400 to 0xFFFC00

### External RAM
The contents of the external RAM is initialized from the flash in multiple portions

- ROM 0x01007E-0x0101F2 copied to RAM 0x221140-0x2212B4 (372 byte)
- ROM 0x010570-0x0113A8 copied to RAM 0x2212B4-0x2220EC (3640 byte)

## UART 
Both UART0 (connected to the terminal) and UART1 (debug?) seems to be initialized and used.

UART0 (terminal) has 31 byte RX buffer, UART1 (debug?) has 15 byte buffer

UART1 (debug?) initialized to 4800 baud (F_CPU == 16M, BRR1 == 103), the baud rate is adjustable with some commands.

Both UART reception handled with RX ISR.

The UART1 looks to have simpler protocol, and it might be involved in Bootloader activites (it ends in one case using a "DownLoad..." string).


UART1 (debug?) frames (only 8 byte is handled).


