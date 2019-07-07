#pragma once

#include <Arduino.h>

class Event
{
public:
  Event();
public:
  void start(uint32_t delay);
  bool isReady(uint32_t currentTime);
  void scheduleNext(uint32_t delay);
private:
  uint32_t _next; 
};
