#ifndef MUSICBUFFER_H
#define MUSICBUFFER_H

#include <al.h>
#include <sndfile.h>

class MusicBuffer final
{
private:
	ALuint p_Source;
	static const int BUFFER_SAMPLES = 8192;
	static const int NUM_BUFFERS = 4;
	ALuint p_Buffers[NUM_BUFFERS];
	SNDFILE* p_SndFile;
	SF_INFO p_Sfinfo;
	short* p_Membuf;
	ALenum p_Format;

public:
	MusicBuffer() = delete;
	MusicBuffer(const char* filename);

	MusicBuffer(const MusicBuffer& a) = delete;
	MusicBuffer operator=(const MusicBuffer& a) = delete;
	~MusicBuffer();

	void Play() const;
	void Pause() const;
	void Stop() const;
	void Resume() const;

	void UpdateBufferStream() const;

	ALint GetSource() const;

	bool isPlaying() const;

	void SetGain(float val) const;
};

#endif //!MUSICBUFFER_H

