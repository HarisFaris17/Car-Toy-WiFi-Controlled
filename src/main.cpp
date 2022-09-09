#include <Arduino.h>
#include<WiFiClient.h>
#include<WiFi.h>
const char* ssid = "Mi Phon";
const char* password = "qwerty67";
void setup() {
  Serial.begin(57600);
  // wifi STA (station) means the esp32 can connect to other device (like router), hence enabling esp32 to connect to the internet
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);
  if(WiFi.reconnect()) delay(5000);
  WiFiClient client = WiFiClient();
  client.connect(ssid,8080);
}

void loop() {
  check_wifi_connection();
}

void check_wifi_connection(){
  while(!WiFi.isConnected()) {
    WiFi.reconnect();
    Serial.println("Reconnecting again....");
    delay(5000);
  }
}