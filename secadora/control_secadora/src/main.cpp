#include <Arduino.h>

/*
avrdude -v -c atmelice_isp -p m328p -U flash:w:./.pio/build/uno/firmware.hex:i
*/

/* ---------------- Configuration ---------------- */

// GPIO pins connected to the relay inputs
static const uint8_t RELAY1_PIN = 10;
static const uint8_t RELAY2_PIN = 11;

// Timing constants (milliseconds)
static const unsigned long TOTAL_RUNTIME_MS =
    3UL * 60UL * 60UL * 1000UL; // 3 hours
static const unsigned long CYCLE_INTERVAL_MS =
    20UL * 60UL * 1000UL; // 20 minutes

/* ---------------- State ---------------- */

static unsigned long bootTimeMs = 0;
static unsigned long lastCycleMs = 0;
static bool finished = false;

/* ---------------- Setup ---------------- */

void setup() {
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);

  digitalWrite(RELAY1_PIN, LOW);
  digitalWrite(RELAY2_PIN, LOW);

  bootTimeMs = millis();
  lastCycleMs = bootTimeMs;
}

/* ---------------- Loop ---------------- */

void loop() {
  if (finished) {
    // Do nothing forever after 3 hours
    while (true) {
      delay(1000);
    }
  }

  unsigned long now = millis();

  // Check if total runtime exceeded
  if (now - bootTimeMs >= TOTAL_RUNTIME_MS) {
    finished = true;
    return;
  }

  // Check if it's time for the next 20-minute cycle
  if (now - lastCycleMs >= CYCLE_INTERVAL_MS) {
    lastCycleMs = now;

    // Relay 1 sequence
    digitalWrite(RELAY1_PIN, HIGH);
    delay(1000); // ON for 1 second
    digitalWrite(RELAY1_PIN, LOW);

    delay(2000); // Wait 2 seconds

    // Relay 2 sequence
    digitalWrite(RELAY2_PIN, HIGH);
    delay(3000); // ON for 3 seconds
    digitalWrite(RELAY2_PIN, LOW);

    delay(2000); // Wait 2 seconds

    // Relay 1 sequence
    digitalWrite(RELAY1_PIN, HIGH);
    delay(1000); // ON for 1 second
    digitalWrite(RELAY1_PIN, LOW);
  }
}
