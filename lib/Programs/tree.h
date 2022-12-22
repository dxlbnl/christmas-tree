
#pragma once

#include "program.h"

class Tree : public Program {
  CRGBW *leds;
  CHSVPalette16 palette = CHSVPalette16(CHSV(80,200,50), CHSV(130,255,100), CHSV(80,200,255));
  int speed1 = 1230;
  int speed2 = 136;
  int speed3 = 500;

  public:
  Tree(CRGBW *leds) {
    this->leds = leds;
  }

  void config(CHSV color1, CHSV color2, CHSV color3, int speed1, int speed2, int speed3) {
    this->palette = CHSVPalette16(color1, color2, color3);
    this->speed1 = speed1;
    this->speed2 = speed2;
    this->speed3 = speed3;
  }
  
  void tick() {
    for (int i=0; i<NUM_LEDS; i++) {
      float fi = (float) i;
      float m = millis();
      float w1 = sin(fi/100 + m/speed1);
      float w2 = sin(fi/10 - m/speed2);

      float w3 = sin(fi/200 + m/speed3);

      // leds[i] = ColorFromPalette(palette, positive(w1 + w2)*255);
      leds[i] = ColorFromPalette(palette, positive(w1 + w2) * positive(w3) * 255);
    }

  }
};
