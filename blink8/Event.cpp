#include "Event.hpp"

#include <Arduino.h>

Event::Event()
  : _next(0)
{
}

void Event::start(uint32_t delay)
{
  _next = millis() + delay;
}

bool Event::isReady(uint32_t currentTime)
{
  if (_next == currentTime) {
    return true;
  }
  const auto delta = _next - currentTime;
  if ((delta & static_cast<uint32_t>(0x80000000ul)) != 0) {
    return true;
  }
  return false;
}

void Event::scheduleNext(uint32_t delay)
{
  _next += delay;
}
