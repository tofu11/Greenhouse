#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

// For the Adafruit shield, these are the default.
#define TFT_CS 10
#define T_CS 7

#define TFT_DC 9
#define TFT_MOSI 11
#define TFT_CLK 13
#define TFT_RST 8
#define TFT_MISO 12
#define LDR_SENSOR 2
#define LDR_RELAY 3
#define MOISTURE_SENSOR A0
#define PUMP 6

#define MAIN_MENU_PAGE 0
#define MOISTURE_PAGE 1

#define MOISTURE_LEVEL_BASE 600

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

boolean led_status = false;
String weather = "sunny";
String date_time = "Wednesday, Oct 18th, 2023, 6:19pm";
int page = MAIN_MENU_PAGE;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(TFT_CS, OUTPUT);
  pinMode(T_CS,OUTPUT);
  
  pinMode(LDR_RELAY, OUTPUT);
  pinMode(LDR_SENSOR, INPUT);
  
  pinMode(MOISTURE_SENSOR, INPUT);
  pinMode(PUMP, OUTPUT);
  
  digitalWrite(TFT_CS, HIGH);
  digitalWrite(T_CS,HIGH);
  
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
  tft.fillScreen(ILI9341_WHITE);
  mainMenu();
}


void loop() {
  // display either the main menu or moisture page
  switch(page) {
    case MAIN_MENU_PAGE:
      mainMenu();
      break;
    case MOISTURE_PAGE:
      moisture();
      break;
    default:
      break;
  }

  
  // if user touches moisture sensor button, display which of the 2 plots needs to be watered based on moisture level
  if(switchToMainMenuPage()) {
    // display moisture page by switching page to MOISTURE
    page = MOISTURE_PAGE;
  }
  // if on moisture page and user presses menu button, display main menu page
  if(switchToMoisturePage()) {
    page = MAIN_MENU_PAGE;
  }

  
  // if between 8am and 8pm, turn on LED's based on light level
  // get time from wifi module
  if(senseLightLevel()) {
    // LED and light sensor logic
     //If there is no light then the sensor value will be 1 else the value will be 0
    int sensorValue = digitalRead(LDR_SENSOR);

    //Serial.println(sensorValue);
    //Its dark
    if (sensorValue == HIGH) {
      digitalWrite(LDR_RELAY, LOW);  //Relay is low level triggered relay so we need to write LOW to switch on the light
      if(!led_status) {
        int x1 = 0, y1 = 0, x2 = 70, y2 = 20;
        tft.fillRect(x1, y1, x2-x1, y2-y1, ILI9341_WHITE);
      }
      led_status = true;
    }
    else {
      digitalWrite(LDR_RELAY, HIGH);    
      if(led_status) {
        int x1 = 0, y1 = 0, x2 = 70, y2 = 20;
        tft.fillRect(x1, y1, x2-x1, y2-y1, ILI9341_WHITE);
      }
      led_status = false;
    }
    //You can add delay for getting good light settled reading depending upon need
  }
  
  // always water plants based on soil moisture level
  // get moisture level from moisture sensor
  int moisture_level = analogRead(MOISTURE_SENSOR);
  Serial.print("moisture: ");
  Serial.print(moisture_level);
  Serial.print("\n");
  if(moisture_level < MOISTURE_LEVEL_BASE) {
    Serial.print("Turn pump on\n");
    digitalWrite(PUMP, HIGH);
  } else {
    Serial.print("Turn pump off\n");
    digitalWrite(PUMP, LOW);
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

// if time is between 8am and 8pm according to wifi module, return true
boolean senseLightLevel() {
  return true;
}

boolean switchToMainMenuPage() {
  return true;
}

boolean switchToMoisturePage() {
  return true;
}

unsigned long mainMenu() {
  // fill screen with white background
  unsigned long start = micros();

  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(1);

  // get LED status from LDR sensor
  tft.println("LED Status: ");
  if(led_status) {
    tft.println("ON");
  }else {
    tft.println("OFF");
  }
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

unsigned long moisture() {
  unsigned long start = micros();
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
