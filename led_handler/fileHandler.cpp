#include "fileHandler.h"
#include <string.h>
#define VALUES_TO_READ 1
#define VALUES_TO_WRITE 1

FileHandler::FileHandler()
{
}

uint8_t FileHandler::ReadFile(const char* filePath)
{
    uint8_t rc = OpenFile(filePath, READ);

    if(rc != OK) return rc; 

    rc = _readContent();

    if(rc != OK) return rc;

    CloseFile();
    return OK;
}

char * FileHandler::GetFileContent()
{
    return _fileBuffer;
}

uint8_t FileHandler::WriteToFile(const char* filePath, const char* data)
{
    uint8_t rc = OpenFile(filePath, WRITE);

    if(rc != OK) return rc;

    rc = _writeContent(data);

    if(rc != OK) return rc;

    CloseFile();
    return OK;
}
uint8_t FileHandler::OpenFile(const char* filePath, const char* fileAction)
{
    return _openFile(filePath, fileAction);
}

uint8_t FileHandler::CloseFile()
{
    return _closeFile();
}

uint8_t FileHandler::_writeContent(const char *data)
{
    size_t writtenBytes = fwrite(data, VALUES_TO_WRITE, strlen(data), _filePointer);

    if(writtenBytes != strlen(data))
        return WRITE_ERROR;

    return OK;
}

uint8_t FileHandler::_readContent()
{
    char* readContent = fgets(_fileBuffer, BUFF_SIZE, _filePointer);

    if (readContent != NULL) 
    {
        // Remove the newline character, if it exists
        size_t len = strlen(_fileBuffer);

        if (len > 0 && _fileBuffer[len - 1] == '\n')
        {
            _fileBuffer[len - 1] = '\0';
        }

        return OK;
    } else {
        return UNEXPECTED_EOF;
    }
}

uint8_t FileHandler::_openFile(const char* filePath, const char* fileAction)
{
    _filePointer = fopen(filePath, fileAction);
    if(_filePointer == NULL)
        return UNABLE_TO_OPEN_FILE;
    return OK;
}

uint8_t FileHandler::_closeFile()
{
    fclose(_filePointer);
    return 0;
}
