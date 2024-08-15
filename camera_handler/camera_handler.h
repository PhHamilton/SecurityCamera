#ifndef CAMERA_HANDLER_H
#define CAMERA_HANDLER_H
#include <string.h>
#include "config_handler.h"

typedef enum
{
    DISABLED,
    DOG_MODE,
    SURVEILLENCE
}SURVEILLENCE_MODES;

class CAMERA_HANDLER
{
    public:
        CAMERA_HANDLER(std::string outputFilepath);
        bool Initialize();
        void TakePicture();
    private:
        std::string _outputFilepath;
        int _cycle;

        SURVEILLENCE_MODES _surveillenceMode = DISABLED;
        CONFIG_HANDLER cameraConfig;
};

#endif //CAMERA_HANDLER_H
