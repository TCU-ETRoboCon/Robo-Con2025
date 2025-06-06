#pragma once
#include "ColorEvaluationStrategy.h"
#include "ColorSensor.h"

class ReflectiveBrightnessEval : public ColorEvaluationStrategy {
public:
    ReflectiveBrightnessEval(ev3api::ColorSensor& sensor, int8_t target)
        : sensor(sensor), target(target) {}

    int8_t calculateError() const override {
        return target - sensor.getBrightness();
    }

private:
    ev3api::ColorSensor& sensor;
    int8_t target;
};
