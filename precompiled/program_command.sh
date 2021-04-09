#!/bin/bash
# Use: first arg=serial port

esptool.py -vv --chip esp8266 -p $1 -ca 0x00000 -cf ESPEasy_1M_128kSPIFFS_PUYA.bin

