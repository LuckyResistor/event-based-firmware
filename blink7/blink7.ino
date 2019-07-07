#include "Event.hpp"

const uint8_t cOrangeLedPin = 13;

Event gBlinkLedEvent;

void setup() {
  pinMode(cOrangeLedPin, OUTPUT);
  gBlinkLedEvent.start(10);
}

uint32_t blinkLedEvent()
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
  uint32_t scheduledDelay;
  if (phase==Phase::FadeIn||phase==Phase::FadeOut) {
    state = !state;
    if (state ^ (phase == Phase::FadeOut)) {
       scheduledDelay = phaseCount*2;
    } else {
       scheduledDelay = (fadeCount-phaseCount+1)*2;      
    }
    if (phaseCount == fadeCount) {
      if (phase == Phase::FadeIn) {
        phase = Phase::On;
      } else {
        phase = Phase::Off;
      }
    }
    phaseCount += 1;
  } else {
    if (phase == Phase::On) {
      state = true;
      phase = Phase::FadeOut;
    } else {
      state = false;
      phase = Phase::FadeIn;
    }
    phaseCount = 0;
    scheduledDelay = 1000;          
  }
  digitalWrite(cOrangeLedPin, (state ? HIGH : LOW));
  return scheduledDelay;
}

void loop() {
  const auto currentTime = millis();
  if (gBlinkLedEvent.isReady(currentTime)) {
    const auto scheduledDelay = blinkLedEvent();
    gBlinkLedEvent.scheduleNext(scheduledDelay);
  }
  while (millis() == currentTime) {}
}
