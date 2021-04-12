# esp-firmware-stuff
ESP32/ESP8266 firmwares and tools


## Notes

[AT API](https://www.espressif.com/sites/default/files/documentation/4a-esp8266_at_instruction_set_en.pdf)

Default UART: 115200 8N1. AT commands sent with CR/LF.

Use cutecom, for example.


## ESP8266 ESP-01 5V 12V 1 2 4 Way WiFi Relay
[Aliexpress](https://www.aliexpress.com/snapshot/0.html?orderId=8128207346845652)

Turn on the first relay:  A0 01 01 A2
Close the first relay:    A0 01 00 A1
Turn on the second relay: A0 02 01 A3
Close the second relay:   A0 02 00 A2

```bash
echo -n -e "\xa0\x01\x01\xa2" | nc 192.168.18.20 8080 -w0
echo -n -e "\xa0\x01\x00\xa1" | nc 192.168.18.20 8080 -w0

echo -n -e "\xa0\x02\x01\xa3" | nc 192.168.18.20 8080 -w0
echo -n -e "\xa0\x02\x00\xa2" | nc 192.168.18.20 8080 -w0
```
