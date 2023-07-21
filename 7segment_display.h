#pragma once
#include "code.h"

#ifndef invertS
#define invertS 1
#endif


#ifndef invertA
#define invertA 1
#endif

#if invertS == 1
#define setPinS(pin, x) digitalWrite(pin, !x)
#else
#define setPinS(pin, x) digitalWrite(pin, x)
#endif

#if invertA == 1
#define setPinA(pin, x) digitalWrite(pin, !x)
#else
#define setPinA(pin, x) digitalWrite(pin, x)
#endif

class Display{
public:
    ~Display() {
        delete[] buf;
        delete[] brCounter;
        delete[] brightness;
    }
    
    void init(uint8_t* _segments, uint8_t* _anod, uint8_t _nAnod = 4, uint8_t _pointPin = -1){
        segments = _segments;
        anod = _anod;
        nAnod = _nAnod;
        pointPin = _pointPin;
        buf = new int16_t[nAnod];
        brightness = new uint8_t[nAnod](20);
        brCounter  = new uint8_t[nAnod];
        
        TCCR2B = (TCCR2B & B11111000) | 1;  //timer2 (~7kHz)
        bitSet(TCCR2A, WGM21);
        bitSet(TIMSK2, OCIE2A);     //прерывание по таймеру
        
        for (uint8_t i = 0;i < 7 + nAnod;i++)
            pinMode(i < 7 ? segments[i] : anod[i - 7], OUTPUT);
        
        pinMode(pointPin, OUTPUT);
        point(0);
    }

    void timer() {
        static uint8_t counter = 0;
        static uint8_t i = 0;
        
        if (++brCounter[i] == brightness[i])
            setPinA(anod[i], true);

        if (brCounter[i] > 25) {
            brCounter[i] = 0;
            if (++i >= nAnod)i = 0;

            if(brightness[i] > 0){
                setChar(buf[i]);
                setPinA(anod[i], false);
            }
        }
    }
    
//-----public-----//
    void setBrightness(uint8_t x){  //x = 0...24 
        for (uint8_t i = 0;i < nAnod;i++)
            setBrightness(i, x);
    }
    
    void setBrightness(uint8_t pos, uint8_t x){   //x = 0...24
        if(pos < nAnod)
            brightness[pos] = (x > 24 ? 24 : x);
    }

    void clear(){
        for (uint8_t i = 0;i < nAnod;i++)
            clear(i);
    }

    void clear(uint8_t pos){
        printChar(pos, _empty);
    }
    
    void point(bool flag){
        if(pointPin != -1)
            setPinS(pointPin, flag);
    }
    
    void print(uint16_t num){
        for (int8_t i = nAnod - 1;i >= 0;i--) {
            buf[i] = digitMask[num % 10];
            num /= 10;
        }
    }

    void print(uint8_t pos, int8_t x){
        if(pos < nAnod) buf[pos] = digitMask[x];
    }    

    void print(int16_t* arr){
        for (uint8_t i = 0;i < nAnod;i++)
            buf[i] = digitMask[arr[i]];
    }

    void clock(uint8_t x1, uint8_t x2){
        buf[0] = digitMask[x1 / 10];
        buf[1] = digitMask[x1 % 10];
        buf[2] = digitMask[x2 / 10];
        buf[3] = digitMask[x2 % 10];
    }
    
    //-----Char-----//
    void printChar(uint8_t pos, int8_t x){
        if(pos < nAnod) buf[pos] = x;
    }  

    void printChar(int16_t* arr){
        for (uint8_t i = 0;i < nAnod;i++)
            buf[i] = arr[i];
    }
    //-----Char-----//
    
//-----public-----//
private:
    int16_t *buf;
    uint8_t *segments, *anod;
    uint8_t *brightness, *brCounter;
    int8_t nAnod, pointPin;
    
//-----func-----//
    void setChar(int16_t x) {
        for (uint8_t i = 0;i < 7;i++)
            setPinS(segments[i], bitRead(x, i));
    }

    void setDigit(int8_t x) {
        if(x != -1){
            for (uint8_t i = 0;i < 7;i++)
                setPinS(segments[i], bitRead(digitMask[x], i));
        }else{
            for (uint8_t i = 0;i < 7;i++)
                setPinS(segments[i], 0);
        }
    }

    void setAnod(uint8_t x) {
        x = 0x01 << x;
        for (uint8_t i = 0;i < nAnod;i++)
            digitalWrite(anod[i], bitRead(x, i));
    }
//-----func-----//
};
Display disp;

ISR(TIMER2_COMPA_vect){
    disp.timer();
}