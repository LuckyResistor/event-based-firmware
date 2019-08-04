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
  const auto delta = static_cast<int32_t>(_next - currentTime);
  return delta <= 0;  
}

void Event::scheduleNext(uint32_t delay)
{
  _next += delay;
}
