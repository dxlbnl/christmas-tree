#pragma once
#include "FastLED.h"
#include "RGBW.h"

class Program {
  public:

  virtual void tick();
  virtual void config(JsonObject);

  virtual void toJson(VariantRef dst);
  virtual bool checkJson(VariantConstRef src);
};

namespace ARDUINOJSON_NAMESPACE {
template <>
struct Converter<Program> {
  static void toJson(const Program& src, VariantRef dst) {
    src->toJson(dst);
  }

  static Program fromJson(VariantConstRef src) {
    return CRGB(src["r"], src["g"], src["b"]);
  }

  static bool checkJson(VariantConstRef src) {
    return src["r"].is<uint8_t>() && src["g"].is<uint8_t>() && src["b"].is<uint8_t>();
  }
};
}



float positive(float value) {
	return value > 0 ? value : 0;
}

