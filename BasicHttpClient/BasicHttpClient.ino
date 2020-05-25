#include <AtWiFi.h>
#include "HTTPClient.h"

#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "PASSWORD"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  // attempt to connect to Wifi network:
  while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      // wait 1 second for re-trying
      delay(100);
  }

  Serial.println("Connected");

  HTTPClient http;

  http.begin("http://example.com/index.html");

  Serial.println("HTTP GET");
  int httpCode = http.GET();

  if(httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
      if(httpCode == HTTP_CODE_OK) {
          String payload = http.getString();
          Serial.println(payload);
      }
  } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
  Serial.println("end");
}

void loop() {
  // put your main code here, to run repeatedly:

}
