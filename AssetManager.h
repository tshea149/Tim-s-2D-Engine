/* author: Tim */
#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

/* Interface class used to access and load various assets stored in their respective managers */

#include "EngineSettings.h"	// for USE_RESOURCE_FILE
#include "TextureManager.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <vector>
#include <stdint.h>
#include <memory>

class AssetManager
{
private:
	// pointers to control order of creation
	std::shared_ptr<ResourceManager> p_resource_manager;
	std::unique_ptr<TextureManager> p_texture_manager;

	AssetManager();

public:
	AssetManager(AssetManager &) = delete;

	static std::shared_ptr<AssetManager> getInstance();

	std::shared_ptr<std::vector<char>> getFileAsBuffer(std::string filepath);
	std::shared_ptr<sf::Texture> getTexture(std::string filepath);
	std::shared_ptr<sf::SoundBuffer> getSoundBuffer(std::string filepath);
};

#endif