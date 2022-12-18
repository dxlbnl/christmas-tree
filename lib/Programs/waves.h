#pragma once

#include "wave.h"

#define N_WAVES 15

class Waves : public Program {
  Wave *waves[N_WAVES];

  public:
  Waves(CRGBW *leds) {
    for (int i=0;i <N_WAVES; i++) {
      waves[i] = new Wave(leds);
      waves[i]->setup();
    }
  }

  void setup() {
  }

  void tick() {
    for (int i=0;i <N_WAVES; i++) {
      waves[i]->tick();
    }
  }
};
