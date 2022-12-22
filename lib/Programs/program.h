#pragma once
#include "FastLED.h"
#include "RGBW.h"

class Program {
  public:

  virtual void tick();
};



float positive(float value) {
	return value > 0 ? value : 0;
}

