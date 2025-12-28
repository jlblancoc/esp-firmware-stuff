#include <Arduino.h>

const uint8_t RELAY1_PIN = 10;
const uint8_t RELAY2_PIN = 11;

void relayOn(uint8_t relayPin) {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
}

void relayOff(uint8_t relayPin) {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
}

void setup() {}

void loop() {

  relayOn(RELAY1_PIN);
  delay(2000);

  relayOff(RELAY1_PIN);
  delay(2000);

  relayOn(RELAY2_PIN);
  delay(2000);

  relayOff(RELAY2_PIN);
  delay(2000);
}
