#include "digitalblinker.h"

void blinker::init(uint8_t _pin1, bool _neg1, uint8_t _pin2, bool _neg2, uint16_t _blinkTime, bool _enable)
{
    pin1 = _pin1;
    neg1 = _neg1;
    pin2 = _pin2;
    neg2 = _neg2;
    blinkTime = _blinkTime;
    enable = _enable;

    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
}

void blinker::poll()
{
    if (!enable)
    {
        digitalWrite(pin1, neg1 ? HIGH : LOW);
        digitalWrite(pin2, neg2 ? HIGH : LOW);
        return;
    }
    else if (millis() - lastblink > blinkTime)
    {
        // Serial.println(".");
        digitalWrite(pin1, neg1 ? !blinkState : blinkState);
        digitalWrite(pin2, neg1 ? !blinkState : blinkState);
        blinkState = !blinkState;
        lastblink = millis();
    }
}

void blinker::on() { enable = true; }   // setter-Methode zum Einschalten des Blinkers
void blinker::off() { enable = false; } // setter-Methode zum Ausschalten des Blinkers

void blinker::setBlinkTime(uint16_t _blinktime)
{
    if (_blinktime > 1000)
    {
        blinkTime = 1000;
        Serial.println("Blinktime > 1000ms, set to 1000ms");
    }
    else if (_blinktime < 50)
    {
        blinkTime = 50;
        Serial.println("Blinktime < 50ms, set to 50ms");
    }
    else
        blinkTime = _blinktime;
}