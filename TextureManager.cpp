#include "TextureManager.h"

void TextureManager::removeTextureCacheEntry(std::string filepath)
{
	texture_cache.erase(filepath);
}

std::shared_ptr<sf::Texture> TextureManager::loadTexture(std::string filepath)
{
	// check map for texture ptr
	//	\ if present, returns copy of the pointer. If not present, loads the texture from file, stores pointer in the map, and returns copy of the pointer.
	std::unordered_map<std::string, TextureCacheEntry>::iterator iter = texture_cache.find(filepath);
	if (texture_cache.end() == iter)
	{
		// texture not in map, must be loaded from file

		std::unique_ptr<std::vector<char>> p_data = p_resource_manager->loadFile(filepath);
		if (nullptr == p_data)
			return nullptr; // texture not loaded

		// allocate texture and make shared pointer to it with custom deletor for removing TextureCacheEntry from texture_cache
		TextureDeleter tex_deleter(this, filepath);
		std::shared_ptr<sf::Texture> p_tex = std::shared_ptr<sf::Texture>(new sf::Texture(), tex_deleter);

		if (true == p_tex->loadFromMemory(p_data->data(), p_data->size()))
		{
			// add texture to map
			texture_cache[filepath].filepath = filepath;
			texture_cache[filepath].p_tex = p_tex;
		}

		return p_tex;	// return p_tex, wether or not it is valid or nullptr
	}
	else
		return iter->second.p_tex.lock();
}

//bool TextureManager::unloadTexture(std::string filepath)
//{
//	// check map for texture ptr
//	//	\ if present and ref count is 1, then the only item using it is the map, and it can be removed from the map (and therefore deallocated)
//	std::unordered_map<std::string, std::shared_ptr<sf::Texture>>::iterator iter = texture_map.find("filepath");
//	if (texture_map.end() == iter)
//		return false;	// texture not in map
//
//	else
//	{
//		// iter->second is the shared pointer to the texture (first is key, second is value)
//		if (iter->second.use_count() == 1)
//		{
//			// only the map has ownership of the texture, it can be deallocated
//			texture_map.erase(iter);
//			return true;
//		}
//		else
//			return false;	// something else has ownership of the texture, it will not be removed
//	}
//}

void TextureManager::TextureDeleter::operator()(sf::Texture* p_tex)
{
	delete p_tex;
	p_texture_manager->removeTextureCacheEntry(filepath);
}
