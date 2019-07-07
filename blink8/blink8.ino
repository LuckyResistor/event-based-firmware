#include "BlinkLed.hpp"
#include "Event.hpp"

Event gBlinkLedEvent;

void setup() {
  BlinkLed::initialize();
  gBlinkLedEvent.start(10);
}

void loop() {
  const auto currentTime = millis();
  if (gBlinkLedEvent.isReady(currentTime)) {
    const auto scheduledDelay = BlinkLed::event();
    gBlinkLedEvent.scheduleNext(scheduledDelay);
  }
  while (millis() == currentTime) {}
}
