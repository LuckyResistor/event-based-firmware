#include "Event.hpp"

const uint8_t cOrangeLedPin = 13;
const uint8_t cGreenLedPin = 12;

Event gNextOrangeLedEvent;
Event gNextGreenLedEvent;

void setup() {
  pinMode(cOrangeLedPin, OUTPUT);
  pinMode(cGreenLedPin, OUTPUT);
  gNextOrangeLedEvent.start(100);
  gNextGreenLedEvent.start(100);
}

void orangeLedEvent()
{
  static bool state = false;
  digitalWrite(cOrangeLedPin, (state ? HIGH : LOW));
  state = !state;
  gNextOrangeLedEvent.scheduleNext(810);
}

void greenLedEvent()
{
  static bool state = false;
  digitalWrite(cGreenLedPin, (state ? HIGH : LOW));
  state = !state;
  gNextGreenLedEvent.scheduleNext(1240);
}

void loop() {
  const auto currentTime = millis();
  if (gNextOrangeLedEvent.isReady(currentTime)) {
    orangeLedEvent();
  }
  if (gNextGreenLedEvent.isReady(currentTime)) {
    greenLedEvent();
  }
  while (millis() == currentTime) {}
}
