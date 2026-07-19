#include <appframework/appframework.h>
#include <ifilesystem.h>
#include <irendersystem.h>
#include <imedia.h>
#include <tier0.h>
#include <iostream>

IFileSystem* g_fileSystem;
IMedia* g_media;
IRenderSystemOpenGL* g_renderSystemGL;

class CTestApplication : public CBaseApplication {
public:
    virtual bool        Create();
    virtual void        Destroy();
    virtual int         OnInit();
    virtual void        OnShutdown();
    virtual int         Main();
private:
    IWindow* m_wnd;
};

bool CTestApplication::Create() {
    appSystemInfo_t systems[] = {
        { QUANTITY_FILESYSTEM_VERSION,      "filesystem.dll" },
        { QUANTITY_MEDIA_VERSION,           "media.dll" },
        { QUANTITY_RENDERSYSTEMGL_VERSION,  "rendersystemgl.dll" },
    };
    AddSystems(systems, 3);

    g_fileSystem = (IFileSystem*)FindSystemAt(0);
    g_media = (IMedia*)FindSystemAt(1);
    g_renderSystemGL = (IRenderSystemOpenGL*)FindSystemAt(2);

    TryConnectAllSystems();
    return true;
}

void CTestApplication::Destroy() {}

int CTestApplication::OnInit() {
    std::cout << "init." << std::endl;
    int i = 0;

    g_fileSystem->InitAndSetBase("D:/dev/gamedev/gander-tester/base");
    i = g_media->Init();

    if(i != SYS_INIT_OK) {
        return i;
    }
    mediaWindowInfo_t info = {};
    info.width = 800;
    info.height = 600;
    info.flags |= (MD_WND_USING_GL);
    info.title = "window.";

    g_media->CreateWindow(&info);
    m_wnd = g_media->GetTargetWindow();

    i = g_renderSystemGL->Init();
    if(i != SYS_INIT_OK) {
        return i;
    }

    return i;
}

void CTestApplication::OnShutdown() {
    std::cout << "shutdown." << std::endl;
}

int CTestApplication::Main() {
    std::cout << "main." << std::endl;

    while(!g_media->CloseRequested()) {
        g_media->Poll();

        g_renderSystemGL->Frame();
        m_wnd->UpdateScreen();
    }
    return 0;
}

CTestApplication app;
DEFINE_APPLICATION_OBJECT_ENTRY(app)