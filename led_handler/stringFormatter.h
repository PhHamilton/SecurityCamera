#ifndef STRING_FORMATTER_H
#define STRING_FORMATTER_H
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define MAX_STRING_SIZE 256

class StringFormatter
{
    public:
        StringFormatter();
        char* AddTwoStrings(const char* str1, const char* str2);
        char* AddThreeStrings(const char* str1, const char* str2, const char* str3);
    private:
        uint8_t _resetString();
};
#endif
