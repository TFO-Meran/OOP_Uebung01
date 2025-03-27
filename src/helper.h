#ifndef HELPER_H
#define HELPER_H

#include <Arduino.h>

/*
    ----------- INFO -------------
    Diese Struktur implementiert eine Taster-Auswertung.
    Es kann eine Debounce Zeit in ms (max. 255) gesetzt werden oder das Debounce
    mit 0 deaktiviert werden.
    Die Struktur verfügt über init-Methode zum Setzen der notwendigen
    Parameter und eine poll-Methode, welche bei jedem Loop ausgeführt
    werden soll. Diese stehen als Member-Variablen zur Verfügung.
*/
class button
{
public:
    bool debounced = false;
    bool rising = false;
    bool falling = false;
    bool longpress = false;

    // Pin-Nummer, Pin-Mode, Debounce-Zeit [ms], Zeitgrenze für langen Druck [ms]
    void init(uint8_t, uint8_t, uint8_t, uint16_t);

    void poll();

    // wenn Debounce-Zeit = 0, dann kein Debounce
    void debounce();

private:
    bool in = false;
    uint8_t mode = false;
    bool db_last = false;
    bool last = false;
    unsigned long lasttime = 0;
    unsigned long last_rising = 0;
    uint8_t pinNr = 0;
    uint8_t debounce_time = 20;
    uint16_t longpress_time = 1000;

    void check_edge();
    void check_longpress();
};

#endif