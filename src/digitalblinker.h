#ifndef DIGITALBLINKER_H
#define DIGITALBLINKER_H

#include <Arduino.h>

/*
    ----------- INFO -------------
    Dise Struktur implementiert einen Wechselblinker auf zwei bliebige Pins.
    In der init-Methode können die Pin-Nummern definiert werden. Außerdem ist es
    möglich eine negation des Ausgangs direkt anzugeben. Die poll-Methode muss
    bei jedem Loop ausgeführt werden.
*/
class blinker
{
public:

    // PinNr.1, Negierung1, PinNr.2, Negierung2, Blinkzeit [ms], Startzustand
    void init(uint8_t, bool, uint8_t, bool, uint16_t, bool);
    void poll();
    void on();
    void off();
    void setBlinkTime(uint16_t);

private:
    uint8_t pin1 = 0, pin2 = 0;
    bool neg1 = false, neg2 = false, blinkState = false, enable = false;
    unsigned long lastblink = 0;    
    uint16_t blinkTime = 0;
};

#endif