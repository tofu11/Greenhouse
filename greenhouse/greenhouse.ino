#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

// For the Adafruit shield, these are the default.
#define TFT_CS 10
#define TFT_DC 9
#define TFT_MOSI 11
#define TFT_CLK 13
#define TFT_RST 8
#define TFT_MISO 12
#define MAIN 0
#define MOISTURE 1
#define MOISTURE_SENSOR 2
#define RELAY 3

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

String led_status = "ON";
String weather = "sunny";
String date_time = "Wednesday, Oct 18th, 2023, 6:19pm";
int page = MAIN;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(TFT_CS, OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(SENSOR_PIN, INPUT);
  
  digitalWrite(TFT_CS, HIGH);
  digitalWrite(7,HIGH);

  
  tft.begin();
  /* read diagnostics (optional but can help debug problems)
  uint8_t x = tft.readcommand8(ILI9341_RDMODE);
  Serial.print("Display Power Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDMADCTL);
  Serial.print("MADCTL Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDPIXFMT);
  Serial.print("Pixel Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDIMGFMT);
  Serial.print("Image Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDSELFDIAG);
  Serial.print("Self Diagnostic: 0x"); Serial.println(x, HEX); */
  mainMenu();
}


void loop() {
  // display either the main menu or moisture page
  switch(page) {
    case MAIN:
      mainMenu();
      break;
    case MOISTURE:
      moisture();
      break;
    default:
      break;
  }

  
  // if user touches moisture sensor button, display which of the 2 plots needs to be watered based on moisture level
  if() {
    // display moisture page by switching page to MOISTURE
    page = MOISTURE;
  }
  // if on moisture page and user presses menu button, display main menu page
  if() {
    page = MAIN;
  }

  
  // if between 8am and 8pm, turn on LED's based on light level
  // get time from wifi module
  if() {
    // LED and light sensor logic
     //If there is no light then the sensor value will be 1 else the value will be 0
    int sensorValue = digitalRead(SENSOR_PIN);
    //Serial.println(sensorValue);
    //Its dark
    if (sensorValue == HIGH) {
      digitalWrite(RELAY_PIN, LOW);  //Relay is low level triggered relay so we need to write LOW to switch on the light
    }
    else {
      digitalWrite(RELAY_PIN, HIGH);    
    }
    //You can add delay for getting good light settled reading depending upon need
    delay(1000);
  }
  
  // always water plants based on soil moisture level
  // get moisture level from moisture sensor
  if() {
    // water pump and moisture sensor logic
  }
} 

/* prints current values for:
 *  LED status
 *  Weather
 *  Date
 *  Time
 *  Day of week
 * to the display
*/

unsigned long mainMenu() {
  // fill screen with white background
  tft.fillScreen(ILI9341_WHITE);
  unsigned long start = micros();

  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(1);

  // get LED status from LDR sensor
  tft.println("LED Status: ");
  tft.println(led_status);
  tft.println();
  
  // get outdoor weather from wifi chip
  tft.println("Weather: ");
  tft.println(weather);
  tft.println();
  
  // get date/time/day of week info from wifi chip
  tft.println("Date/Time: ");
  tft.println(date_time);
  tft.println();
  
  return micros() - start;
}

// sample function from adafruit ili9341 library graphicstest example
unsigned long testText() {
  tft.fillScreen(ILI9341_BLACK);
  // save time since program started
  unsigned long start = micros();
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(ILI9341_YELLOW); tft.setTextSize(2);
  tft.println(1234.56);
  tft.setTextColor(ILI9341_RED);    tft.setTextSize(3);
  tft.println(0xDEADBEEF, HEX);
  tft.println();
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(5);
  tft.println("Groop");
  tft.setTextSize(2);
  tft.println("I implore thee,");
  tft.setTextSize(1);
  tft.println("my foonting turlingdromes.");
  tft.println("And hooptiously drangle me");
  tft.println("with crinkly bindlewurdles,");
  tft.println("Or I will rend thee");
  tft.println("in the gobberwarts");
  tft.println("with my blurglecruncheon,");
  tft.println("see if I don't!");
  return micros() - start;
}
