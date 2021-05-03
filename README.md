# esp-firmware-stuff
ESP32/ESP8266 firmwares and tools


## Notes

[AT API](https://www.espressif.com/sites/default/files/documentation/4a-esp8266_at_instruction_set_en.pdf)

Default UART: 115200 8N1. AT commands sent with CR/LF.

Use cutecom, for example.


## ESP8266 ESP-01 5V 12V 1 2 4 Way WiFi Relay
[Aliexpress](https://es.aliexpress.com/item/4001094436563.html)

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


## Programmer

[This programmer](https://www.aliexpress.com/snapshot/0.html?orderId=8129207443365652) 
plus a jump to ground GPIO 0 to GND in program mode
[as shown here](https://neburtechspace.blogspot.com/2018/01/programming-esp8266-esp-01-using-uart.html).

## Configure

https://tasmota.github.io/docs/devices/LC-Technology-WiFi-Relay/

LC Technology WiFi Relay - Dual Relay 

To configure an LC Technology ESP8266 Relay X2, use the following settings...

Set module to Generic (in module configuration and click save)
Set GPIO0 and GPIO2 as Relay1 and Relay 2 (in module configuration and click save)
Disable SerialLog (type seriallog 0 in the Tasmota console)
Add the following rules typing in the Tasmota console:

Important finding: send "ready\r\n" (hex 72656164790a0d) required.

Rule1
 on System#Boot do Backlog Baudrate 115200; SerialSend5 72656164790a0d endon
 on Power1#State=1 do SerialSend5 A00101A2 endon
 on Power1#State=0 do SerialSend5 A00100A1 endon
 on Power2#State=1 do SerialSend5 A00201A3 endon
 on Power2#State=0 do SerialSend5 A00200A2 endon

Enable the rule (type rule1 1 in the Tasmota console)

Power on the Relay module while pressing Button #1, 
only L1 on, then after "ready" -> L3 blinking, it 
is responsive to turn on/off commands.

----
CP2102 USB-TTL module: works too. RX->TX, TX->RX.


## Web access to the tasmota console

console:

  http://192.168.18.201/cs?


## Change to static IP

Backlog IPAddress1 192.168.18.201; IPAddress2 192.168.18.1; IPAddress3 255.255.255.0; IPAddress4 192.168.18.1

restart 1



## others

https://github.com/nodemcu/nodemcu-firmware


