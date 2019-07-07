const uint8_t cOrangeLedPin = 13;
const uint8_t cGreenLedPin = 12;

uint32_t gNextOrangeLedEvent;
uint32_t gNextGreenLedEvent;

void setup() {
  pinMode(cOrangeLedPin, OUTPUT);
  pinMode(cGreenLedPin, OUTPUT);
  gNextOrangeLedEvent = millis() + 100;
  gNextGreenLedEvent = millis() + 100;
}

void orangeLedEvent()
{
  static bool state = false;
  digitalWrite(cOrangeLedPin, (state ? HIGH : LOW));
  state = !state;
  gNextOrangeLedEvent += 810;
}

void greenLedEvent()
{
  static bool state = false;
  digitalWrite(cGreenLedPin, (state ? HIGH : LOW));
  state = !state;
  gNextGreenLedEvent += 1240;
}

void loop() {
  const auto currentTime = millis();
  if (currentTime == gNextOrangeLedEvent) {
    orangeLedEvent();
  }
  if (currentTime == gNextGreenLedEvent) {
    greenLedEvent();
  }
  while (millis() == currentTime) {}
}
