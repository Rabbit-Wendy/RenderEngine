#pragma once

using namespace RE;

extern Application* CreateApplication();

int main(int argc, char* argv)
{
	Log::Init();
	auto app = CreateApplication();
	app->Run();
	delete app;
}