#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "FastLED.h"

#define NUM_LEDS 29


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
#define MOISTURE_SENSOR_1 A0
#define MOISTURE_SENSOR_2 A1
#define PUMP 6

#define MAIN_MENU_PAGE 0
#define MOISTURE_PAGE 1

#define MOISTURE_LEVEL_BASE 450

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

boolean led_status = false;
boolean led_status_just_changed = false;
String weather = "sunny";
String date_time = "Wednesday, Oct 18th, 2023, 6:19pm";
int page = MAIN_MENU_PAGE;


const byte DATA_PIN = 2;
const byte ldrPin = A2;

const int lightThreshold = 600;
const int hysteresis = 20;

CRGB leds[NUM_LEDS];
CRGB Violet = CRGB(127, 0, 255);
CRGB colors[] = {CRGB::Violet};
//CRGB Gold = CRGB(255, 215, 0);
//CRGB colors[] = {CRGB::Red, CRGB::Gold, CRGB::White}; // Add more colors if needed

void setColor(CRGB color);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(TFT_CS, OUTPUT);
  pinMode(T_CS,OUTPUT);
  
//  pinMode(LDR_RELAY, OUTPUT);
//  pinMode(LDR_SENSOR, INPUT);
  
  pinMode(MOISTURE_SENSOR_1, INPUT);
  pinMode(MOISTURE_SENSOR_2, INPUT);
  pinMode(PUMP, OUTPUT);
  
  pinMode(ldrPin, INPUT_PULLUP);
  LEDS.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
  LEDS.setBrightness(120);
  setColor(CRGB::Black);  // Turn all LEDs off
  FastLED.show();

  digitalWrite(TFT_CS, HIGH);
  digitalWrite(T_CS,HIGH);
  
  tft.begin();
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
    static unsigned long timer = 0;
    static int colorIndex = 0;
    unsigned long interval = 3000;
    
    if (millis() - timer >= interval)
    {
        timer = millis();
        int lightValue = analogRead(ldrPin);
        Serial.println(lightValue);

        if (lightValue > lightThreshold + hysteresis)
        {
            if(led_status) {
              led_status_just_changed = true;
              led_status = false;
            }else {
              led_status_just_changed = false;
            }
            // Change the color
            setColor(colors[colorIndex]);
            FastLED.show();
            colorIndex = (colorIndex + 1) % (sizeof(colors) / sizeof(colors[0])); // Cycle through colors
        }
        else if (lightValue < lightThreshold - hysteresis)
        {
            if(!led_status) {
              led_status_just_changed = true;
              led_status = true;
            }else {
              led_status_just_changed = false;
            }
            setColor(CRGB::Black);
            FastLED.show();
        }
    }
  }
  
  // always water plants based on soil moisture level
  // get moisture level from moisture sensor
  int sensor1Value = analogRead(MOISTURE_SENSOR_1);
  int sensor2Value = analogRead(MOISTURE_SENSOR_2);
  Serial.print("Plant 1 - Moisture Level:");
  Serial.println(sensor1Value);
  Serial.print("Plant 2 - Moisture Level:");
  Serial.println(sensor2Value);
  if (sensor1Value > MOISTURE_LEVEL_BASE || sensor2Value > MOISTURE_LEVEL_BASE) {
    digitalWrite(PUMP, LOW);
  } else {
    digitalWrite(PUMP, HIGH);
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
  tft.setTextSize(3);

  // get LED status from LDR sensor
  tft.println("LED Status: ");
  if(led_status_just_changed) {
    if(led_status) {
      tft.setCursor(0, 0);
      tft.setTextColor(ILI9341_BLACK);
      tft.println("LED Status: ");
      tft.setTextColor(ILI9341_WHITE);
      tft.println("ON");
      // tft.println("OFF");
      tft.setTextColor(ILI9341_BLACK);
      tft.setCursor(0, 0);
      tft.println("LED Status: ");
      tft.println("OFF");
    }else {
      tft.setCursor(0, 0);
      tft.setTextColor(ILI9341_BLACK);
      tft.println("LED Status: ");
      tft.setTextColor(ILI9341_WHITE);
      tft.println("OFF");
      tft.setTextColor(ILI9341_BLACK);
      tft.setCursor(0, 0);
      tft.println("LED Status: ");
      tft.println("ON");
    }
  }else {
    tft.setCursor(0, 0);
      tft.setTextColor(ILI9341_BLACK);
      tft.println("LED Status: ");
      if(led_status) {
        tft.println("OFF");
      }else {
        tft.println("ON");  
      }
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


void setColor(CRGB color)
{
    for (byte n = 0; n < NUM_LEDS; n++)
    {
        leds[n] = color;
    }
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
