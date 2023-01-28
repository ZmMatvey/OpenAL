#ifndef OPENALERRORCHECK_H
#define OPENALERRORCHECK_H

#include <alc.h>
#include <al.h>

static void ALC_CheckAndThrow(ALCdevice* device) {
	if (alcGetError(device) != ALC_NO_ERROR)
		throw("error with alcDevice");
}

static void AL_CheckAndThrow() {
	if (alGetError() != AL_NO_ERROR)
		throw("error with al");
}

#endif //!OPENALERRORCHECK_H