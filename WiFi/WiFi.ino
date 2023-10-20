#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Arduino_JSON.h>

const char *ssid="UB_Connect";
unsigned long lastConnectionTime = 0;
//const unsigned long counter = 10L * 1000L; // delay between updates, in milliseconds
//const String API_KEY = "a3607837a6a044f388275829231910";
const String CITY = "Buffalo";

String httpGETRequest(String serverName);

WiFiClientSecure client;
HTTPClient http;
//String server_name = "api.weatherapi.com/v1/current.json";
String server_name = "api.open-meteo.com/v1/forecast?latitude=52.52&longitude=13.41&current=temperature_2m,relativehumidity_2m,apparent_temperature,is_day,precipitation,rain,showers,snowfall,cloudcover&temperature_unit=fahrenheit&windspeed_unit=mph&precipitation_unit=inch&forecast_days=1";
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

  unsigned long timeout = millis();
  while(millis() - timeout < 10000 && WiFi.status() != WL_CONNECTED) {
    delay(500);
    timeout += 500;
    Serial.println(".");
  }
  Serial.println("Connected!");
  Serial.print("NodeMCU IP Address:");
  Serial.print(WiFi.localIP());

}

// the loop function runs over and over again forever
void loop() {
    if (millis() - lastConnectionTime > 5000) {  
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
      lastConnectionTime = millis();
  }
}

String httpGETRequest(String serverName) {
  
  //  String URL = serverName + "?key=" + API_KEY + "&q=" + CITY + "&aqi=no";
  String URL = serverName;
  http.begin(client, URL);
  
  // If you need Node-RED/server authentication, insert user and password below
  //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  if(httpResponseCode > 0) {
    Serial.print("Response: ");
    Serial.println(http.getString());
    Serial.println();
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();
  return payload;
}
