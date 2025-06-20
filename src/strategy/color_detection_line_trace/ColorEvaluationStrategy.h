#pragma once

class ColorEvaluationStrategy {
public:
    virtual ~ColorEvaluationStrategy() = default;

    /**
     * 誤差（目標値との差）を計算する
     * @return 誤差値（int8_t）
     */
    virtual int8_t calculateError() const = 0;
};
