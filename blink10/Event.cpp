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
  const auto delta = static_cast<int32_t>(_next - currentTime);
  return delta <= 0;  
}

Event::Function Event::getCall() const
{
  return _call;
}

void Event::clear()
{
  _call = nullptr;
}
