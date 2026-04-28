#include <WiFi.h>
#include <WebServer.h>
#include "DHT.h"

const char* ssid = "/";
const char* password = "/";

WebServer server(80);
DHT dht(15, DHT22);

void handleRoot() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  
  String html = "<h1>Temperatura: " + String(t) + "°C</h1>";
  html += "<h1>Vlaznost: " + String(h) + "%</h1>";
  
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println(WiFi.localIP()); // ovo ti kaze IP adresu
  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  server.handleClient();
}
