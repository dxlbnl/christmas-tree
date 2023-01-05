#include "map"
#include "FastLED.h"
#include "RGBW.h"

#define LED_TYPE   SK6812
#define DATA_PIN     13
#define VOLTS          5
#define MAX_MA       10000
#define NUM_LEDS      300

static CRGBW leds[NUM_LEDS];
static CRGB *ledsRGB = (CRGB *) &leds[0];

#include "wifi.h"
#include "scene.h"
#include "Cyclon.h"
#include "webserver.h"

class MainPrograms : public MainControl {
    std::map<std::string, Program*> programs;
    Program *cur;
public:
    MainPrograms()
        : cur(nullptr)
    {
			programs["Wavy"] = new Scene({
				{"tree", new Tree()},
				{"trickle", new RedTrickle()},
				{"twinkle", new Twinkle()},
			});
        programs["Cyclon"] = new Cyclon();
        this->setCurrentProgram("Cyclon");
    }

    bool setCurrentProgram(const std::string& name) override
    {
        auto i = programs.find(name);
        if (i == programs.end())
            return false;

        cur = i->second;
        return true;
    }
    const std::string getCurrentProgram()
    {
        for (auto &i: programs) {
            if (i.second == cur) {
                return i.first;
            }
        }
    }
    std::vector<std::string> getPrograms() override
    {
        std::vector<std::string> v;
        for (auto kv : programs)
            v.emplace_back(kv.first);
        return v;
    }

    Program* current()
    {
        return cur;
    }

    void loop()
    {
        if (cur) {
            cur->tick();
            FastLED.show();
        }
    }
};

MainPrograms programs;
LightServer webserver(&programs);

void ledsSetup() {
  FastLED.setMaxPowerInVoltsAndMilliamps( VOLTS, MAX_MA);
  FastLED.addLeds<LED_TYPE, DATA_PIN, RGB>(ledsRGB, getRGBWsize(NUM_LEDS));
    // .setCorrection(TypicalLEDStrip);
}

void setup() {
  delay( 300 ); //safety startup delay

  Serial.begin(115200);
  while (!Serial);

  delay(200);

	Serial.println("Setting up wifi");
	wifiSetup();
	
	Serial.println("Setting up server");
	webserver.setup();

	Serial.println("Setting up leds");
	ledsSetup();

	programs.setCurrentProgram("Christmas");
}


void loop(){
	wifiLoop();
	webserver.loop();

	programs.loop();
}
