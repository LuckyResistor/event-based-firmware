const uint8_t cOrangeLedPin = 13;

void setup() {
  pinMode(cOrangeLedPin, OUTPUT);
}

void loop() {
  digitalWrite(cOrangeLedPin, HIGH);
  delay(1000);
  digitalWrite(cOrangeLedPin, LOW);
  delay(1000);
}
