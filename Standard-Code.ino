// Arduino Nano Standard Layout
// Used with Arduino Nano
// By Jeremy S. Cook 3/18/2019
//
// Includes code from:
// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// How many NeoPixels are attached to the Arduino?
#define PINRGB 3
#define NUMPIXELSRGB   2
Adafruit_NeoPixel pixelsRGB = Adafruit_NeoPixel(NUMPIXELSRGB, PINRGB, NEO_RGB + NEO_KHZ800);

int DIP9 = 0;
int DIP10 = 0;
int DIP11 = 0;
int DIP12 = 0;
int PIR = 0;

void setup() {
  pinMode(7, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  
  pixelsRGB.begin(); // This initializes the NeoPixel library as pixelsRGB object.
  Serial.begin(9600);
}

void loop() {

PIR = analogRead(A6);
DIP9 = digitalRead(9);
DIP10 = digitalRead(10);
DIP11 = digitalRead(11);
DIP12 = digitalRead(12);

Serial.print("PIR  ");
Serial.println(PIR);
Serial.print("DIP9 ");
Serial.println(DIP9);

if (DIP9 == LOW && PIR > 100){
  Serial.println("button pressed => random");
  int randomGreen = random(50, 256);
  int randomRed = random(50, 256);
  int randomBlue = random(50, 256);
  if (randomGreen < randomRed && randomGreen < randomBlue) randomGreen = 0;
  if (randomRed < randomGreen && randomRed < randomBlue) randomRed = 0;
  if (randomBlue < randomRed && randomBlue < randomGreen) randomBlue = 0; 
  pixelsRGB.setPixelColor(0, pixelsRGB.Color(randomGreen,randomRed,randomBlue)); //sets random color and light - note GRB strip
  pixelsRGB.show();
  delay(250);
}

else if (DIP10 == LOW && PIR > 100){
  Serial.println("button pressed");
  for (int i = 0; i < 5; i++) {
  pixelsRGB.setPixelColor(0, pixelsRGB.Color(0,200,0)); // Green/Red/Blue
  pixelsRGB.show(); // This sends the updated pixel color to the hardware.  
  delay(250);
  pixelsRGB.setPixelColor(0, pixelsRGB.Color(0,0,200)); // Green/Red/Blue
  pixelsRGB.show(); // This sends the updated pixel color to the hardware.  
  delay(250); 
  }
}
else{
  pixelsRGB.setPixelColor(0, pixelsRGB.Color(0,0,0));
  pixelsRGB.show();
}
}
