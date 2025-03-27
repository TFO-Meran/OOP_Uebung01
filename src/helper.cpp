#include "helper.h"

// ****************************************************************************
// ************************** button ******************************************
// ****************************************************************************

void button::init(uint8_t _pinNr, uint8_t _mode, uint8_t _debounce_time, uint16_t _longpress_time)
{
    pinNr = _pinNr;
    mode = _mode;
    debounce_time = _debounce_time;
    longpress_time = _longpress_time;

    pinMode(pinNr, mode);
    debounced = db_last = last = digitalRead(pinNr); // ..damit nicht schon beim Start eine Flanke ausgelöst wird..
}

void button::poll()
{
    in = digitalRead(pinNr);
    in = ((mode == INPUT_PULLUP) ? !in : in);
    debounce();
    check_edge();
    check_longpress();
}

void button::debounce()
{
    if (millis() - lasttime > debounce_time)
    {
        if (in != db_last)
        {
            debounced = db_last;
        }
        else
        {
            debounced = in;
        }
        lasttime = millis();
        db_last = in;
    }
}

void button::check_edge()
{
    rising = false;

    if (debounced && !last)
        rising = true;

    falling = false;

    if (!debounced && last)
        falling = true;

    last = debounced;
}


void button::check_longpress()
{
    longpress = false;

    if (rising)
    {
        last_rising = millis();
        return;
    }

    if (falling)
    {
        if (millis() - last_rising > longpress_time)
        {
            longpress = true;
        }
    }
    else // damit longpress nur einen einzigen Zyklus lang true ist
    {
        longpress = false;
    }
}
