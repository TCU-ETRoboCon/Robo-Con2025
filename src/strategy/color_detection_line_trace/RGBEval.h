#pragma once
#include "ColorEvaluationStrategy.h"
#include "ColorSensor.h"

class RGBEval : public ColorEvaluationStrategy {
public:
    RGBEval(ev3api::ColorSensor& sensor, int8_t target)
        : sensor(sensor), target(target) {}

    int8_t calculateError() const override {
        rgb_raw_t rgb;
        sensor.getRawColor(rgb);

        int8_t brightness = static_cast<int8_t>(
            0.2133 * rgb.r + 0.0171 * rgb.g + 0.3639 * rgb.b + 3.9663
        );

        return target - brightness;
    }

private:
    ev3api::ColorSensor& sensor;
    int8_t target;
};
