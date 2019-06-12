#include "TextureManager.h"

std::shared_ptr<sf::Texture> TextureManager::loadTexture(std::string filepath)
{
	// check map for texture ptr
	//	\ if present, returns copy of the pointer. If not present, loads the texture from file, stores pointer in the map, and returns copy of the pointer.
	std::unordered_map<std::string, std::weak_ptr<sf::Texture>>::iterator iter = texture_cache.find(filepath);
	if (texture_cache.end() == iter)
	{
		// texture not in map, must be loaded from file

		std::unique_ptr<std::vector<char>> p_data = p_resource_manager->loadFile(filepath);
		if (nullptr == p_data)
			return nullptr; // texture not loaded

		// allocate texture and make shared pointer to it with custom deletor for removing TextureCacheEntry from texture_cache
		TextureDeleter tex_deleter(&texture_cache, filepath);
		std::shared_ptr<sf::Texture> p_tex = std::shared_ptr<sf::Texture>(new sf::Texture(), tex_deleter);

		if (true == p_tex->loadFromMemory(p_data->data(), p_data->size()))
		{
			// add texture to map
			texture_cache[filepath] = p_tex;
		}

		return p_tex;	// return p_tex, wether or not it is valid or nullptr
	}
	else
		return iter->second.lock();
}

void TextureManager::TextureDeleter::operator()(sf::Texture* p_tex)
{
	// delete the texture data
	delete p_tex;

	// remove weak_ptr to texture from the texture_cache
	p_texture_cache->erase(filepath);
}
