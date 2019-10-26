#include <Wire.h>
#include <LiquidCrystal.h>

const int rs = 2, en = 3, d4 = 7, d5 = 8, d6 = 9, d7 = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Wire.begin(8);                
  Wire.onReceive(receiveEvent); 
  Serial.begin(9600);           
  lcd.begin(16, 2);
  lcd.print("  CYBORG  ROOM  ");
  lcd.setCursor(0, 1);
  lcd.print("   AUTOMATION   ");
  delay(2000);
}

void loop() {
  delay(100);
}

void receiveEvent(int howMany) {
 while (Wire.available()) {
    char c = Wire.read();      
    Serial.print(c);
    lcd.print(c);          
  }
 Serial.println();            
}
