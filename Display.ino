#include <TFT.h>
#include <SPI.h>
#include <Adafruit_ILI9341.h>

/*
T_DO, SDO(MISO): GREY     10
T_DIN, SDI(MOSI): GREEN   9
T_CS: WHITE               4
TFT_CS: YELLOW            5
T_CK, SCK: PURPLE         7
LED, VCC: RED             5.5v
DC: BLUE                  6
RESET: ORANGE             8
GND: BLACK                GND 
*/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9400);
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
