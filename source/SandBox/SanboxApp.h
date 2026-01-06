#pragma once
#include "RenderEngine.h"

using namespace RE;

class SanboxApp : public Application
{
public:
	SanboxApp();
	~SanboxApp();

	virtual void Run() override;
};

