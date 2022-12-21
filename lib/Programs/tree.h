
#pragma once

#include "program.h"

class Tree : public Program {
  CRGBW *leds;
  CHSVPalette16 palette = CHSVPalette16(CHSV(80,200,30), CHSV(130,255,100));

  public:
  Tree(CRGBW *leds) {
    this->leds = leds;
  }
  
  void tick() {
    for (int i=0; i<NUM_LEDS; i++) {
      float fi = (float) i;
      float m = millis();
      float w1 = sin(fi + m/123);
      float w2 = sin(fi/10 - m/136) ;

      float w3 = sin(fi/5 + m/500);

      leds[i] = ColorFromPalette(palette, positive(w1 + w2) * positive(w3) * 255);
    }

  }
};
