/* Author: Tim */
#ifndef SOUNDCOMPONENT_H
#define SOUNDCOMPONENT_H

#include <SFML/Audio/Sound.hpp>
#include <string>

class SoundComponent
{
private:
	sf::Sound sound;

	// a SoundBuffer is a resource (as it is loaded from the resource file), and multiple sounds can use the same SoundBuffer
	// therefore it will be accessed through the ResourceManager
	sf::SoundBuffer* sound_buffer;

public:
	SoundComponent();
	bool setSound(std::string filename);

	// 0 to 100
	void setVolume(float vol);
	void play();
	void stop();


};



#endif // !SOUNDCOMPONENT_H


