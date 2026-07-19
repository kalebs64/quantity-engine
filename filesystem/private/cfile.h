#pragma once
#include "ifile.h"

//Interface class for file
class CBaseFile : public IFile {
public:
                            CBaseFile();

    virtual bool            Open(const char* path, uint16 mode);
    virtual int             Read(void* buffer, size_t size);

    virtual bool            MoveCursor(int32 offset, uint16 to);
    virtual int32           GetCursorPos();
    virtual void            Close();

    virtual COpaqueFile*    RawHandle();
    virtual Size_T          GetSize();
private:
    COpaqueFile*            rawHandle;
};