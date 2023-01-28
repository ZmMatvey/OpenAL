#ifndef SOUNDEFFECTSLIBRARY_H
#define SOUNDEFFECTSLIBRARY_H

#include <al.h>
#include <vector>

/// <summary>
/// SoundEffectsLibrary: Singleton class that keeps track of the shorter sounds
/// we've loaded into memory. Use the Play function from an instantiation of the
/// SoundEffectsPlayer on an ID returned from the load function.
/// 
/// load function: Use the SE_LOAD(...) function to add sounds, programmer should keep track of
/// the returned ALuint to use the sound.
/// 
/// unload function: Use SE_UNLOAD(...) remove sounds from memory. 
/// 
/// </summary>

class SoundEffectsLibrary 
{
private:
	std::vector<ALuint> p_SoundEffectBuffers;

public:
	SoundEffectsLibrary();

	SoundEffectsLibrary(const SoundEffectsLibrary& a) = delete;
	SoundEffectsLibrary operator=(const SoundEffectsLibrary& a) = delete;
	~SoundEffectsLibrary();

	ALuint Load(const char* filename);
	bool UnLoad(const ALuint& bufferId);

	ALuint operator[] (int i) const;

};

#endif //!SOUNDEFFECTSLIBRARY_H

