#include "Motor.h"
#include "ColorSensor.h"
#include "util.h"
#include "SonarSensor.h"


#define WHITE_BRIGHTNESS 90
#define BLACK_BRIGHTNESS 6

#define RIGHT_EDGE -1 //右側エッジ(clockwise)  
#define LEFT_EDGE 1 //左側エッジ(anti-clockwise)　こっちの方が安定

#include "../color_detection_line_trace/ColorEvaluationStrategy.h" // 色認識のインターフェース

using namespace ev3api;

class Tracer {
public:
	Tracer(ColorEvaluationStrategy* evaluator);
	void run();
	void init();
	void terminate();
	ev3api::ColorSensor colorSensor;
	int8_t right_motor_power = 0; //右モーターのパワー
	int8_t left_motor_power = 0; //左モーターのパワー	
private:
	ColorEvaluationStrategy* colorEvaluator;
	ev3api::Motor leftWheel;
	ev3api::Motor rightWheel;
	ev3api::SonarSensor sonarSensor;
	const int8_t target = (WHITE_BRIGHTNESS + BLACK_BRIGHTNESS) / 2; //目標値
	const float Kp = 0.4; // Pゲイン
	const float Ki = 0.01; //Iゲイン
	const float Kd = 0.73; //Dゲイン

	

#ifndef MAKE_RASPIKE
	const int8_t BASE_SPEED = 35; // モーターの初期パワー
#else
	const int8_t BASE_SPEED = 35;
#endif
};
