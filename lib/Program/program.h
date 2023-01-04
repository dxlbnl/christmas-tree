#pragma once

#include "ArduinoJson.h"

class Program {
  public:
  virtual void tick() = 0;
  virtual void setConfig(JsonObject);
  virtual void getConfig(JsonObject);
  
};


float positive(float value) {
	return value > 0 ? value : 0;
}

