
// ****************************************************************************
// *                                                                          *
// * Aufgabe:                                                                 *
// *                                                                          *
// * -> Schreib ein Programm mit folgenden Eigenschaften:                     *
// *    Es gibt zwei Taster (TASTER1, TASTER2), zwei LEDs (LED1, LED2) und    *
// *    ein Potentiometer. Taster1 schaltet einen digitalen Blinker auf die   *
// *    beiden LEDs, Taster2 schaltet einen analogen Blinker auf die beiden   *
// *    LEDs. Die Geschwindigkeit des Blinkers soll mit dem Poti zwischen     *
// *    50ms und 1000ms eingestellt werden können. Ein langer Tastendruck     *
// *    auf einen der beiden Taster toggelt die Blinkfunktion ein/aus.        *
// *                                                                          *
// * -> Suche dir ein/zwei Mitarbeiter und forke dieses Projekt               *
// * -> Teile die Arbeit auf die Mitarbeiter so auf, dass ein fast-forward-   *
// *    merge ermöglicht wird.                                                *
// * -> Fülle die bestehenden Header-Dateien und erzeuge die entsprechenden   *
// *    Implementierungen (cpp-Dateien). Verwende ausschließlich Klassen!     *
// *                                                                          *
// * -> Erstelle einen pull-request                                           *
// *                                                                          *
// *                                                                          *
// ****************************************************************************

#include <Arduino.h>
#include "helper.h"
#include "digitalblinker.h"
#include "analogblinker.h"

#define LED1 3     // Low-side switch (leuchtet mit LOW)
#define LED2 5     // Low-side switch (leuchtet mit LOW)
#define LED3 6     // Low-side switch (leuchtet mit LOW)
#define TASTER1 10 // LOW wenn gedrückt
#define TASTER2 11 // LOW wenn gedrückt
#define TASTER3 12 // LOW wenn gedrückt
#define POT1 A7

#define DEBOUNCE_TIME 20
#define LONGPRESS_TIME 1000
#define BLINK_TIME 200
#define MIN_BLINK_TIME 50
#define MAX_BLINK_TIME 1000
#define POLL_TIME 50

button taster1, taster2;
blinker d_blink;
analogblinker a_blink;

void setup()
{
    Serial.begin(115200); // Baud rate
    Serial.println("..Start..\n");

    taster1.init(TASTER1, INPUT_PULLUP, DEBOUNCE_TIME, LONGPRESS_TIME);
    taster2.init(TASTER2, INPUT_PULLUP, DEBOUNCE_TIME, LONGPRESS_TIME);

    d_blink.init(LED1, true, LED2, true, BLINK_TIME, false);
    a_blink.init(LED1, LED2, BLINK_TIME, POLL_TIME, false, false);
}

void loop()
{
    taster1.poll();
    taster2.poll();
    a_blink.poll();
    d_blink.poll();

    uint16_t blinktime = MIN_BLINK_TIME + ((MAX_BLINK_TIME - MIN_BLINK_TIME) / 1023.0) * analogRead(POT1);
    a_blink.setBlinkTime(blinktime);
    d_blink.setBlinkTime(blinktime);

    if (taster1.rising)
    {
        Serial.print("digital blinker EIN : ");
        Serial.print(blinktime);
        Serial.println("ms");
        a_blink.off();
        d_blink.on();
    }

    if (taster2.rising)
    {
        Serial.print("analog blinker EIN : ");
        Serial.print(blinktime);
        Serial.println("ms");
        d_blink.off();
        a_blink.on();
    }

    if (taster1.longpress || taster2.longpress)
    {
        Serial.println("BLINKER AUS");
        a_blink.off();
        d_blink.off();
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, HIGH);    
    }
}
