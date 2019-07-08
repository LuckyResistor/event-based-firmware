#include "EventLoop.hpp"

#include "Event.hpp"

namespace EventLoop {

const uint8_t cEventStackSize = 8;

uint32_t gCurrentTime = 0;
Event gEvents[cEventStackSize];

void initialize()
{
  gCurrentTime = millis();
}

void addEvent(const Event &newEvent)
{
  for (auto &event : gEvents) {
    if (!event.isValid()) {
      event = newEvent;
      break;
    }
  }
}

void addDelayedEvent(Function call, uint32_t delay)
{
  addEvent(Event(call, gCurrentTime + delay));
}

void processEvents()
{
  for (auto &event : gEvents) {
    if (event.isValid() && event.isReady(gCurrentTime)) {
      const auto call = event.getCall();
      event.clear();
      call();      
    }
  }  
}

void loop()
{
  const auto currentTime = millis();
  if (gCurrentTime != currentTime) {
    gCurrentTime = currentTime;
    processEvents();  
  }
}


}
