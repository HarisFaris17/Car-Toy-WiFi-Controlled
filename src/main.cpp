#include <Arduino.h>
#include<WiFiClient.h>
#include<WiFi.h>
#include<WebServer.h>
const char* ssid = "Mi Phon";
const char* password = "qwerty67";

void check_wifi_connection();
void server_path_config();
void turn_left();
void turn_right();
void straight();
void back_left();
void back_right();
void back();
void not_found();

WebServer server(80);


void setup() {
  Serial.begin(115200);
  // wifi STA (station) means the esp32 can connect to other device (like router), hence enabling esp32 to connect to the internet
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);
  // this will make the wifi auto reconnect every time it loses its connection
  WiFi.setAutoReconnect(true);
  check_wifi_connection();
  server_path_config();
}

void loop() {
  check_wifi_connection();
  server.handleClient();
}

void check_wifi_connection(){
  if(!WiFi.isConnected()){
    while(!WiFi.isConnected()) {
      Serial.println("Reconnecting again....");
      delay(5000);
    }
    Serial.println("Wifi connected on IP : "+WiFi.localIP().toString());
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
  Serial.println("The car is turning left");
  // set the car turn left
}

void turn_right(){
  server.send(200,"text/html","car turning right");
  Serial.println("The car is turning right");
  // set the car turn right
}

void straight(){
  server.send(200,"text/html","car moving straight");
  Serial.println("The car is moving straight");
  // set the car turn straight
}

void back_left(){
  server.send(200,"text/html","car moving left backwards");
  Serial.println("The car is moving left backward");
  // set the car moving left backward
}

void back_right(){
  server.send(200,"text/html","car moving right backwards");
  Serial.println("The car is moving right backward");
  // set the car moving right backward
}

void back(){
  server.send(200,"text/html","car moving backwards");
  Serial.println("The car is moving backward");
  // set the car moving right backward
}

void not_found(){
  server.send(404,"text/html","Not found");
  Serial.println("The request is not found");
}