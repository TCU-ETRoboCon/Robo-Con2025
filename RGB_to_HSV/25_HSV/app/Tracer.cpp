#include "Tracer.h"
#include <cmath>

Tracer::Tracer() :
	leftWheel(PORT_C), rightWheel(PORT_B), colorSensor(PORT_2), sonarSensor(PORT_3) {
}

void Tracer::init() {
	init_f("Tracer");
}

void Tracer::terminate() {
	msg_f("Stopped.", 1);
	leftWheel.stop();
	rightWheel.stop();
}

// RGBをHSVに変換して青を検出
bool Tracer::isBlueColor(rgb_raw_t rgb) {
    float r = rgb.r / 255.0;
    float g = rgb.g / 255.0;
    float b = rgb.b / 255.0;

    float max = r;
	if(max < g) max = g;
	if(max < b) max = b;

    float min = r;
	if(min > g) min = g;
	if(min > b) min = b;

    float diff = max - min;

    float h = 0.0;
    if (diff != 0) {
        if (max == r)
            h = fmod((60 * ((g - b) / diff) + 360), 360);
        else if (max == g)
            h = fmod((60 * ((b - r) / diff) + 120), 360);
        else
            h = fmod((60 * ((r - g) / diff) + 240), 360);
    }

    float s = (max == 0) ? 0 : (diff / max);
    float v = max;

    // 青と判定する条件（しきい値は環境に応じて調整可）
    return (h >= 200 && h <= 260 && s >= 0.4 && v >= 0.2);
}

void Tracer::run() {
	rgb_raw_t rgb; //rgb値の格納場所
	colorSensor.getRawColor(rgb); //rgb値取得

	if(isBlueColor(rgb)){
		terminate();
		return;
	}
	int8_t pBrightness = round(0.2133 * rgb.r + 0.0171 * rgb.g + 0.3639 * rgb.b + 3.9663);

	int8_t err = target - pBrightness; //誤差(目標値-反射光)

	int8_t pControl = err * Kp; //比例制御の値

	int8_t err_sum = 0; //目標値の差の合計
	err_sum += err; //しきい値の差の合計＋しきい値の差
	int8_t iControl = err_sum * Ki; //積分制御の値

	static int8_t prev_err = 0; //1つ前の目標値x
	int8_t dControl = (err - prev_err) * Kd; //微分制御の値
	prev_err = err; //1つ前の目標値の差を更新

	int8_t controlTotal = (LEFT_EDGE) * (pControl + iControl + dControl); //制御値の合計

	msg_f("running...", 1);
	right_motor_power = BASE_SPEED + controlTotal; //パワー＋制御値の合計
	left_motor_power = BASE_SPEED - controlTotal; //パワーー制御の値の合計
	rightWheel.setPWM(right_motor_power);
	leftWheel.setPWM(left_motor_power);

	
}
