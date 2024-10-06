#ifndef GPIO_H
#define GPIO_H
#include <stdint.h>
#include "fileManager.h"
#include "fileHandler.h"
#include "stringFormatter.h"

#define PATH_MAX 256;
#define GPIO_PATH "/sys/class/gpio"

typedef enum
{
    INPUT,
    OUTPUT
}GPIO_MODE;

typedef enum
{
    LOW,
    HIGH,
} PIN_STATES;

typedef enum
{
    RISING,
    FALLING
} DETECTION_TYPE;

typedef enum
{
} GPIO_ERROR_CODES;

class GPIO
{
    public:
        GPIO(const char* pinNumber);
        const char* Get();
        uint8_t Set(GPIO_MODE mode);
        uint8_t TurnOn();
        uint8_t TurnOff();
        uint8_t Toggle();
        ~GPIO() {_unexport(_pinNumber);}
    private:
        uint8_t _write(const char* fileName, const char* value);
        uint8_t _read();
        uint8_t _export(const char *pinNumber);
        uint8_t _unexport(const char *pinNumber);
        uint8_t _debounceTime;
        const char* _pinNumber;
        char* _filePath = new char[MAX_STRING_SIZE];

        FileHandler _fileHandler;
        FileManager _fileManager;
        StringFormatter _formatter;
};

#endif
