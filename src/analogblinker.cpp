#include "analogblinker.h"

// ****************************************************************************
// ************************** analogblinker ************************************
// ****************************************************************************

void analogblinker::init(uint8_t _pin1, uint8_t _pin2, uint16_t _blinkTime, uint8_t _polltime, bool _sync, bool _enable)
{
    pin1 = _pin1;
    pin2 = _pin2;
    blinkTime = _blinkTime;
    polltime = _polltime;
    sync = _sync;
    enable = _enable;

    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
}

void analogblinker::poll()
{
    if (!enable)
    {
        analogWrite(pin1, 0);
        analogWrite(pin2, 0);
        return;
    }
    else if (millis() - lastpoll > polltime)
    {
        step = 256 / (blinkTime / polltime);
        dutycycle += step;
        if (dutycycle >= 511)
        {
            dutycycle = 0;
        }
        uint16_t pwm = dutycycle > 255 ? 511 - dutycycle : dutycycle;
        analogWrite(pin1, pwm);
        if (sync)
            analogWrite(pin2, pwm);
        else
            analogWrite(pin2, 255 - pwm);
        lastpoll = millis();
    }
}

void analogblinker::setBlinkTime(uint16_t _blinktime)
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