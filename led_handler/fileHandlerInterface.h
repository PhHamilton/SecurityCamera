#ifndef FILE_HANDLER_INTERFACE_H
#define FILE_HANDLER_INTERFACE_H
#include <stdint.h>

class FileHandlerInterface
{
    public:
        virtual uint8_t ReadFile(const char* filePath) = 0;
        virtual char* GetFileContent() = 0;
        virtual uint8_t WriteToFile(const char* filePath, const char* data) = 0;
        virtual uint8_t OpenFile(const char* filePath, const char* fileAction) = 0;
        virtual uint8_t CloseFile() = 0;

        virtual ~FileHandlerInterface() = default;
};
#endif
