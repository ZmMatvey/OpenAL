#include "SoundDevice.h"
#include "OpenALErrorCheck.h"

#include <stdio.h>

SoundDevice::SoundDevice(const char* name_device) : copy(new int(0)) {
	p_ALCDevice = alcOpenDevice(name_device); // nullptr = get default device
	if (!p_ALCDevice)
		throw("failed to get sound device");
	
	p_ALCContext = alcCreateContext(p_ALCDevice, nullptr);  // create context
	if (!p_ALCContext)
		throw("failed to set sound context");

	const ALCchar* name = nullptr;
	if (alcIsExtensionPresent(p_ALCDevice, "ALC_ENUMERATE_ALL_EXT"))
		name = alcGetString(p_ALCDevice, ALC_ALL_DEVICES_SPECIFIER);
	if (!name || alcGetError(p_ALCDevice) != AL_NO_ERROR)
		name = alcGetString(p_ALCDevice, ALC_DEVICE_SPECIFIER);
	printf("Opened \%s""\n", name);
}

SoundDevice::SoundDevice(const SoundDevice& a) 
	: p_ALCDevice(a.p_ALCDevice), p_ALCContext(a.p_ALCContext), copy(a.copy) {
	(*copy)++;
}

SoundDevice SoundDevice::operator=(const SoundDevice& a) {
	this->~SoundDevice();

	p_ALCDevice = a.p_ALCDevice;
	p_ALCContext = a.p_ALCContext;
	copy = a.copy;
	(*copy)++;

	return *this;
}

SoundDevice::~SoundDevice() {
	if (*copy == 0) {
		alcMakeContextCurrent(nullptr);
		alcDestroyContext(p_ALCContext);
		alcCloseDevice(p_ALCDevice);

		delete copy;
	}
	else {
		(*copy)--;
	}
}

bool SoundDevice::MakeContextCurrent() const {
	return alcMakeContextCurrent(p_ALCContext);
}

const char* SoundDevice::GetName() const {
	return alcGetString(p_ALCDevice, ALC_DEVICE_SPECIFIER);
}

/// <summary>
/// Gets the listeners current locaiton.
/// </summary>
/// <param name="x">return value x</param>
/// <param name="y">return value y</param>
/// <param name="z">return value z</param>
void SoundDevice::GetLocation(float vec[3]) {
	alGetListener3f(AL_POSITION, &vec[0], &vec[1], &vec[2]);
}

void SoundDevice::GetVelocity(float vec[3]) {
	alGetListener3f(AL_VELOCITY, &vec[0], &vec[1], &vec[2]);
}

/// <summary>
/// Gets the current listener Orientation as 'at' and 'up'
/// </summary>
/// <param name="ori"> Return value: Must be a float array with 6 slots available ex: float myvar[6]</param>
void SoundDevice::GetOrientation(float ori[6]) {
	alGetListenerfv(AL_ORIENTATION, ori);
}

/// <summary>
/// Gets the current volume of our listener.
/// </summary>
/// <returns>current volume</returns>
void SoundDevice::GetGain(float& a) {
	alGetListenerf(AL_GAIN, &a);
}

/// <summary>
/// Sets the Attunation Model.
/// </summary>
/// <param name="key">
///#define AL_INVERSE_DISTANCE                      0xD001
///#define AL_INVERSE_DISTANCE_CLAMPED              0xD002
///#define AL_LINEAR_DISTANCE                       0xD003
///#define AL_LINEAR_DISTANCE_CLAMPED               0xD004
///#define AL_EXPONENT_DISTANCE                     0xD005
///#define AL_EXPONENT_DISTANCE_CLAMPED             0xD006
/// </param>
void SoundDevice::SetAttunation(int key) {
	if (key < 0xD001 || key > 0xD006)
		throw("bad attunation key");

	alDistanceModel(key);
	AL_CheckAndThrow();
}

/// <summary>
/// Sets the location of our listener
/// </summary> 
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
void SoundDevice::SetLocation(const float vec[3]) {
	alListener3f(AL_POSITION, vec[0], vec[1], vec[2]);
}

void SoundDevice::SetVelocity(const float vec[3]) {
	alListener3f(AL_VELOCITY, vec[0], vec[1], vec[2]);
}

/// <summary>
/// Sets the orientation of our listener using 'look at' (or foward vector) and 'up' direction
/// </summary>
/// <param name="atx"></param>
/// <param name="aty"></param>
/// <param name="atz"></param>
/// <param name="upx"></param>
/// <param name="upy"></param>
/// <param name="upz"></param>
void SoundDevice::SetOrientation(const float ori[6]) {
	alListenerfv(AL_ORIENTATION, ori);
}

/// <summary>
/// Sets the master volume of our listeners. capped between 0 and 5 for now.
/// </summary>
/// <param name="val"></param>
void SoundDevice::SetGain(float val) {
	// clamp between 0 and 5
	float newVol = val;
	if (newVol < 0.0f)
		newVol = 0.0f;
	else if (newVol > 5.0f)
		newVol = 5.0f;

	alListenerf(AL_GAIN, newVol);
}