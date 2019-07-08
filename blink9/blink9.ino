#include "Event.hpp"

const uint8_t cOrangeLedPin = 13;

Event gEvent;

void ledOnEvent();
void ledOffEvent();

void setup() {
  pinMode(cOrangeLedPin, OUTPUT);
  ledOnEvent();
}

void ledOnEvent()
{
  digitalWrite(cOrangeLedPin, HIGH);
  gEvent = Event(&ledOffEvent, millis() + 800);
}

void ledOffEvent()
{
  digitalWrite(cOrangeLedPin, LOW);  
  gEvent = Event(&ledOnEvent, millis() + 600);
}

void loop() {
  const auto currentTime = millis();
  if (gEvent.isValid() && gEvent.isReady(currentTime)) {
    auto call = gEvent.getCall();
    gEvent.clear();
    call();
  }
  while (millis() == currentTime) {}
}
