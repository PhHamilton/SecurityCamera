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

const std::string outputFilePath = "./";
CAMERA_HANDLER cameraHandler("outputFilePath");

int main(int argc, char* argv[])
{
    cameraHandler.Initialize();
    while(1)
    {

    }

    return 0;
}
