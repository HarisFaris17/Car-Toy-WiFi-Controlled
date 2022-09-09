#include <Arduino.h>
#include<WiFiClient.h>
#include<WiFi.h>
#include<WebServer.h>
const char* ssid = "Mi Phon";
const char* password = "qwerty67";

WebServer server(80);


void setup() {
  Serial.begin(57600);
  // wifi STA (station) means the esp32 can connect to other device (like router), hence enabling esp32 to connect to the internet
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);
  // this will make the wifi auto reconnect every time it is lose the connection
  WiFi.setAutoReconnect(true);
  check_wifi_connection();
  server_path_config();
}

void loop() {
  server.handleClient();
  check_wifi_connection();
}

void check_wifi_connection(){
  while(!WiFi.isConnected()) {
    Serial.println("Reconnecting again....");
    delay(5000);
  }
}

void server_path_config(){
  // check if the client requesting to the esp32 (server)
    server.on("/turnleft",turn_left);
    server.on("/turnright",turn_right);
    server.on("/straight",straight);
    server.on("/backleft",back_left);
    server.on("/backright",back_right);
    server.on("/back",back);
    server.onNotFound(not_found);
    server.begin();
    Serial.println("HTTP Web server configured!");
}

void turn_left(){
  server.send(200,"text/html","car turning left");
  // set the car turn left
}

void turn_right(){
  server.send(200,"text/html","car turning left");
  // set the car turn right
}

void straight(){
  server.send(200,"text/html","car moving straight");
  // set the car turn straight
}

void back_left(){
  server.send(200,"text/html","car moving left backwards");
  // set the car moving left backward
}

void back_right(){
  server.send(200,"text/html","car moving right backwards");
  // set the car moving right backward
}

void back(){
  server.send(200,"text/html","car moving backwards");
  // set the car moving right backward
}

void not_found(){
  server.send(404,"text/html","Not found");
}