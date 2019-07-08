#include "Event.hpp"

Event::Event()
  : _call(nullptr), _next(0)
{
}

Event::Event(Function call, uint32_t next)
  : _call(call), _next(next)
{   
}

bool Event::isValid() const
{
  return _call != nullptr;
}

bool Event::isReady(uint32_t currentTime) const
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

Event::Function Event::getCall() const
{
  return _call;
}

void Event::clear()
{
  _call = nullptr;
}
