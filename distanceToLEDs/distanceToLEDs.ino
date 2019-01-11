#ifdef __AVR__
  #include <avr/power.h>
#endif

#include <FastLED.h>

// HC-SR04
#define TRIG_PIN 2
#define ECHO_PIN 16
#define MAX_DIST 50

// Neopixels
#define LED_PIN 0
#define NUM_LEDS 16

CRGB leds[NUM_LEDS]; // Define the array of leds

void setup() {
    pinMode(TRIG_PIN, OUTPUT); // Sets the TRIG_PIN as an Output
    pinMode(ECHO_PIN, INPUT); // Sets the ECHO_PIN as an Input
    
    FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);

    Serial.begin(115200); // Starts the serial communication
}

void loop() {
  int distance = measureDistance();
  Serial.print("Distance (cm): ");
  Serial.println(distance);

  // set LED colour based on 'thesholding'
  //
  CRGB color;
  int threshold = 20;
  int numLedsToLight = NUM_LEDS;
  if(distance < threshold){
    // set one colour for this threshold
    color = CRGB(255, 0, 0); // red
  }
  else{
    // set to other colour when not past threshold
    color = CRGB(0, 255, 0); // blue
  }

  // Set number of LEDs based on distance
  // "continuous"
  //
  // CRGB color(255, 0, 0); // red
  // int numLedsToLight = map(distance, 0, MAX_DIST, 0, NUM_LEDS);
  // Serial.print("Distance (normalized): ");
  // Serial.println(numLedsToLight);

  // Set HUE of LEDS based on distance
  //
  // int numLedsToLight = NUM_LEDS;
  // int max_val = 255; // we need a value between 0 and max_val
  // int hue = map(distance, 0, MAX_DIST, 0, max_val);
  // CHSV color(hue, 255, 255); // Hue, Saturation, Value

  // First, clear the existing led values
  FastLED.clear();
  for(int led = 0; led < numLedsToLight; led++) { 
      leds[led] = color;
  }
  FastLED.show();

  delay(10);
}

int measureDistance(){
    // Clears the TRIG_PIN
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    // Sets the TRIG_PIN on HIGH state for 10 micro seconds
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Reads the ECHO_PIN, returns the sound wave travel time in microseconds
    long duration = pulseIn(ECHO_PIN, HIGH);

    // Calculating the distance and return
    return (duration * 0.034/2);
}