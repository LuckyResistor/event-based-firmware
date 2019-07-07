const uint8_t cOrangeLedPin = 13;

uint32_t gNextEvent;
bool gBlinkState = false;

void setup() {
  pinMode(cOrangeLedPin, OUTPUT);
  gNextEvent = millis() + 1000;
}

void loop() {
  while (millis() != gNextEvent) {}
  digitalWrite(cOrangeLedPin, (gBlinkState ? HIGH : LOW));
  gBlinkState = !gBlinkState;
  gNextEvent += 1000;
}
