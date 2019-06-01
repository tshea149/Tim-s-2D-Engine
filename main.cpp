/* Author: Tim */
#include <memory>

#include "WindowManager.h"
#include "HandleManager.h"
#include "AssetManager.h"
#include "RenderEngine.h"
#include "Game.h"

// Testing files
#include "Testing.h"

#if _DEBUG
#include "Debug.h"
#endif

#include "MusicComponent.h"

int main()
{
	// initalize debugging module if applicable
	#if _DEBUG
	Debug::initialize();
	#endif //DEBUG

	// component initialization
	std::shared_ptr<AssetManager> p_asset_manager = AssetManager::getInstance();
	std::shared_ptr<WindowManager> p_window_manager = WindowManager::getInstance();
	std::shared_ptr<RenderEngine> p_render_engine = RenderEngine::getInstance();
	p_render_engine->setRenderTarget(p_window_manager->getWindow());

	Testing::RenderEngineTest1();
	Testing::musicTest1();

	system("pause");

#ifdef DEBUG
	Debug::close();
#endif // DEBUG

	return 0;
}