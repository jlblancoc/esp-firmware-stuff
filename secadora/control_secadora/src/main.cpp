#include <Arduino.h>

// ---- Command sequences ----
const byte CMD_READY[] = {'r', 'e', 'a', 'd', 'y', '\n', '\r'}; // "ready\r\n"
const byte RELAY1_ON[] = {0xA0, 0x01, 0x01, 0xA2};
const byte RELAY1_OFF[] = {0xA0, 0x01, 0x00, 0xA1};
const byte RELAY2_ON[] = {0xA0, 0x02, 0x01, 0xA3};
const byte RELAY2_OFF[] = {0xA0, 0x02, 0x00, 0xA2};

void sendCommand(const byte *cmd, size_t len) {
  Serial.write(cmd, len);
  Serial.flush();
}

void toggleLed() {
  static bool initialized = false;
  static uint8_t state = LOW;
  if (!initialized) {
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, state);
    initialized = true;
  }
  state = (state == LOW) ? HIGH : LOW;
  digitalWrite(LED_BUILTIN, state);
}

void setup() {
  // Hardware Serial used for relay board
  Serial.begin(115200);
  delay(1000);

  // Send handshake
  sendCommand(CMD_READY, sizeof(CMD_READY));
  delay(500);
}

void loop() {
  toggleLed();
  // Toggle relays in sequence
  sendCommand(RELAY1_ON, sizeof(RELAY1_ON));
  delay(2000);

  toggleLed();
  sendCommand(RELAY2_ON, sizeof(RELAY2_ON));
  delay(2000);

  toggleLed();
  sendCommand(RELAY1_OFF, sizeof(RELAY1_OFF));
  delay(2000);

  toggleLed();
  sendCommand(RELAY2_OFF, sizeof(RELAY2_OFF));
  delay(2000);
}
