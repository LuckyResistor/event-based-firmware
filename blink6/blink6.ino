#include "Event.hpp"

const uint8_t cOrangeLedPin = 13;

Event gBlinkLedEvent;

void setup() {
  pinMode(cOrangeLedPin, OUTPUT);
  gBlinkLedEvent.start(10);
}

void blinkLedEvent()
{
  const uint16_t fadeCount = 64;
  enum class Phase {
    FadeIn,
    On,
    FadeOut,
    Off
  };
  static auto phase = Phase::FadeIn;
  static uint16_t phaseCount = 0;
  static bool state = false;
  switch (phase) {
  case Phase::FadeIn:
    state = !state;
    if (state) {
       gBlinkLedEvent.scheduleNext(phaseCount*2);
    } else {
       gBlinkLedEvent.scheduleNext((fadeCount-phaseCount+1)*2);      
    }
    if (phaseCount == fadeCount) {
      phaseCount = 0;
      phase = Phase::On;
    }
    break;
  case Phase::On:
    state = true;
    phaseCount = 0;
    phase = Phase::FadeOut;
    gBlinkLedEvent.scheduleNext(1000);          
    break;
  case Phase::FadeOut:
    state = !state;
    if (state) {
       gBlinkLedEvent.scheduleNext((fadeCount-phaseCount+1)*2);      
    } else {
       gBlinkLedEvent.scheduleNext(phaseCount*2);
    }
    if (phaseCount == fadeCount) {
      phaseCount = 0;
      phase = Phase::Off;
    }
    break;
  case Phase::Off:
    state = false;
    phaseCount = 0;
    phase = Phase::FadeIn;
    gBlinkLedEvent.scheduleNext(1000);          
    break;
  }
  phaseCount += 1;
  digitalWrite(cOrangeLedPin, (state ? HIGH : LOW));
}

void loop() {
  const auto currentTime = millis();
  if (gBlinkLedEvent.isReady(currentTime)) {
    blinkLedEvent();
  }
  while (millis() == currentTime) {}
}
