#include "RenderComponent.h"
#include "AssetManager.h"
#include "RenderEngine.h"

#if _DEBUG
#include "Debug.h"
#endif

void RenderComponent::setLocation(sf::Vector2f new_location)
{
	sprite.setPosition(new_location);
}

bool RenderComponent::setTexture(std::string texture_filepath)
{
	p_texture = AssetManager::getInstance()->getTexture(texture_filepath);

	if (nullptr == p_texture)
		return false;

	else
	{
		sprite.setTexture(*p_texture);
		return true;
	}
}

void RenderComponent::setLayer(RenderLayer layer)
{
	this->layer = layer;
}

void RenderComponent::setLayerPriority(LayerPriority layer_priority)
{
	this->layer_priority = layer_priority;
}

void RenderComponent::setVisibility(bool v)
{
	this->visible = v;
}

bool RenderComponent::isVisible()
{
	return this->visible;
}