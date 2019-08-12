char toggleOutput(String pinName)
{
  int pin;
  
  if (pinName.equals("switch1"))
    pin = 0;
  else if (pinName.equals("switch2"))
    pin = 1;
  else if (pinName.equals("switch3"))
    pin = 2;
  else if (pinName.equals("switch4"))
    pin = 3;
  else if (pinName.equals("switch5"))
    pin = 4;
  else if (pinName.equals("switch6"))
    pin = 5;
  else if (pinName.equals("switch7"))
    pin = 6;
  else if (pinName.equals("switch8"))
    pin = 7;

  pcf.toggle(pin);
  return (1 & (pcf.returnMask() >> pin));
}


void handleDigitalOutStatusJson() {
  char someBuffer[200];
  char p[8];
  
  for (int i = 0; i < 8; i++)
    p[i] = (1 & (pcf.returnMask() >> i)) + '0';
    
  sprintf(someBuffer, "{\"digital_outputs\":{\"switch1\":%c,\"switch2\":%c,\"switch3\":%c,\"switch4\":%c,\"switch5\":%c,\"switch6\":%c,\"switch7\":%c,\"switch8\":%c}}", 
          p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]);

  server.send ( 200, "application/json", someBuffer);
}


void handleDigitalOutToggle() {
  String someBuffer = "";
  char stateOfPin = toggleOutput(server.arg(0));
  someBuffer += String(stateOfPin, DEC);
  server.send ( 200, "text/plain", someBuffer);
}


float readTemperatureSensor()
{
  float temperatureC;
  int reading = analogRead(A0);
  // converting that reading to voltage, for 3.3v arduino use 3.3
  float voltage = reading * 3.3;
  voltage /= 1023.0;
  temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
  //to degrees ((voltage - 500mV) times 100)
  //Serial.print(temperatureC); Serial.println(" degrees C");
  return temperatureC; 
}
