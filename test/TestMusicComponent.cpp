#include "TestMusicComponent.h"
#include <iostream>

bool TestMusicComponent::playMusicComponent(std::string music_filepath)
{
	MusicComponent mc;
	if (mc.setTrack(music_filepath))
	{
		mc.setLoop(true);
		mc.setVolume(7.0f);
		mc.play();
		while (1)
		{			
			std::cout << "Testing music. On key-press the music object will go out of scope and the music will stop." << std::endl;
			system("pause");
			break;
		}
		return true;
	}
	else
		return false;
}