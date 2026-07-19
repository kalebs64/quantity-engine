#include "file.h"
#include <assert.h>
#include <stdlib.h>

CFile::CFile(const char* fullPath, uint16 mode) {
    switch(mode) {
        case FS_READ:
            Open(fullPath, "r");
            break;
        case FS_WRITE:
            Open(fullPath, "wb");
            break;
        case FS_READWRITE:
            Open(fullPath, "rw+");
            break;
        case FS_APPEND:
            Open(fullPath, "ab");
            break;
    }

    path = fullPath;
}

int CFile::Read(void* buffer, size_t size) {
    return (int)fread(buffer, 1, size, fileHandle);
}

bool CFile::Open(const char* name, const char* mode) {
    fileHandle = fopen(name, mode);

    if(fileHandle) {
        MoveCursor(0, FSU_EOF);
        size = GetCursorPos();
        MoveCursor(0, FSU_BOF);

        return true;
    }

    return false;
}

void CFile::Close() {
    size = 0;
    fclose(fileHandle);
}

bool CFile::MoveCursor(int32 offset, uint16 to) {
    switch(to) {
        case FSU_BOF:
            return (fseek(fileHandle, offset, SEEK_SET) == 0);
            break;
        case FSU_CUR:
            return (fseek(fileHandle, offset, SEEK_CUR) == 0);
            break;
        case FSU_EOF:
        default:
            return (fseek(fileHandle, offset, SEEK_END) == 0);
            break;
    }
}

int32 CFile::GetCursorPos() {
    return ftell(fileHandle);
}