#include "EventLoop.hpp"

const uint8_t cOrangeLedPin = 13;
const uint8_t cGreenLedPin = 12;

void orangeOnEvent();
void orangeOffEvent();
void greenToggleEvent();

void setup() {
  pinMode(cOrangeLedPin, OUTPUT);
  pinMode(cGreenLedPin, OUTPUT);
  EventLoop::initialize();
  orangeOnEvent();
  greenToggleEvent();
}

void orangeOnEvent() {
  digitalWrite(cOrangeLedPin, HIGH);
  EventLoop::addDelayedEvent(&orangeOffEvent, 800);
}

void orangeOffEvent() {
  digitalWrite(cOrangeLedPin, LOW);  
  EventLoop::addDelayedEvent(&orangeOnEvent, 600);
}

void greenToggleEvent() {
  static bool isHigh = false;
  digitalWrite(cGreenLedPin, (isHigh ? HIGH : LOW));
  isHigh = !isHigh;
  EventLoop::addDelayedEvent(&greenToggleEvent, 200);  
}

void loop() {
  EventLoop::loop();
}
