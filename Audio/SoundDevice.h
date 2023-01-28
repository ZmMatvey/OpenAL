#ifndef SOUNDDEVICE_H
#define SOUNDDEVICE_H

#include <alc.h>

/// <summary>
/// Singleton class that initilizes our sound hardware device and allows
/// us to change our listener values.
/// </summary>

class SoundDevice
{
private:
	ALCdevice* p_ALCDevice;   //pointer to the speakers
	ALCcontext* p_ALCContext; //context for speakers
	
	int* copy;

public:
	//do not call from one name
	SoundDevice(const char* name_device = nullptr);

	SoundDevice(const SoundDevice& a);
	SoundDevice operator= (const SoundDevice& a);
	~SoundDevice();

	bool MakeContextCurrent() const;

	//parameters of the current context
	const char* GetName() const;

	static void GetLocation(float vec[3]);
	static void GetVelocity(float vec[3]);
	static void GetOrientation(float ori[6]);
	static void GetGain(float& a);

	static void SetAttunation(int key);
	static void SetLocation(const float vec[3]);
	static void SetVelocity(const float vec[3]);
	static void SetOrientation(const float ori[6]);
	static void SetGain(float val);
};

#endif //!SOUNDDEVICE_H

