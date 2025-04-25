#include "app.h"
#include "Tracer.h"
#include "Clock.h"

#include <stdio.h>

using namespace ev3api;

Tracer tracer;
Clock clock;
FILE *fp;

void tracer_task(intptr_t exinf) {

    fprintf(fp,"reflection:%d,right_motor:%d,left_motor:%d\n", tracer.colorSensor.getBrightness(), tracer.right_motor_power, tracer.left_motor_power);//書き込み

    tracer.run();
    ext_tsk();
}

void main_task(intptr_t unused) {
    const uint32_t duration = 100 * 1000;
    
    fp = fopen("reflection.txt","a"); //ファイルをオープン(名前の指定)
    if (fp == NULL) {
        printf("Failed to open file\n");
        ext_tsk();  // 終了
    }

    tracer.init();

    while(1){
    if(ev3_button_is_pressed(RIGHT_BUTTON)){
      break;
        }
    }
    sta_cyc(TRACER_CYC);

    while (!ev3_button_is_pressed(LEFT_BUTTON)) {
        clock.sleep(duration);
    }

    stp_cyc(TRACER_CYC);
    fclose(fp);
    tracer.terminate();
    ext_tsk();
}
