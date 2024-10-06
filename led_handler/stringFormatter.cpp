#include "stringFormatter.h"


StringFormatter::StringFormatter()
{
}

char* StringFormatter::AddTwoStrings(const char* str1, const char* str2)
{
    _resetString(); // To make sure that the string has no previous value stored
    char* result = new char[strlen(str1) + strlen(str2) + 1];
    sprintf(result, "%s%s", str1, str2);
    return result;
}

char* StringFormatter::AddThreeStrings(const char* str1, const char* str2, const char* str3)
{
    _resetString(); // To make sure that the string has no previous value stored
    char* result = new char[strlen(str1) + strlen(str2) + strlen(str3) + 1];
    sprintf(result, "%s%s%s", str1, str2, str3);
    return result;
}
uint8_t StringFormatter::_resetString()
{
    return 0;
}
