# General parameters of the RL-2000 (City 120) communication
 * 0-5V levels between the PIC in the terminal and the H8S/2000 in the robot
 * 19200 baud 8n1 inverted (UART idles at low)
 * Robot seems to be the master
 * Checksum: sum all bytes then negate
 
# Terminal ackets
Terminal sends the following packets periodically (with varying -depending on the traffic from the robot- rate between 10-60ms). 
I never saw traffic on the TX and RX at the same time (the terminal and the robot seems to be handshaking on the bus).

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

# Newer models protocol info
RS/RC/RX packet format:

170 (API preamble)
MSG size (wo checksum)
