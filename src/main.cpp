

#include "FastLED.h"
#include "RGBW.h"

#define LED_TYPE   SK6812
#define DATA_PIN     13
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

	// for (int i=0; i<NUM_LEDS; i++) {
	// 	leds[i] = CRGB::Yellow;
	// 	delay(10);
	// 	FastLED.show();
	// }
	// delay(100);
	// for (int i=0; i<NUM_LEDS; i++) {
	// 	leds[i] = CRGB::Red;
	// 	delay(10);
	// }
	// delay(100);

	tree->tick();
	redtrickle->tick();
	twinkle->tick();
	// trickle->tick();
	FastLED.show();
}


void setup() {
  delay( 300 ); //safety startup delay

  Serial.begin(115200);
  while (!Serial);

  delay(200);

	Serial.println("Setting up wifi");
	wifiSetup();
	
	Serial.println("Setting up server");
	serverSetup();

	Serial.println("Setting up leds");
	ledsSetup();
}

void loop(){
	wifiLoop();
	serverLoop();

	ledsLoop();
}