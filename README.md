19200 baud 8n1

Robot seems to be the master

Checksum: sum all bytes then negate

Terminal sends periodically:

Idle:     0x23 0x00 0x18 0xC4

Forward:  0x23 0x40 0x18 0x84

Backward: 0x23 0x80 0x18 0x44

Left:     0x23 0x10 0x18 0xB4

Right:    0x23 0x20 0x18 0xA4

Rabbit:   0x23 0x00 0x19 0xC3

C:        0x23 0x08 0x18 0xBC

Go:       0x23 0x80 0x18 0x44

Stop:     0x23 0x00 0x1A 0xC2

Factory:  0x23 0x00 0x1C 0xC0

Up:       0x23 0x01 0x18 0xC3

Down:     0x23 0x02 0x18 0xC2


RS/RC/RX packet format:

170 (API preamble)
MSG size (wo checksum)
