#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "iPhone"; // Replace with your desired AP SSID
const char* password = "11111111"; // Replace with your desired AP password
AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);

  Serial.print("AP SSID: ");
  Serial.println(ssid);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    int sensorValue = analogRead(A0); // Replace this with your actual sensor reading
    String data = String(sensorValue);
    request->send(200, "text/plain", data);
  });

  server.begin();
}

void loop() {
  // Handle other tasks if needed
}

