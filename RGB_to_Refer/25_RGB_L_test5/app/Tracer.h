#include "Motor.h"
#include "ColorSensor.h"
#include "util.h"
#include "SonarSensor.h"

#define WHITE_BRIGHTNESS 90
#define BLACK_BRIGHTNESS 6

#define RIGHT_EDGE -1 //右側エッジ(clockwise)  
#define LEFT_EDGE 1 //左側エッジ(anti-clockwise)　こっちの方が安定

using namespace ev3api;

class Tracer {
public:
	Tracer();
	void run();
	void init();
	void terminate();
	ColorSensor colorSensor;
	SonarSensor sonarSensor;
	int8_t right_motor_power = 0; //右モーターのパワー
	int8_t left_motor_power = 0; //左モーターのパワー	
private:
	Motor leftWheel;
	Motor rightWheel;
	const int8_t target = (WHITE_BRIGHTNESS + BLACK_BRIGHTNESS) / 2; //目標値
	const float Kp = 0.57; // Pゲイン
	const float Ki = 0.09; //Iゲイン
	const float Kd = 0.69; //Dゲイン

	

#ifndef MAKE_RASPIKE
	const int8_t BASE_SPEED = 40; // モーターの初期パワー
#else
	const int8_t BASE_SPEED = 40;
#endif
};
