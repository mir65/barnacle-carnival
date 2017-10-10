avrdude -p m328p -c arduino -b 57600 -P /dev/ttyUSB0 -U flash:w:build/test1.hex:a
