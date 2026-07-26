#include "cfile.h"
#include <stdio.h>
#include <stdlib.h>

CBaseFile::CBaseFile(const char* fullPath, uint16 mode) {
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

    m_path = fullPath;
}

bool CBaseFile::Open(const char* name, const char* mode) {
    FILE* pFileHand = fopen(name, mode);

    if(pFileHand) {
        m_rawHandle = reinterpret_cast<COpaqueFile*>(pFileHand);
        MoveCursor(0, FSU_EOF);
        m_size = GetCursorPos();
        MoveCursor(0, FSU_BOF);

        return true;
    }

    return false;
}

int CBaseFile::Read(void* buffer, size_t size) {
    return (int)fread(buffer, 1, size, reinterpret_cast<FILE*>(m_rawHandle));
}

bool CBaseFile::MoveCursor(int32 offset, uint16 to) {
    FILE* file = reinterpret_cast<FILE*>(m_rawHandle);
    switch(to) {
        case FSU_BOF:
            return (fseek(file, offset, SEEK_SET) == 0);
            break;
        case FSU_CUR:
            return (fseek(file, offset, SEEK_CUR) == 0);
            break;
        case FSU_EOF:
        default:
            return (fseek(file, offset, SEEK_END) == 0);
            break;
    }
    return false;
}

int32 CBaseFile::GetCursorPos() {
    return ftell(reinterpret_cast<FILE*>(m_rawHandle));
}

void CBaseFile::Close() {
    m_size = 0;
    fclose(reinterpret_cast<FILE*>(m_rawHandle));
}

COpaqueFile* CBaseFile::RawHandle() {
    return m_rawHandle;
}

Size_T CBaseFile::GetSize() {
    return m_size;
}