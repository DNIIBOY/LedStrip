#include <FastLED.h>
#define LED_PIN1 2
#define LED_PIN2 3
#define NUM_LEDS 150
#define BLOCKS 1
#define ADDRESS 1
#define MAX_ADDRESS ADDRESS + BLOCKS * 3 - 1
#define BLOCK_SIZE NUM_LEDS / BLOCKS

CRGB strip1[NUM_LEDS];
CRGB strip2[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2813, LED_PIN1, GRB>(strip1, NUM_LEDS);
  FastLED.addLeds<WS2813, LED_PIN2, GRB>(strip2, NUM_LEDS);
  Serial.begin(9600);
  Serial.print("Address: ");
  Serial.println(ADDRESS);
  Serial.print("Ending address: ");
  Serial.println(MAX_ADDRESS);
  Serial.print("Channels: ");
  Serial.println(BLOCKS*3);
  Serial.print("Block size: ");
  Serial.println(BLOCK_SIZE);
}

int readDMX(int address){
  // TODO
  return 255;
}

void loop() {
  for (int i = 0; i < BLOCKS; i++){
    int blockAddress = ADDRESS + (i*3);
    int red = readDMX(blockAddress);
    int green = readDMX(blockAddress+1);
    int blue = readDMX(blockAddress+2);
    for (int led = ADDRESS+i*3; led < ADDRESS+BLOCK_SIZE; led++){
      strip1[led] = CRGB(red, green, blue);
    }
  }
  FastLED.show();
  for (int i = 0; i < BLOCKS; i++){
    int blockAddress = ADDRESS+BLOCKS*3 + (i*3);
    int red = readDMX(blockAddress);
    int green = readDMX(blockAddress+1);
    int blue = readDMX(blockAddress+2);
    for (int led = ADDRESS+i*3; led < ADDRESS+BLOCK_SIZE; led++){
      strip2[led] = CRGB(red, green, blue);
    }
  }
  FastLED.show();
}