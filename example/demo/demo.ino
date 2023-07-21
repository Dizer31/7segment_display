#include "7segment_display.h"

//-----setting-----//
#define invertS 1
#define invertA 1
//-----setting-----//

uint8_t dot = 13; //пин точки
uint8_t segments[] = { 6,7,8,9,10,11,12 }; //пины сегментов (A B C D E F G)
uint8_t anod[] = { 5,4,3,2 };  //пины разрядов
uint8_t nAnod = sizeof(anod) / sizeof(uint8_t); //нужно если не четырёхразрядный 7-сегментный индикатор

void setup() {
    disp.init(segments, anod, nAnod, dot);
    disp.setBrightness(24);
}

void loop() {
    disp.print(1234);
    disp.setBrightness(5);
    delay(1000);
    
    disp.setBrightness(24);
    delay(1000);

    disp.setBrightness(5);
    delay(1000);
    
    disp.setBrightness(24);
    delay(1000);
    
    for (uint8_t j = 0;j < 2;j++){
        for (uint8_t i = 0;i < nAnod;i++){
            disp.setBrightness(24);
            disp.setBrightness(i, 5);
            delay(1000);
        }
    }
    
    disp.clear();
    disp.setBrightness(24);
    
    int16_t arr[] = { _h, _e, _l, _l };
    disp.printChar(arr);
    delay(1000);
    
    for (uint8_t i = 0;i < nAnod;i++){
        disp.clear(i);
        delay(1000);
    }
  
    disp.print(1234);
    disp.setBrightness(24);
    delay(1000);

    disp.point(1);
    delay(500);
    
    disp.point(0);
    delay(500);

    disp.point(1);
    delay(500);
    
    disp.point(0);
    delay(500);

    disp.printChar(0, _A);
    disp.printChar(1, _B);
    disp.printChar(2, _C);
    disp.printChar(3, _D);
    delay(2000);

    disp.print(0, 6);
    disp.print(1, 3);
    disp.print(2, 2);
    disp.print(3, 9);
    delay(1000);

    disp.clock(14, 40);
    delay(1000);
}
