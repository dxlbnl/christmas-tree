
#pragma once

#include "program.h"

class Tree : public Program {
  CHSVPalette16 palette = CHSVPalette16(CHSV(80,200,50), CHSV(130,255,100), CHSV(80,200,255));
  int speed1 = 1230;
  int speed2 = 136;
  int speed3 = 500;

  public:
  Twinkle(VariantConstRef src) {
    this->palette = CHSVPalette16(src["color1"], src["color2"], src["color3"]);
    this->speed1 = src["speed1"];
    this->speed2 = src["speed2"];
    this->speed3 = src["speed3"];
  }
  bool checkJson(VariantConstRef src) {
    return (
      src["color1"].is<CSHV>() &&
      src["color2"].is<CSHV>() &&
      src["color3"].is<CSHV>() &&
      src["speed1"].is<int>() &&
      src["speed2"].is<int>() &&
      src["speed3"].is<int>()
    );
  }

  void config(JsonObject data) {
    this->palette = CHSVPalette16(data["color1"], data["color2"], data["color3"]);
    this->speed1 = data["speed1"];
    this->speed2 = data["speed2"];
    this->speed3 = data["speed3"];
  }
  void toJson(VariantRef dst) {
    dst["color1"] = this->palette[0];
    dst["color2"] = this->palette[7];
    dst["color3"] = this->palette[15];

    dst["speed1"] = this->speed1;
    dst["speed2"] = this->speed2;
    dst["speed3"] = this->speed3;
  }
  
  void tick() {
    for (int i=0; i<NUM_LEDS; i++) {
      float fi = (float) i;
      float m = millis();
      float w1 = sin(fi/100 + m/speed1);
      float w2 = sin(fi/10 - m/speed2);

      float w3 = sin(fi/50 + m/speed3);

      // leds[i] = ColorFromPalette(palette, positive(w1 + w2)*255);
      leds[i] = ColorFromPalette(palette, positive(w1 + w2) * positive(w3) * 255);
    }

  }
};
