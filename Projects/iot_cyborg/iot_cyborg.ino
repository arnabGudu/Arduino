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
  pcf.begin(0);

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

void loop() {

  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  url = "/api_php.php?";

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  delay(1000);

  String section = "header";
  while (client.available())
  {
    String line = client.readStringUntil('\r');

//    if (millis() % 5000 == 0)
//    {
//      float temp = (analogRead(A0) * 3.3 / 1023.0 - 0.5) * 100;
//      url = "api_php.php?temp=" + String(temp);
//      client.print(String("GET ") + url + " HTTP/1.1\r\n" +
//                   "Host: " + host + "\r\n" +
//                   "Connection: close\r\n\r\n");
//    }

    if (section == "header")
    {
      if (line == "\n")
        section = "json";
    }
    else if (section == "json")
    {
      section = "ignore";
      String result = line.substring(1);

      //https://arduinojson.org/v5/assistant/ for size calculation
      const size_t buffSize = JSON_ARRAY_SIZE(10) + 11 * JSON_OBJECT_SIZE(2);
      char json[buffSize];
      result.toCharArray(json, buffSize);

      DynamicJsonBuffer jsonBuffer(buffSize);
      JsonObject& json_parsed = jsonBuffer.parseObject(json);

      if (!json_parsed.success())
      {
        Serial.println("parseObject() failed");
        return;
      }

      for (int i = 0; i < 8; i++)
      {
        String led = json_parsed["led"][i]["status"];

        if (led == "1")
          pcf.write(i, 1);
        else if (led == "0")
          pcf.write(i, 0);
      }
    }
  }
  Serial.println(pcf.returnMask(), BIN);
}
