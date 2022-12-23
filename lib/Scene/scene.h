#pragma once
#include <map>
#include <string>

#include "program.h"


#include "waves.h"
#include "trickle.h"
#include "redtrickle.h"
#include "palette.h"
#include "tree.h"
#include "twinkle.h"

class Scene {
  std::map<std::string, Program*> programs;

  public:
    Scene(std::map<std::string, Program*> programs) {
      this->programs = programs;
    }
    void add(std::string name, Program *program) {
      programs[name] = program;
    }
    Program* get(std::string name) {
      return programs[name];
    }
     
    void tick() {
      FastLED.clearData();

      for(auto &[name, program]: programs) {
        program->tick();
      }

      FastLED.show();
    }
};

// #include "ArduinoJson.h"

// namespace ARDUINOJSON_NAMESPACE {
// template <>
// struct Converter<Scene> {
//   static void toJson(const CRGB& src, VariantRef dst) {
//     dst["r"] = src.r;
//     dst["g"] = src.g;
//     dst["b"] = src.b;
//   }

//   static CRGB fromJson(VariantConstRef src) {
//     return CRGB(src["r"], src["g"], src["b"]);
//   }

//   static bool checkJson(VariantConstRef src) {
//     return src["r"].is<uint8_t>() && src["g"].is<uint8_t>() && src["b"].is<uint8_t>();
//   }
// };
// }