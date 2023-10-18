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

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

int moisture_level = 0;
String led_status = "ON";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(TFT_CS, OUTPUT);
  pinMode(7,OUTPUT);
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

}


void loop() {
  // put your main code here, to run repeatedly:

}

unsigned long mainMenu() {
  // fill screen with white background
  tft.fillScreen(ILI9341_WHITE);
  unsigned long start = micros();
  tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(1);

  // get date and time info from wifi chip
  tft.println("Date/Time: ");
  tft.println();

  //get moisture level from moisture sensor
  tft.println("Moisure Level:");
  tft.println(moisture_level);

  // get LED status from LDR sensor
  tft.println("LED Status: ");
  tft.println(led_status);

  
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