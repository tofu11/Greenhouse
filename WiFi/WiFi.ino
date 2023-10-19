#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Arduino_JSON.h>
#include <string.h>
#include <iostream>
using namespace std;

const char *ssid="UB_Connect";
const char *URL="http://api.weatherapi.com/v1/current.json";
const char *API_KEY="a3607837a6a044f388275829231910";
unsigned long lastConnectionTime = 0;
const unsigned long counter = 10L * 1000L; // delay between updates, in milliseconds

String httpGETRequest(String serverName);

WiFiClientSecure client;
String server_name = "http://api.weatherapi.com/v1/current.json?key=a3607837a6a044f388275829231910&q=Buffalo&aqi=no";
String response;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to WiFi ");
  Serial.print(ssid);

  //connects to wifi
  WiFi.begin(ssid);

  Serial.println();
  Serial.println("Connecting ...");

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }
  Serial.println("Connected!");
  
  Serial.print("NodeMCU IP Address:");
  Serial.print(WiFi.localIP());

}

// the loop function runs over and over again forever
void loop() {
  if(WiFi.status() == WL_CONNECTED) {
    response = httpGETRequest(server_name);
    Serial.print("Raw response: ");
    Serial.println(response);
    JSONVar response_obj = JSON.parse(response);

    if(JSON.typeof(response_obj) == "undefined") {
      Serial.println("Parsing input failed");
      return;
    }
    Serial.print("JSON Object: ");
    Serial.println(response_obj);

    JSONVar keys = response_obj.keys();

    for(int i=0; i<keys.length(); i++) {
      JSONVar value = response_obj[keys[i]];
      Serial.print(keys[i]);
      Serial.print(" = ");
      Serial.print(value);
    }  
    lastConnectionTime = millis();
    if (millis() - lastConnectionTime > counter) {  
      response = httpGETRequest(server_name);
      Serial.println(response);
      JSONVar response_obj = JSON.parse(response);

      if(JSON.typeof(response_obj) == "undefined") {
        Serial.println("Parsing input failed");
        return;
      }
      Serial.print("JSON Object: ");
      Serial.println(response_obj);
  
      JSONVar keys = response_obj.keys();
  
      for(int i=0; i<keys.length(); i++) {
        JSONVar value = response_obj[keys[i]];
        Serial.print(keys[i]);
        Serial.print(" = ");
        Serial.print(value);
      }
    }
  }else {
    Serial.println("WiFi Disconnected");
  }
  lastConnectionTime = millis();
}
  
String httpGETRequest(String serverName) {
  WiFiClient client;
  HTTPClient http;

  // Your IP address with path or Domain name with URL path 
  http.begin(client, server_name);

  // If you need Node-RED/server authentication, insert user and password below
  //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");

  // Send HTTP POST request
  int httpResponseCode = http.GET();

  String payload = "{}"; 
  Serial.print("Response: ");
  Serial.println(http.getString());
  Serial.println();
  if(httpResponseCode > 0) {
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    return payload;
  }
  // Free resources
  http.end();
  return payload;
}
