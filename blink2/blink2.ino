const uint8_t cOrangeLedPin = 13;

uint32_t gNextEvent;

void setup() {
  pinMode(cOrangeLedPin, OUTPUT);
  gNextEvent = millis() + 1000;
}

void loop() {
  while (millis() != gNextEvent) {}
  digitalWrite(cOrangeLedPin, HIGH);
  gNextEvent += 1000;
  while (millis() != gNextEvent) {}
  digitalWrite(cOrangeLedPin, LOW);
  gNextEvent += 1000;
}
