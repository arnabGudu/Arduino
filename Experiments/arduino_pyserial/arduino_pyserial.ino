void setup() {
  Serial.begin(115200);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop() {
  if (Serial.available())
  {
    byte b = Serial.readBytes();
    analogWrite(9, base + b);
    analogWrite(10, base - b);
  }
}
