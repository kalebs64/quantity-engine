#pragma once
#include "ifile.h"

//Interface class for file
class CBaseFile : public IFile {
public:
                            CBaseFile(const char* fullPath, uint16 mode);

    virtual bool            Open(const char* name, const char* mode);
    virtual int             Read(void* buffer, size_t size);

    virtual bool            MoveCursor(int32 offset, uint16 to);
    virtual int32           GetCursorPos();
    virtual void            Close();

    virtual COpaqueFile*    RawHandle();
    virtual Size_T          GetSize();
private:
    size_t                  m_size;
    const char*             m_path;
    COpaqueFile*            m_rawHandle;
};