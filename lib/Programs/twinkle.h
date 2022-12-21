
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
#define TWINKLE_POINTS 30
#define TWINKLE_REFRESH_TIME 50
class Twinkle : public Program {
  CRGBW *leds;
  Point *points[TWINKLE_POINTS];
  int index = 0;

  public:
  Twinkle(CRGBW *leds) {
    this->leds = leds;
    for (int i=0; i<TWINKLE_POINTS; i++) {
      points[i] = new Point();
    }
  }
  
  void tick() {

    EVERY_N_MILLIS(TWINKLE_REFRESH_TIME) {
      points[index++]->reset();

      index %= TWINKLE_POINTS;
    }
    
    for (int i=0; i<TWINKLE_POINTS; i++) {
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
