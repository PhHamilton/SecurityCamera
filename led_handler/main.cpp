#include <iostream>
#include <unistd.h>
#include <cstring>

#include "gpio.h"
#include "mqtt_handler.h"
#include "config_handler.h"
#include "led_handler.h"

int main(int argc, char* argv[])
{
    LED_HANDLER ledHandler("536");
    ledHandler.Initialize();
    ledHandler.StartThread();

    while(1)
    {

    }

    return 0;
}
