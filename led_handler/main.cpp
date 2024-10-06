#include <iostream>
#include <unistd.h>
#include <cstring>

#include "gpio.h"
#include "mqtt_handler.h"
#include "config_handler.h"

int main(int argc, char* argv[])
{
    GPIO redLed = GPIO("535");
    GPIO greenLed = GPIO("536");

    redLed.Set(OUTPUT);
    greenLed.Set(OUTPUT);
    redLed.TurnOn();
    greenLed.TurnOn();
    int i = 0;
    int maxValue = 100000;
    while(i < maxValue)
    {
        i += 1;
    }

    redLed.TurnOff();
    greenLed.TurnOff();

    return 0;
}
