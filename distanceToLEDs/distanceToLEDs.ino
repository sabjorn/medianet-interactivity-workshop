/*
    Based on the Adafruit NeoPixel strandtest example
    and the HC-SR04 example from how to www.HowToMechatronics.com
*/

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// HC-SR04
#define TRIGPIN 14
#define ECHOPIN 12

// Neopixels
#define LEDPIN 15
#define NUMLEDS 30

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMLEDS, LEDPIN, NEO_GRB + NEO_KHZ800);


// variables for HC-SR04
int distance;
double maximumDistance = 400.; // the maximum distance in CM

long oldTime = 0;
long updateRate = 100; // sets how often the sensor takes a reading

void setup() {
    pinMode(TRIGPIN, OUTPUT); // Sets the TRIGPIN as an Output
    pinMode(ECHOPIN, INPUT); // Sets the ECHOPIN as an Input
    
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'

    Serial.begin(115200); // Starts the serial communication
}

void loop() {
    long now = millis(); // measures how long since device started
    if((now - oldTime) > updateRate){
        distance = measureDistance();
        Serial.print("Distance (cm): ");
        Serial.println(distance);

        int normalized = (distance / maximumDistance) * 255; // make distance a value between 0, 255
        normalized = min(normalized, 255); // clamp value
        Serial.print("Distance (normalized): ");
        Serial.println(normalized);

        // update LEDs
        // colorWipe(Wheel(normalized), 10);

        int numLEDs = .3 * strip.numPixels(); // fill up 30% of LEDs
        fillLEDs(Wheel(normalized), numLEDs);

        numLEDs = (1 - .3) * strip.numPixels(); // fill remaining LEDs
        fillLEDs(Wheel(255 - normalized), numLEDs);

        // only update LEDs if we say so
        // this allows for multiple drawings to LEDs
        strip.show();

        oldTime = now; // we must update oldTime or else this will keep happening
    }
}

int measureDistance(){
    // Clears the TRIGPIN
    digitalWrite(TRIGPIN, LOW);
    delayMicroseconds(2);

    // Sets the TRIGPIN on HIGH state for 10 micro seconds
    digitalWrite(TRIGPIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGPIN, LOW);

    // Reads the ECHOPIN, returns the sound wave travel time in microseconds
    long duration = pulseIn(ECHOPIN, HIGH);

    // Calculating the distance and return
    return (duration * 0.034/2);
}

// simple way to set all LEDs.
void fillLEDs(uint32_t c, int numLEDs){
    for(uint16_t i=0; i<numLEDs; i++) {
        strip.setPixelColor(i, c);
    }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}