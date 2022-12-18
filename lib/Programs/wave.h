
#pragma once

#include "program.h"
#include "FastLED.h" 
#include "RGBW.h"

CHSVPalette16 palette = CHSVPalette16(CHSV(160,255,51), CHSV(0,255,100),  CHSV(120,255,100), CHSV(250,255,51));


class Wave : public Program {
  CRGBW *leds;

	int pos = 0;
	int width = 10;
	int speed = 10;
	int speed_i =0;
	CHSV color = CHSV(0,255,255);

	public:
  Wave(CRGBW *leds) {
    this->leds = leds;
    setup();
    pos = random8(NUM_LEDS);
  }
	void setup() {
		pos = 0;
		width = random8(10) + 1;
		color = ColorFromPalette(palette, random8());
		speed = random8(10) + 1;
		speed_i = 0;
	}

	void tick() {
    float step = M_PI / width;

    for (int i=0; i<width; i++) {
      CHSV c = CHSV(color);
      c.value = sin(i * step) * 255;
      leds[i + pos % NUM_LEDS] = c;
    }

		if (pos > NUM_LEDS) {
			setup();
		}

		if (speed_i == 0) {
			pos ++;
		}
		speed_i = ++speed_i % speed;
	}
};