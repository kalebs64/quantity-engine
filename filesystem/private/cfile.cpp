#include "cfile.h"

CBaseFile::CBaseFile() {}

bool CBaseFile::Open(const char* path, uint16 mode) {
    return false;
}

int CBaseFile::Read(void* buffer, size_t size) {
    return -1;
}

bool CBaseFile::MoveCursor(int32 offset, uint16 to) {
    return false;
}

int32 CBaseFile::GetCursorPos() {
    return -1;
}

void CBaseFile::Close() {}

COpaqueFile* CBaseFile::RawHandle() {
    return nullptr;
}

Size_T CBaseFile::GetSize() {
    return 0;
}