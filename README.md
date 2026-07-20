# quantity-engine

Quantity is not just an engine but a framework of modules that allow you to quickly make software just by plugging them into an `Application`. I chose to design it like this due to previous engine editor relationships, the biggest issue I had was that my editor had to really hack through the engine to turn off specific parts of its runtime. This also has the benefit of faster build times thanks to ninja, so you only rebuild modules and their dependents when source code is changed.

Yes, it is quite inspired by Source Engine. :)

# Status
Currently getting rendersystemgl back to its former glory as this rewrite is pretty fresh.

# Why so sparse?
This used to be a more complete engine featuring entity components and some simple rendering tech, but now I am doing a major rewrite for modularization so I can encourage reusabilty and ease app relations.

# Why such an odd coding style?
My coding style comes from a long history of working with idTech 4, I used to mod it aspiring to make games with it. I think it is a pretty clean style it is quite readable in my eye.

# How do I make applications with this?
```cpp
//Headers for all interface declarations.
#include <appframework/appframework.h>
#include <ifilesystem.h>
#include <irendersystem.h>
#include <imedia.h>
#include <tier0.h>
#include <iostream>

//You must define system pointers in main as in their header they are `extern`
IFileSystem* g_fileSystem;
IMedia* g_media;
IRenderSystemOpenGL* g_renderSystemGL;

// Our application
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

//Create is called before Init, so here we do module/interface creation.
bool CTestApplication::Create() {
    //an array describing how each system to load, expects: interface name, module dll name.
    appSystemInfo_t systems[] = {
        { QUANTITY_FILESYSTEM_VERSION,      "filesystem.dll" },
        { QUANTITY_MEDIA_VERSION,           "media.dll" },
        { QUANTITY_RENDERSYSTEMGL_VERSION,  "rendersystemgl.dll" },
    };
    //add them, this function will also load the interfaces from the dlls into memory for you.
    AddSystems(systems, 3);

    //FindSystemAt is not final, and I am actively looking for a better way of getting loaded interfaces.
    g_fileSystem = (IFileSystem*)FindSystemAt(0);
    g_media = (IMedia*)FindSystemAt(1);
    g_renderSystemGL = (IRenderSystemOpenGL*)FindSystemAt(2);

    TryConnectAllSystems();
    return true;
}

void CTestApplication::Destroy() {
}


//Called after Create, this is where you should be initializing all that you want to initialize.
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

//Called after Main
void CTestApplication::OnShutdown() {
    std::cout << "shutdown." << std::endl;
    //Clean up
    g_fileSystem->Shutdown();
    g_media->Shutdown();
    g_renderSystemGL->Shutdown();
}

//You're app's main loop (if it does loop)
int CTestApplication::Main() {
    std::cout << "main." << std::endl;

    //a basic main loop
    while(!g_media->CloseRequested()) {
        g_media->Poll();

        g_renderSystemGL->Frame();
        m_wnd->UpdateScreen();
    }
    return 0;
}

//This is your entrypoint, it will run your app for you.
CTestApplication app;
DEFINE_APPLICATION_OBJECT_ENTRY(app)
```