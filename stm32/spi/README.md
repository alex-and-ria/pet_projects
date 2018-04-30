STM32/SPI written in C (embedded C)

There are one master module (STM32F407VE) and two slave modules (STM32F103C8). Connections:
```
______________________|                      ________________________
|                 PA0 |----------------| |--| PA0                    |
|                 PA1 |--------------| |-+--| PA1                    |    
|                 PA2 |--------------+---|  |                        |
|                     |              |   |  |                        |
|    STM32F407VE      |              |   |  |         STM32F103C8    |
|                 PA5 |----------|---+---+--| PA5                    |
|                 PA6 |--------|-+---+---+--| PA6                    |
|                 PA7 |------|-+-+---+---+--| PA7                    |
|                     |      | | |   |   |  |                        |
|                 GND |--|---+-+-+---+---+--| GND                    |
|_____________________|  |   | | |   |   |  |________________________|
                         |   | | |   |   |
                         |   | | |   |   |   ________________________
                         |   | | |   |   |--| PA0                    |
                         |   | | |   |------| PA1                    |    
                         |   | | |          |                        |
                         |   | | |          |                        |
                         |   | | |          |         STM32F103C8    |
                         |   | | |----------| PA5                    |
                         |   | |------------| PA6                    |
                         |   |--------------| PA7                    |
                         |                  |                        |
                         |------------------| GND                    |
                                            |________________________|
```
Project consists of two files: one (main_master.c) is for master, another (main.c) is for slaves. To select code for particular slave one of "#define sl1" or "#define sl2" lines should be uncommented while another should be commented.

Operation sequence is as follows:

1. Slaves configuring their SPI interfaces followed by sending confirmation ('spi_ready') as rising edge on master's PA0 (first slave) and PA1 (second slave) GPIO pins. Slave which will be selected by master first should be started last.
2. Master accepts this confirmation, selects slave for communication via PWM (slaves using pwm input mode to distinguish which of them is selected), receives confirmation from slaves (falling edge on PA0 or PA1 pin), enables SPI and starts communication.
3. DMA is used for communication;
4. Rising edge at PA0 (for first slave) or at PA1 (for second slave) is a signal that the message is transmitted and new SPI communication starts.
5. SPI interfaces disabled and reconfigured. Master waits for answer from slave.
6. When master receives confirmation (falling edge on PA0 or PA1 pin), it enables DMA and SPI and new iteration of SPI communication starts.

Slaves can distinguish which of them is selected by pwm duty cycle. Thus number of slave modules can be increased by dividing into more than two intervals (between intervals there should be transition region to prevent simultaneous trigerring of both slave modules).

If you have questions or ideas for improvement this project, don't hesitate and mail me (alex.and.riaqqq@gmail.com).
