#include "fileManager.h"


FileManager::FileManager(FileHandlerInterface *handler)
{
    _fileHandler = handler;
}
uint8_t FileManager::ReadFile(const char* filePath)
{
    return _fileHandler->ReadFile(filePath);
}

const char* FileManager::GetFileContent()
{
    return _fileHandler->GetFileContent();
}

uint8_t FileManager::Open(const char* filePath, const char* fileAction)
{
    return _fileHandler->OpenFile(filePath, fileAction);
}

uint8_t FileManager::Close()
{
    return _fileHandler->CloseFile();
}

uint8_t FileManager::WriteToFile(const char* filePath, const char* data)
{
    return _fileHandler->WriteToFile(filePath, data);
}
