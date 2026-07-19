#pragma once
#include "types.h"
#include <stdio.h>

enum MoveOrigin : uint16 {
    FSU_EOF = 0,
    FSU_CUR,
    FSU_BOF
};

enum OpenMode : uint16 {
    FS_READ,
    FS_WRITE,
    FS_READWRITE,
    FS_APPEND
};

class CFile {
public:
	CFile(const char* fullPath, uint16 mode);

    int     Read(void* buffer, size_t size);
    Size_T  GetSize() {return size;}

    FILE*   RawHandle() {return fileHandle;}

    void    Close();
    bool    MoveCursor(int32 offset, uint16 to);
    int32   GetCursorPos();
private:
    bool    Open(const char* name, const char* mode);
private:
    FILE* fileHandle;
    size_t size;
    const char* path;
};
