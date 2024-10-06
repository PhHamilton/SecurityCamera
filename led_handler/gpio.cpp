#include "gpio.h"
#include <stdint.h>
#include <string.h>

#define STR_NULL (const char*)'\0'

GPIO::GPIO(const char* pinNumber) : _fileManager(&_fileHandler)
{
    _pinNumber = pinNumber;
    _filePath = _formatter.AddThreeStrings(GPIO_PATH, "/gpio", pinNumber);
    _export(_pinNumber);

}

const char* GPIO::Get()
{
    char* storedValuePath = _formatter.AddTwoStrings(_filePath, "/value");
    uint8_t rc = _fileManager.ReadFile(storedValuePath);

    if(rc == OK)
        return _fileManager.GetFileContent();
    else
        return STR_NULL;
}

uint8_t GPIO::Set(GPIO_MODE mode)
{
    const char* GPIOModeString = (mode == INPUT) ? "in" : "out";
    char* storedValuePath = _formatter.AddTwoStrings(_filePath, "/direction");

    printf("Setting mode to: %s, at: %s\n", GPIOModeString, storedValuePath);
    return _fileHandler.WriteToFile(storedValuePath, GPIOModeString);
}

uint8_t GPIO::TurnOn()
{
    return _write("/value", "1");
}

uint8_t GPIO::TurnOff()
{
    return _write("/value", "0");
}

uint8_t GPIO::Toggle()
{
    const char* currentValue = Get(); 
    const char* newValue = (strcmp(currentValue, "0") == 0) ? "1" : "0";
    _write("/value", newValue);
    return 0;
}
/*
uint8_t GPIO::EnableSoftwareDebounce(uint8_t debounceTime)
{
    _debounceTime = debounceTime;
    return 0;
}
*/

uint8_t GPIO::_write(const char* fileName, const char* value)
{
    char* storedValuePath = _formatter.AddTwoStrings(_filePath, fileName);
    printf("Writing: %s, to: %s\n", value, storedValuePath);
    uint8_t rc = _fileHandler.WriteToFile(storedValuePath, value);
    return rc;
}

uint8_t GPIO::_read()
{
    return 0;
}

uint8_t GPIO::_export(const char* pinNumber)
{
    char* exportPath = _formatter.AddTwoStrings(GPIO_PATH, "/export");
    uint8_t rc = _fileHandler.WriteToFile(exportPath, pinNumber); 
    printf("Writing: %s, to: %s\n", pinNumber, exportPath);
    return rc;
}

uint8_t GPIO::_unexport(const char* pinNumber)
{
    char* exportPath = _formatter.AddTwoStrings(GPIO_PATH, "/unexport");
    uint8_t rc = _fileHandler.WriteToFile(exportPath, pinNumber); 
    return rc;
}
