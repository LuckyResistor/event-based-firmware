#pragma once

#include "Event.hpp"

namespace EventLoop {

typedef void (*Function)();

void initialize();
void addDelayedEvent(Function call, uint32_t delay);
void loop();
  
}
