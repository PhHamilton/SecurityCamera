#include "camera_handler.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <signal.h>
#include <unistd.h>

CAMERA_HANDLER::CAMERA_HANDLER(std::string outputFilepath) : cameraConfig("config/config.json")
{
    _outputFilepath = outputFilepath;
}

bool CAMERA_HANDLER::Initialize()
{
    return true;
}

void CAMERA_HANDLER::TakePicture()
{
    if((fork()) != 0)
        std::cerr << "Failed to duplicate process.." << std::endl;

    std::ostringstream ss;
    int width = std::to_string(cameraConfig.GetImageCycleLimit() - 1).length();
    ss << cameraConfig.GetOutputFilename() << std::setw(width) << std::setfill('0') << _cycle;

    if(cameraConfig.GetVerticalFlip() == true)
    {
        execl("/user/bin/raspistill",
              "/user/bin/raspistill",
              "-n",
              "-vf",
              "-o",
              ss.str(),
              NULL
             );
    }
    else
    {
        execl("/user/bin/raspistill",
          "/user/bin/raspistill",
          "-n",
          "-o",
          ss.str(),
          NULL
         );

    }
}
