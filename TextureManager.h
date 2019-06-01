/* Author: Tim */
#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <unordered_map>
#include <SFML/Graphics/Texture.hpp>
#include <memory>

#include "ResourceManager.h"

#include <iostream>

class TextureManager
{
private:
	friend class AssetManager;
	TextureManager(std::shared_ptr<ResourceManager> const _p_resource_manager) : p_resource_manager(_p_resource_manager) {};

	std::shared_ptr<ResourceManager> const p_resource_manager;

	struct TextureCacheEntry
	{
		// stored filename for finding the texture inside the texture_cache
		std::string filepath;
		std::weak_ptr<sf::Texture> p_tex;
	};

	// deletes the pointer to texture data and removes the corresponding TextureCacheEntry from the texture_cache
	struct TextureDeleter
	{
		TextureDeleter(TextureManager* _p_texture_manager, std::string _filepath) : p_texture_manager(_p_texture_manager), filepath(_filepath) {};
		void operator()(sf::Texture*);
		TextureManager* p_texture_manager;
		std::string filepath;
	};

	void removeTextureCacheEntry(std::string filepath);

	// Key filepath, value texture
	std::unordered_map<std::string, TextureCacheEntry> texture_cache;	// get the shared ptr reference count to determine when to delete (should be 1, as the map will be the only reference)

public:
	// returns shared_ptr to texture loaded in memory (and loads texture into memory if not already present)
	std::shared_ptr<sf::Texture> loadTexture(std::string filepath);

	// removes texture from the manager (and memory) if and only if there is nothing else using the texture
	// returns true on success, false on failure (meaning the texture has another dependency or was not found in the map)
	/*bool unloadTexture(std::string filepath);*/
};

#endif // !TEXTUREMANAGER_H


