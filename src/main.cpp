

#include "FastLED.h"
#include "RGBW.h"

#define LED_TYPE   SK6812
#define DATA_PIN        15
//#define CLK_PIN       4
#define VOLTS          5
#define MAX_MA       10000
#define NUM_LEDS      300

#include "wifi.h"

#include "waves.h"
#include "trickle.h"
#include "redtrickle.h"
#include "palette.h"
#include "tree.h"
#include "twinkle.h"


CRGBW leds[NUM_LEDS];
CRGB *ledsRGB = (CRGB *) &leds[0];

Waves *waves = new Waves(leds);
Trickle *trickle = new Trickle(leds);
Palette *palette = new Palette(leds);
Tree *tree = new Tree(leds);
Twinkle *twinkle = new Twinkle(leds);

#include "server.h"


void ledsSetup() {

  FastLED.setMaxPowerInVoltsAndMilliamps( VOLTS, MAX_MA);
  FastLED.addLeds<LED_TYPE, DATA_PIN, RGB>(ledsRGB, getRGBWsize(NUM_LEDS))
    .setCorrection(TypicalLEDStrip);

	redtrickle = new RedTrickle(leds);

}

void ledsLoop() {
	FastLED.clearData();

	tree->tick();
	redtrickle->tick();
	twinkle->tick();
	// trickle->tick();

	FastLED.show();
}


void setup() {
  delay( 1000 ); //safety startup delay
	
	wifiSetup();
	serverSetup();

	ledsSetup();
}

void loop(){
	wifiLoop();
	serverLoop();

	ledsLoop();
}