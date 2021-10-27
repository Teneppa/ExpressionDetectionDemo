/*
 This example is made for my 10x8 neopixel matrix badge, but feel free to modify
 this to fit your application.
*/

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#define PIN 2
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(10, 8, PIN,
                            NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
                            NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
                            NEO_GRB            + NEO_KHZ800);

char *color = NULL;

uint8_t currentR = 0;
uint8_t currentG = 0;
uint8_t currentB = 0;

uint8_t targetR = 0;
uint8_t targetG = 0;
uint8_t targetB = 0;

void setup() {
  Serial.begin(115200);

  matrix.begin();
  matrix.setBrightness(110);
  matrix.fillScreen(0);
  matrix.show();
}

long oldMsgTime = 0;
uint8_t rgb[3];
unsigned long oldUpdate = 0;
void loop() {

  if (millis() - oldUpdate > 10) {
    if(currentR < targetR) {
      currentR++;
    }
    if(currentG < targetG) {
      currentG++;
    }
    if(currentB < targetB) {
      currentB++;
    }

    if(currentR > targetR) {
      currentR--;
    }
    if(currentG > targetG) {
      currentG--;
    }
    if(currentB > targetB) {
      currentB--;
    }
    
    matrix.fillScreen(matrix.Color(currentR, currentG, currentB));
    matrix.show();
    
    oldUpdate = millis();
  }

  if (Serial.available() > 0) {
    oldMsgTime = millis();

    String str = Serial.readStringUntil(';');
    Serial.flush();

    char carray[12];
    str.toCharArray(carray, 12);
    
    color = strtok(carray, ",");
    
    uint8_t i = 0;
    
    while (color != NULL) {
      rgb[i] = String(color).toInt();
      i++;
      Serial.println(color);
      color = strtok(NULL, ",");
    }  

    Serial.println("R:"+String(rgb[0])+" G:"+String(rgb[1])+" B:"+String(rgb[2]));

    targetR = rgb[0];
    targetG = rgb[1];
    targetB = rgb[2];
  }
}
