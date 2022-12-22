#pragma once

#include "program.h"

class Point {
  public:
  int pos;
  uint8_t value;

  Point () {
    reset();
  }

  void reset() {

    pos = random(NUM_LEDS);
    value = random8(100);
  }
  
};
#define TWINKLE_POINTS 150
#define TWINKLE_REFRESH_TIME 50
class Twinkle : public Program {
  CRGBW *leds;
  Point *points[TWINKLE_POINTS];
  int index = 0;
  uint8_t count = 30;

  public:
  Twinkle(CRGBW *leds) {
    this->leds = leds;
    for (int i=0; i<TWINKLE_POINTS; i++) {
      points[i] = new Point();
    }
  }

  void setCount(uint8_t c) {
    count = c;
  }
  
  void tick() {
    if (!count) return;

    EVERY_N_MILLIS(TWINKLE_REFRESH_TIME) {
      points[index++]->reset();

      index %= count;
    }
    
    for (int i=0; i<count; i++) {
      Point *point = points[i];
      if (point->value == 255) {
        point->value = random8(100);
      } else if (point->value > 5) {
        point->value -= 4;
      } else {
        point->value = 255;
      }
      
      leds[point->pos].white = point->value;
    }
  }
};
