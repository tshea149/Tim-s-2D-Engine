#include "TestMusicComponent.h"

bool TestMusicComponent::playMusicComponent(std::string music_filepath)
{
	MusicComponent mc;
	if (mc.setTrack(music_filepath))
	{
		mc.setLoop(true);
		mc.setVolume(7.0f);
		mc.play();
		return true;
	}
	else
		return false;
}