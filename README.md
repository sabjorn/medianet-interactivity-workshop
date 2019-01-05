# Interactivity Workshop
## About
This repo exists as a resource to explore interactivity with microcontrollers. This code was originally created for the MediaNet interactive art workshop series in January 2019 but with the full understanding that it may be useful for others in the future.

The basic idea is to show a simple example of mapping and input and output between a sensor, a microcontroller, and a set of individually programmable RGB LEDs.

## Components
This project utilizes three main components:

### Arduino
Specifically, this project was designed to be used with the ESP8266 microcontroller. The Arduino framework is used because it allows for some cross-platform capabilities and will therefore allow this code to be used more broadly with different microcontrollers.

### WS2812 RGB LEDs
These LEDs were chosen for their ubiquity and relative inexpensiveness. Individually addressable LEDs allow for a wide range of output behaviour with only a small amount of knowledge. Furthermore, exploring colour space (e.g. RGB vs HSV) and array indexing is highly likely with this type of output (compared to an actuator like a solenoid, which has a small set of output states).

### HCSR04 Ultrasonic Rangefinder
This device was chosen because it is inexpensive and allows for a wide range of control options (e.g. threshold triggering, discrete region mapping, and 'continuous' control). Furthermore, these devices have a large maximum distance range, making them appropriate for use in human interaction.