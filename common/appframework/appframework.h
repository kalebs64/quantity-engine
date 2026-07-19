#pragma once
#include "application.h"
#include "platform/platform.h"
#include "interface.h"

int AppMain(int argc, char** argv, CBaseApplication *app);

#ifdef _WIN32
#define DEFINE_APPLICATION_OBJECT_ENTRY(appName)                                                            \
	int main(int argc, char** argv)	{                                                                       \
		return AppMain(argc, argv, &appName);    		                                                    \
	}
#endif