#include "stringutil.h"
#include <Windows.h>
#include <iostream>

std::string UTF16To8(const std::wstring& utf16Str) {
    if (utf16Str.empty()) {
        return "";
    }

    int utf8Len = WideCharToMultiByte(
        CP_UTF8,
        0,
        utf16Str.c_str(),
        static_cast<int>(utf16Str.length()),
        NULL,
        0,
        NULL, NULL
    );

    if (utf8Len == 0) {
        throw std::runtime_error("WideCharToMultiByte failed in first pass");
    }

    std::string utf8Str(utf8Len, '\0');
    int result = WideCharToMultiByte(
        CP_UTF8,
        0,
        utf16Str.c_str(),
        static_cast<int>(utf16Str.length()),
        &utf8Str[0],
        utf8Len,
        NULL, NULL
    );

    if (result == 0) {
        throw std::runtime_error("WideCharToMultiByte failed in second pass");
    }

    return utf8Str;
}