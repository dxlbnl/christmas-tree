#include "program.h"
#include "Animation.h"
#include "FastLED.h"

class Cyclon : public Program {
    Animator animations = Animator(2);
    uint16_t lastPixel = 0; // track the eye position
    int8_t moveDir = 1; // track the direction of movement
    AnimEaseFunction moveEase =
    //      Ease::Linear;
    //      Ease::QuadraticInOut;
    //      Ease::CubicInOut;
            // Ease::QuarticInOut;
    //      Ease::QuinticInOut;
         Ease::SinusoidalInOut;
    //      Ease::ExponentialInOut;
    //      Ease::CircularInOut;

    uint8_t fadeAmount[NUM_LEDS];

     void FadeAnimUpdate(const AnimationParam& param)
    {
        if (param.state == AnimationState_Completed)
        {
            for (int i=0; i<NUM_LEDS; i++) {
                leds[i].nscale8(255 - fadeAmount[i]);
            }

            animations.RestartAnimation(param.index);
        }
    }

    void MoveAnimUpdate(const AnimationParam& param)
    {
        // apply the movement animation curve
        float progress = moveEase(param.progress);

        // use the curved progress to calculate the pixel to effect
        uint16_t nextPixel;
        if (moveDir > 0)
        {
            nextPixel = progress * NUM_LEDS;
        }
        else
        {
            nextPixel = (1.0f - progress) * NUM_LEDS;
        }

        // if progress moves fast enough, we may move more than
        // one pixel, so we update all between the calculated and
        // the last
        uint8_t hue = ((float) millis()) / 20;
        CHSV color(hue, 255, 255);
        if (lastPixel != nextPixel)
        {
            for (uint16_t i = lastPixel + moveDir; i != nextPixel; i += moveDir)
            {
                leds[i] = color;
            }
        }
        leds[nextPixel] = color;
        if (random8() > 150) {
            leds[nextPixel].white = random8();
        }
        

        lastPixel = nextPixel;
        Serial.printf("Pixel: %d\n", lastPixel);

        if (param.state == AnimationState_Completed)
        {
            // reverse direction of movement
            moveDir *= -1;

            // done, time to restart this position tracking animation/timer
            animations.RestartAnimation(param.index);

            for (int i=0; i<NUM_LEDS; i++) {
                fadeAmount[i] = random8(6, 15);
            }
        }
    }

    public:

    Cyclon() {
        // fade all pixels providing a tail that is longer the faster
        // the pixel moves.
        Serial.println("Setup animations");
        animations.StartAnimation(0, 5, [this] (const AnimationParam& param) { this->FadeAnimUpdate(param); });

        // take several seconds to move eye fron one side to the other
        animations.StartAnimation(1, 3000, [this] (const AnimationParam& param) { this->MoveAnimUpdate(param);} );
    };
    void tick() {
        animations.UpdateAnimations();
    };
    void setConfig(JsonObject config) {}
    void getConfig(JsonObject config) {}
};
