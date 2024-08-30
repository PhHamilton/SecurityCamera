#include <iostream>
#include <unistd.h>
#include <cstring>

#include "camera_handler.h"

/*
typedef enum
{
    DISABLED,
    DOG_MODE,
    SURVEILLENCE
}SURVEILLENCE_MODES;
*/

CAMERA_HANDLER cameraHandler("./");

int main(int argc, char* argv[])
{
    cameraHandler.Initialize();
    while(1)
    {

    }

    return 0;
}
