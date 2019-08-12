#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <pcf8574_esp.h>
#include <Wire.h>

TwoWire testWire;
PCF857x pcf(0x20, &testWire);

const char* ssid     = "realme 3 Pro";
const char* password = "rourkela";
const char* host = "cyborg-room-automation.000webhostapp.com";

void setup() {
  Serial.begin(115200);
  delay(100);

  testWire.begin(4, 5);
  testWire.setClock(100000L);
  pcf.begin();

  Serial.print("\nConnecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("\nWiFi connected");
  Serial.print("\nIP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Netmask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
}

String url;
int count = 0;

void loop() {

  float temp = (analogRead(A0) * 3.3 / 1023.0 - 0.5) * 100;
  
  Serial.print("connecting to ");
  Serial.println(host);

  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  url = "/api/led/read_all.php?id=" + String(count);
  
  if (count == 8)
    url = "/api/weather/insert.php?temp=" + String(temp);
    
  Serial.print("Here");
  Serial.println(++count);

  Serial.print("Requesting url: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  delay(500);

  String section = "header";
  while (client.available())
  {
    String line = client.readStringUntil('\r');

    if (section == "header")
    {
      if (line == "\n")
        section = "json";
    }
    else if (section == "json")
    {
      section = "ignore";
      String result = line.substring(1);

      int size = result.length() + 1;
      char json[size];
      result.toCharArray(json, size);
      StaticJsonBuffer<200> jsonBuffer;
      JsonObject& json_parsed = jsonBuffer.parseObject(json);
      if (!json_parsed.success())
      {
        Serial.println("parseObject() failed");
        return;
      }
      String led = json_parsed["led"] [0] ["status"];

      if (led == "on")
      {
        pcf.write(count, 1);
        delay(100);
        Serial.println("D1 is on");
      }
      else if (led == "off")
      {
        pcf.write(count, 0);
        delay(100);
        Serial.println("D1 is off");
      }
    }
  }
}
