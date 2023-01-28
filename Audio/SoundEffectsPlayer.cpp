#include "SoundEffectsPlayer.h"
#include "OpenALErrorCheck.h"

#include <iostream>

SoundEffectsPlayer::SoundEffectsPlayer() : copy(new int(0)) {
	alGenSources(1, &p_Source);
	alSourcei(p_Source, AL_BUFFER, p_Buffer);
	AL_CheckAndThrow();
}

SoundEffectsPlayer::SoundEffectsPlayer(const SoundEffectsPlayer& a) 
	 : p_Source(a.p_Source), p_Buffer(a.p_Buffer), copy(a.copy) {
	(*copy)++;
}

SoundEffectsPlayer SoundEffectsPlayer::operator=(const SoundEffectsPlayer& a) {
	this->~SoundEffectsPlayer();

	p_Source = a.p_Source;
	p_Buffer = a.p_Buffer;
	copy = a.copy;
	(*copy)++;

	return *this;
}

SoundEffectsPlayer::~SoundEffectsPlayer() {
	if (*copy == 0) {
		alDeleteSources(1, &p_Source);
		delete copy;
	}
	else {
		(*copy)--;
	}
}

void SoundEffectsPlayer::Play(ALuint buffer_to_play) {
	if (buffer_to_play != p_Buffer) {
			p_Buffer = buffer_to_play;
			alSourcei(p_Source, AL_BUFFER, (ALint)p_Buffer);
			AL_CheckAndThrow();
	}
	alSourcePlay(p_Source);
	AL_CheckAndThrow();
}

void SoundEffectsPlayer::Stop() const {
	alSourceStop(p_Source);
	AL_CheckAndThrow();
}

void SoundEffectsPlayer::Pause() const {
	alSourcePause(p_Source);
	AL_CheckAndThrow();
}

void SoundEffectsPlayer::Resume() const {
	alSourcePlay(p_Source);
	AL_CheckAndThrow();
}

void SoundEffectsPlayer::SetBufferToPlay(ALuint buffer_to_play) {
	if (buffer_to_play != p_Buffer) {
		p_Buffer = buffer_to_play;
		alSourcei(p_Source, AL_BUFFER, (ALint)p_Buffer);
		AL_CheckAndThrow();
	}
}

void SoundEffectsPlayer::SetPitch(float val) const {
	alSourcef(p_Source, AL_PITCH, val);
}

void SoundEffectsPlayer::SetGain(float val) const {
	alSourcef(p_Source, AL_GAIN, val);
}

void SoundEffectsPlayer::SetMaxDistance(float val) const {
	alSourcef(p_Source, AL_MAX_DISTANCE, val);
}

void SoundEffectsPlayer::SetRolloffFactor(float val) const {
	alSourcef(p_Source, AL_ROLLOFF_FACTOR, val);
}

void SoundEffectsPlayer::SetReferenceDistance(float val) const {
	alSourcef(p_Source, AL_REFERENCE_DISTANCE, val);
}

void SoundEffectsPlayer::SetMinGain(float val) const {
	alSourcef(p_Source, AL_MIN_GAIN, val);
}

void SoundEffectsPlayer::SetMaxGain(float val) const {
	alSourcef(p_Source, AL_MAX_GAIN, val);
}

void SoundEffectsPlayer::SetConeOuterGain(float val) const {
	alSourcef(p_Source, AL_CONE_OUTER_GAIN, val);
}

void SoundEffectsPlayer::SetConeInnerAngle(int val) const {
	alSourcei(p_Source, AL_CONE_INNER_ANGLE, val);
}

void SoundEffectsPlayer::SetConeOuterAngle(int val) const {
	alSourcei(p_Source, AL_CONE_OUTER_ANGLE, val);
}

void SoundEffectsPlayer::SetPosition(const float vec[3]) const {
	alSource3f(p_Source, AL_POSITION, vec[0], vec[1], vec[2]);
}

void SoundEffectsPlayer::SetVelocity(const float vec[3]) const {
	alSource3f(p_Source, AL_VELOCITY, vec[0], vec[1], vec[2]);
}

void SoundEffectsPlayer::SetDirection(const float vec[3]) const {
	alSource3f(p_Source, AL_DIRECTION, vec[0], vec[1], vec[2]);
}

void SoundEffectsPlayer::SetSourceRelative(bool rel) const {
	alSourcei(p_Source, AL_SOURCE_RELATIVE, (ALint)rel);
}

void SoundEffectsPlayer::SetLooping(bool loop) const {
	alSourcei(p_Source, AL_LOOPING, (ALint)loop);
}

bool SoundEffectsPlayer::isPlaying() const {
	ALint playState;
	alGetSourcei(p_Source, AL_SOURCE_STATE, &playState);
	return (playState == AL_PLAYING);
}
