#include "appframework.h"
#include "interface.h"
#include <assert.h>

int AppMain(int argc, char** argv, CBaseApplication* app) {
    assert(app);

    return app->Run();
}