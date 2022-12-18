
#include "FastLED.h"

#include "RGBW.h"
#include "waves.h"
// #include "trickle.h"

#define NUM_LEDS      300
#define LED_TYPE   SK6812
#define DATA_PIN        15
//#define CLK_PIN       4
#define VOLTS          5
#define MAX_MA       10000

CRGBW leds[NUM_LEDS];
CRGB *ledsRGB = (CRGB *) &leds[0];

Waves *waves;
// Trickle *trickle;

void setup() {
  delay( 3000 ); //safety startup delay
  FastLED.setMaxPowerInVoltsAndMilliamps( VOLTS, MAX_MA);
  FastLED.addLeds<LED_TYPE, DATA_PIN, RGB>(ledsRGB, getRGBWsize(NUM_LEDS))
    .setCorrection(TypicalLEDStrip);

	waves = new Waves(leds);
	// trickle = new Trickle(leds);
}



void loop(){
	FastLED.clearData();

	waves->tick();

	FastLED.show();
}