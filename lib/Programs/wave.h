
#pragma once

#include "program.h"
#include "FastLED.h" 
#include "RGBW.h"

CHSVPalette16 palette = CHSVPalette16(CHSV(160,255,51), CHSV(0,255,100),  CHSV(120,255,100), CHSV(250,255,51));


class Wave : public Program {
  CRGBW *leds;
  int num_leds;

	int pos = 0;
	int width = 10;
	int speed = 10;
	int speed_i =0;
	CHSV color = CHSV(0,255,255);

	public:
  Wave(CRGBW *leds) {
    this->leds = leds;
    num_leds = sizeof(leds) / sizeof(leds[0]);
  }
	void setup() {
		pos = 0;
		width = random8(10) + 1;
		color = ColorFromPalette(palette, random8());
		speed = random8(10) + 1;
		speed_i = 0;
	}

	void tick() {
		wave(pos, width, color);

		if (pos > num_leds) {
			setup();
		}

		if (speed_i == 0) {
			pos ++;
		}
		speed_i = ++speed_i % speed;
	}

  void wave(int pos, int period, CHSV color) {
    float step = (float) 255 / period;

    for (int i=0; i<period; i++) {
      CHSV c = CHSV(color);
      c.value = sin8(i * step);
      leds[i + pos % num_leds] = c;
    }
  }

};