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

void Tracer::run() {
	rgb_raw_t rgb; //rgb値の格納場所
	colorSensor.getRawColor(rgb); //rgb値取得

	int8_t pBrightness = round(0.2133 * rgb.r + 0.0171 * rgb.g + 0.3639 * rgb.b + 3.9663);

	int8_t err = target - pBrightness; //誤差(目標値-反射光)

	int8_t pControl = err * Kp; //比例制御の値

	int8_t err_sum = 0; //目標値の差の合計
	err_sum += err; //しきい値の差の合計＋しきい値の差
	int8_t iControl = err_sum * Ki; //積分制御の値

	static int8_t prev_err = 0; //1つ前の目標値
	int8_t dControl = (err - prev_err) * Kd; //微分制御の値
	prev_err = err; //1つ前の目標値の差を更新

	int8_t controlTotal = (LEFT_EDGE) * (pControl + iControl + dControl); //制御値の合計

	msg_f("running...", 1);
	right_motor_power = BASE_SPEED + controlTotal; //パワー＋制御値の合計
	left_motor_power = BASE_SPEED - controlTotal; //パワーー制御の値の合計
	rightWheel.setPWM(right_motor_power);
	leftWheel.setPWM(left_motor_power);
}
