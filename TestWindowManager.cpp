/* Author: Tim */
#ifndef TESTWINDOWMANAGER_CPP
#define TESTWINDOWMANAGER_CPP

#include "TestWindowManager.h"

#include "WindowManager.h"
#include "RenderEngine.h"

void TestWindowManager::displayRenderComponents()
{
	WindowManager::getInstance()->clearWindow();
	RenderEngine::getInstance()->update();
	WindowManager::getInstance()->displayWindow();
}

#endif // !WINDOWMANAGER_CPP
