#include "MusicComponent.h"
#include "AssetManager.h"

MusicComponent::MusicComponent()
{

}

bool MusicComponent::setTrack(std::string filepath)
{
	return music.openFromFile(filepath);
}

void MusicComponent::setVolume(float vol)
{
	music.setVolume(vol);
}

void MusicComponent::setLoop(bool tf)
{
	music.setLoop(tf);
}

void MusicComponent::play()
{
	music.play();
}

void MusicComponent::pause()
{
	music.pause();
}

void MusicComponent::stop()
{
	music.stop();
}
