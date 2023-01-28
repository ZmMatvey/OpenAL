#ifndef SOUNDEFFECTSPLAYER_H
#define SOUNDEFFECTSPLAYER_H

#include <al.h>

class SoundEffectsPlayer final
{
private:
	ALuint p_Source;
	ALuint p_Buffer = 0;

	int* copy;
	
public:
	SoundEffectsPlayer();

	SoundEffectsPlayer(const SoundEffectsPlayer& a);
	SoundEffectsPlayer operator=(const SoundEffectsPlayer& a);
	~SoundEffectsPlayer();

	void Play(ALuint buffer_to_play);
	void Stop() const;
	void Pause() const;
	void Resume() const;

	void SetBufferToPlay(ALuint buffer_to_play);
	void SetPitch(float val) const;
	void SetGain(float val) const;
	void SetMaxDistance(float val) const;
	void SetRolloffFactor(float val) const;
	void SetReferenceDistance(float val) const;
	void SetMinGain(float val) const;
	void SetMaxGain(float val) const;
	void SetConeOuterGain(float val) const;
	void SetConeInnerAngle(float val) const;
	void SetConeOuterAngle(float val) const;
	void SetPosition(const float vec[3]) const;
	void SetVelocity(const float vec[3]) const;
	void SetDirection(const float vec[3]) const;
	void SetSourceRelative(bool rel = true) const;
	void SetLooping(bool loop = true) const;

	bool isPlaying() const;

};

#endif //!SOUNDEFFECTSPLAYER_H
