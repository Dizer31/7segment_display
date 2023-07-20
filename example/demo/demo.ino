#include "7segment_display.h"

uint8_t dot = 13;
uint8_t segments[] = { 6,7,8,9,10,11,12 }; //пины сегментов (A B C D E F G)
uint8_t anod[] = { 5,4,3,2 };  //пины разрядов
uint8_t nAnod = sizeof(anod) / sizeof(uint8_t); //нужно если не четырёхразрядный 7-сегментный индикатор

void setup() {
    Serial.begin(9600);
    disp.init(segments, anod, nAnod, dot);
}

void loop() {
    tick();
    qw();
}

void tick(){
    static uint32_t tmr = 0;
    static bool flag = 0;
    if(millis() - tmr > 500){
        tmr = millis();
        flag =!flag;
        disp.point(flag);
    }
}

void qw(){
    int16_t arr[] = {_h, _e, _l, _l};
    disp.printChar(arr);
    delay(1000);
    
    disp.print(1234);
    delay(1000);
}