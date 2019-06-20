/* Author: Tim */
#include "Testing.h"
#include "TestRenderEngine.h"
#include "TestWindowManager.h"
#include "TestMusicComponent.h"

#include <vector>

void Testing::RenderEngineTest1()
{
	std::vector<std::shared_ptr<RenderComponent>> p_vec = TestRenderEngine::randomSquaresTest(2, 500);
	TestWindowManager::displayRenderComponents();
}

void Testing::RenderEngineTest2()
{
	std::vector<std::shared_ptr<RenderComponent>> p_vec = TestRenderEngine::randomSquaresTest(2, 10);
	TestWindowManager::displayRenderComponents();
}

void Testing::musicTest1()
{
	TestMusicComponent::playMusicComponent("music/test_music_1.ogg");
}
