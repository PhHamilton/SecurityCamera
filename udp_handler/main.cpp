#include <iostream>
#include <unistd.h>
#include <cstring>

#include "socket_handler.h"
#include "mqtt_handler.h"
#include "config_handler.h"


int main(int argc, char* argv[])
{
    SOCKET_HANDLER socketHandler("config/config.json");
    socketHandler.Initialize();
    socketHandler.Connect();

    while(1)
    {

    }

    return 0;
}
