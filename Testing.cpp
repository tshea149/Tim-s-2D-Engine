/* Author: Tim */
#include "Testing.h"
#include "TestRenderEngine.h"
#include "TestWindowManager.h"
#include "TestMusicComponent.h"

#include <vector>

void Testing::RenderEngineTest1()
{
	std::vector<RenderComponentHandle> p_vec = TestRenderEngine::randomSquaresTest(2, 500);
	TestWindowManager::displayRenderComponents();
	TestRenderEngine::deallocateRenderComponents(p_vec);
}

void Testing::RenderEngineTest2()
{
	std::vector<RenderComponentHandle> p_vec = TestRenderEngine::randomSquaresTest(2, 10);
	TestRenderEngine::deallocateRenderComponents(p_vec);
	TestWindowManager::displayRenderComponents();
}

void Testing::musicTest1()
{
	TestMusicComponent::playMusicComponent("music/test_music_1.ogg");
}
