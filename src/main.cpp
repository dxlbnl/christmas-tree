

#include "FastLED.h"
#include "RGBW.h"

#define LED_TYPE   SK6812
#define DATA_PIN     13
//#define CLK_PIN       4
#define VOLTS          5
#define MAX_MA       10000
#define NUM_LEDS      300


static CRGBW leds[NUM_LEDS];
static CRGB *ledsRGB = (CRGB *) &leds[0];

#include "wifi.h"
#include "scene.h"

Scene *scene = new Scene({
	{"tree", new Tree()},
	{"trickle", new RedTrickle()},
	{"twinkle", new Twinkle()},
});
#include "server.h"

void ledsSetup() {
  FastLED.setMaxPowerInVoltsAndMilliamps( VOLTS, MAX_MA);
  FastLED.addLeds<LED_TYPE, DATA_PIN, RGB>(ledsRGB, getRGBWsize(NUM_LEDS))
    .setCorrection(TypicalLEDStrip);

	scene->setup();
}

void ledsLoop() {
	scene->tick();
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