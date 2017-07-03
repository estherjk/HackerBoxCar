int IR_PIN_DIGITAL = 14; // Maps to D5
int IR_PIN_ANALOG = A0;

void setup() {
  Serial.begin(9600);

  pinMode(IR_PIN_DIGITAL, INPUT);
}

void loop() {
  // Read either the digital or analog value from the IR sensor
  // To read the digital value, connect D0 to GPIO4 (on board) and call readDigitalValue() in code
  // To read the analog value, connect A0 to A0 (on board) and call readAnalogValue() in code

  readDigitalValue();
  // readAnalogValue();

  // Set a delay in between readings
  delay(50);
}

void readDigitalValue() {
  int state = digitalRead(IR_PIN_DIGITAL);
  Serial.println(state);
}

void readAnalogValue() {
  int value = analogRead(IR_PIN_ANALOG);
  Serial.println(value);
}