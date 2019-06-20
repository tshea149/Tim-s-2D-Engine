#include "AssetManager.h"

static std::weak_ptr<AssetManager> instance;

AssetManager::AssetManager()
{
	// not using make_shared because constructors are private
	p_resource_manager = std::shared_ptr<ResourceManager>(new ResourceManager());
	p_texture_manager = std::unique_ptr<TextureManager>(new TextureManager(p_resource_manager));
}

std::shared_ptr<AssetManager> AssetManager::getInstance()
{
	std::shared_ptr<AssetManager> p = instance.lock();
	if (p == nullptr)
	{
		p = std::shared_ptr<AssetManager>(new AssetManager());	// std::make_shared will not work here because constructor is private
		instance = p;
		return p;
	}

	else
		return p;
}

std::shared_ptr<std::vector<char>> AssetManager::getFileAsBuffer(std::string filepath)
{
	return p_resource_manager->loadFile(filepath);
}

std::shared_ptr<sf::Texture> AssetManager::getTexture(std::string filepath)
{
	return p_texture_manager->loadTexture(filepath);
}

std::shared_ptr<sf::SoundBuffer> AssetManager::getSoundBuffer(std::string filepath)
{
	return nullptr;
}
