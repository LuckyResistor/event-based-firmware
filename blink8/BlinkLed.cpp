#include "BlinkLed.hpp"

namespace BlinkLed {

enum class Phase {
  FadeIn,
  On,
  FadeOut,
  Off
};

const uint16_t fadeCount = 64;
const uint8_t cOrangeLedPin = 13;

static auto phase = Phase::FadeIn;
static uint16_t phaseCount = 0;
static bool state = false;

void initialize()
{
  pinMode(cOrangeLedPin, OUTPUT);
}

uint32_t event()
{
  uint32_t scheduledDelay;
  if (phase == Phase::FadeIn || phase == Phase::FadeOut) {
    state = !state;
    if (state ^ (phase == Phase::FadeOut)) {
       scheduledDelay = phaseCount;
    } else {
       scheduledDelay = (fadeCount-phaseCount+1);      
    }
    if (phaseCount == fadeCount) {
      phase = (phase == Phase::FadeIn ? Phase::On : Phase::Off);
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
  
}
