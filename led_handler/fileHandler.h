#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H
#include <stdio.h>
#include <stdint.h>
#include "fileHandlerInterface.h"

#define BUFF_SIZE 50

#define READ "rb"
#define WRITE "w"
typedef enum
{
    OK,
    FILE_NOT_FOUND,
    UNABLE_TO_OPEN_FILE,
    UNEXPECTED_EOF,
    READ_ERROR,
    WRITE_ERROR,
    UNKNOWN_ERROR
}FILE_HANDLER_ERROR_CODES;

class FileHandler : public FileHandlerInterface
{
    public:
        FileHandler();
        virtual uint8_t ReadFile(const char* filePath) override;
        virtual char* GetFileContent() override;
        virtual uint8_t WriteToFile(const char* filePath, const char *data) override;
        virtual uint8_t OpenFile(const char* filePath, const char* fileAction) override;
        virtual uint8_t CloseFile() override;
        ~FileHandler() {}

    private: 
        FILE *_filePointer = NULL;
        char _fileBuffer[BUFF_SIZE] = {'\0'};
        uint8_t _openFile(const char* filePath, const char* fileAction);
        uint8_t _writeContent(const char *data);
        uint8_t _readContent();
        uint8_t _closeFile();
};
#endif
