#pragma once

#include <Arduino.h>

class Event
{
public:
  typedef void (*Function)();
public:
  Event();
  Event(Function call, uint32_t next);
  Event(const Event&) = default;
  Event& operator=(const Event&) = default;
public:
  bool isValid() const;
  bool isReady(uint32_t currentTime) const;
  Function getCall() const;
  void clear();
private:
  Function _call;
  uint32_t _next; 
};
