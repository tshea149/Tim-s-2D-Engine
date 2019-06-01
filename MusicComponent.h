/* Author: Tim */
#ifndef MUSICCOMPONENT_H
#define MUSICCOMPONENT_H

#include <SFML/Audio/Music.hpp>

// This class should be accessed through direct pointers instead of handles
//	\ because MusicComponents are managed and accessed only by their respective owner
//		\ there is no class to organize, create, or manage MusicComponents
class MusicComponent
{
private:
	// music is a bit different than other resources, as it is streamed from a file.
	// Even though it is a resource, it doesn't make sense to load a large music file into main memory.
	// TODO: it needs to be streamed from a file into a custom input stream and given to a Music object
	sf::Music music;

public:
	MusicComponent();
	
	// no constructor taking filepath to set track, as there is no way of telling if success or failure doing so

	// changes the music track. Returns true/false on success/failure
	bool setTrack(std::string filepath);

	// 0 to 100
	void setVolume(float vol);
	void setLoop(bool tf);
	void play();
	void pause();
	void stop();
};

#endif // !MUSICCOMPONENT_H
