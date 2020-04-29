# OneWheel Lights

Simple RPM controlled lights for DIY OneWheel builds. Using the library from SolidGeek (https://github.com/SolidGeek/VescUart) for communicating with the Vesc.


## Implementation

Connect WS2812 data line to A5 pin, +5 and GND to the +5 and GND on the Arduino pro mini.

Arduino RX to Vesc TX, Arduino TX to Vesc RX. +5 are taken direct from the Vesc +5 line and should be enought for about 20 LED's but I would recommend to take it from it's own power supply.
