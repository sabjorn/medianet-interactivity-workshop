#ifdef __AVR__
  #include <avr/power.h>
#endif

#include <FastLED.h>

// HC-SR04
#define TRIG_PIN 14
#define ECHO_PIN 12
#define MAX_DIST 50

// Neopixels
#define LED_PIN 23
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

  // update LEDs
  int numLedsToLight = map(distance, 0, MAX_DIST, 0, NUM_LEDS);
  numLedsToLight = min(numLedsToLight, NUM_LEDS);
  Serial.print("Distance (normalized): ");
  Serial.println(numLedsToLight);

  // First, clear the existing led values
  FastLED.clear();
  for(int led = 0; led < numLedsToLight; led++) { 
      leds[led] = CRGB::Blue; 
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