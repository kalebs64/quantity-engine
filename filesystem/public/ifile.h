#pragma once
#include <types.h>
#include <platform/platform.h>

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

//opaque pointer to a raw C FILE type, we just have to reinterpret the pointer to for C file operations.
class COpaqueFile;

//Interface class for file
stripped_vclass IFile {
public:
    virtual                 ~IFile() {}

    virtual int             Read(void* buffer, size_t size) = 0;
    virtual bool            MoveCursor(int32 offset, uint16 to) = 0;
    virtual int32           GetCursorPos() = 0;
    virtual void            Close() = 0;

    virtual COpaqueFile*    RawHandle() = 0;
    virtual Size_T          GetSize() = 0;
};