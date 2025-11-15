#include "SanboxApp.h"

using namespace RE;

SanboxApp::SanboxApp()
{
}

SanboxApp::~SanboxApp()
{
}

Application* CreateApplication()
{
	return new SanboxApp();
}