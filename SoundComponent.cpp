#include "SoundComponent.h"

SoundComponent::SoundComponent()
{

}

bool SoundComponent::setSound(std::string filename)
{
	return false;
}

void SoundComponent::setVolume(float vol)
{
	sound.setVolume(vol);
}

void SoundComponent::play()
{
	sound.play();
}

void SoundComponent::stop()
{
	sound.stop();
}
