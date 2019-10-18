int in[] = {8, 9, 12, 13};
int en[] = {10, 11};

void setup()
{
  Serial.begin(115200);
  
  for (int i = 0; i < 4; i++)
    pinMode(in[i] , OUTPUT);
  
  for (int i = 0; i < 2; i++)
    pinMode(en[i] , OUTPUT);
}

void loop() {
  if (Serial.available())
  {
    char ch = Serial.read();
    
  }
}
