/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** Core functions implementation: audio routines
*/


// This is just enough to get Hammerfight working without using libBASS.
//  If you want a full HGE audio implementation, you should either use the
//  code in sound_libbass.cpp (and maybe pay for a BASS license), or improve
//  this code.


#include "hge_impl.h"

#include "AL/al.h"
#include "AL/alc.h"
#include "ogg/ogg.h"
#include "vorbis/vorbisfile.h"

// ogg i/o callbacks.
struct oggcbdata
{
	const BYTE *data;
	DWORD size;
	DWORD pos;
};

static size_t oggcb_read(void *ptr, size_t size, size_t nmemb, void *datasource)
{
	oggcbdata *data = (oggcbdata *) datasource;
	const DWORD avail = data->size - data->pos;
	size_t want = nmemb * size;
	if (want > avail)
		want = avail - (avail % size);
	if (want > 0)
	{
		memcpy(ptr, data->data + data->pos, want);
		data->pos += want;
	}
	return want / size;
}

static int oggcb_seek(void *datasource, ogg_int64_t offset, int whence)
{
	oggcbdata *data = (oggcbdata *) datasource;
	ogg_int64_t pos = 0;
	switch (whence)
	{
		case SEEK_SET: pos = offset; break;
		case SEEK_CUR: pos = ((ogg_int64_t) data->pos) + offset; break;
		case SEEK_END: pos = ((ogg_int64_t) data->size) + offset; break;
		default: return -1;
	}

	if ( (pos < 0) || (pos > ((ogg_int64_t) data->size)) )
		return -1;

	data->pos = (DWORD) pos;
	return 0;
}

static int oggcb_close(void *datasource)
{
	return 0; // no-op.
}

static long oggcb_tell(void *datasource)
{
	oggcbdata *data = (oggcbdata *) datasource;
	return (long) data->pos;
}

static ov_callbacks oggcb = { oggcb_read, oggcb_seek, oggcb_close, oggcb_tell };

static void *decompress_vorbis(const BYTE *data, const DWORD size, ALsizei *decompressed_size, ALenum *fmt, ALsizei *freq)
{
#ifdef __POWERPC__
	const int bigendian = 1;
#else
	const int bigendian = 0;
#endif

	oggcbdata cbdata = { data, size, 0 };
	OggVorbis_File vf;
	memset(&vf, '\0', sizeof (vf));
	if (ov_open_callbacks(&cbdata, &vf, NULL, 0, oggcb) == 0)
    {
        int bitstream = 0;
        vorbis_info *info = ov_info(&vf, -1);

        *decompressed_size = 0;
        *fmt = (info->channels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
        *freq = info->rate;

        if ((info->channels != 1) && (info->channels != 2))
        {
            ov_clear(&vf);
            return NULL;
        }

        char buf[1024 * 16];
        long rc = 0;
        size_t allocated = 64 * 1024;
        BYTE *retval = (ALubyte *) malloc(allocated);
        while ( (rc = ov_read(&vf, buf, sizeof (buf), bigendian, 2, 1, &bitstream)) != 0 )
        {
            if (rc > 0)
            {
                *decompressed_size += rc;
                if (*decompressed_size >= allocated)
                {
                    allocated *= 2;
                    ALubyte *tmp = (ALubyte *) realloc(retval, allocated);
                    if (tmp == NULL)
                    {
                        free(retval);
                        retval = NULL;
                        break;
                    }
                    retval = tmp;
                }
                memcpy(retval + (*decompressed_size - rc), buf, rc);
            }
        }
        ov_clear(&vf);
        return retval;
    }

    return NULL;
}

#define MAX_SIDS 128
static int sidcount = 0;
static ALuint sids[MAX_SIDS];  // !!! FIXME: this is sort of hacky.

static ALuint get_source()
{
    for (int i = 0; i < sidcount; i++)
    {
        ALint state = AL_PLAYING;
        alGetSourceiv(sids[i], AL_SOURCE_STATE, &state);
        if ((state != AL_PLAYING) && (state != AL_PAUSED))
            return sids[i];
    }
    if (sidcount >= MAX_SIDS)
        return 0;

    ALuint sid = 0;
    alGenSources(1, &sid);
    if (sid == 0)
        return 0;
    sids[sidcount++] = sid;
    return sid;
}


HEFFECT CALL HGE_Impl::Effect_Load(const char *filename, DWORD size)
{
	DWORD _size, length, samples;
	void *data;

	if(hOpenAL)
	{
		if(bSilent) return 1;

		if(size) { data=(void *)filename; _size=size; }
		else
		{
			data=Resource_Load(filename, &_size);
			if(!data) return 0;
		}

		const BYTE *magic = (const BYTE *) data;
		const bool isOgg = ( (_size > 4) &&
		                     (magic[0] == 'O') && (magic[1] == 'g') &&
		                     (magic[2] == 'g') && (magic[3] == 'S') );

		// !!! FIXME: we currently expect Ogg Vorbis, since this is all we
		// !!! FIXME:  need at the moment.
		if (!isOgg)
		{
			if(!size) Resource_Free(data);
			return 0;
		}

		// !!! FIXME: alternately, stream ogg data?
		void *allocation_decompressed = NULL;
		void *decompressed = NULL;
		ALsizei decompressed_size = 0;
		ALsizei freq = 0;
		ALenum fmt = AL_FORMAT_STEREO16;
		if (isOgg)
		{
			if (alIsExtensionPresent((const ALchar *) "AL_EXT_vorbis"))
			{
				fmt = alGetEnumValue((const ALchar *) "AL_FORMAT_VORBIS_EXT");
				decompressed = data;
				decompressed_size = _size;
			}
			else
			{
				allocation_decompressed = decompress_vorbis((const BYTE *) data, _size, &decompressed_size, &fmt, &freq);
				decompressed = allocation_decompressed;
			}
		}

		ALuint bid = 0;
		alGenBuffers(1, &bid);
		alBufferData(bid, fmt, decompressed, decompressed_size, freq);
		free(allocation_decompressed);  // not delete[] !
		if(!size) Resource_Free(data);
		return (HEFFECT) bid;
	}
	else return 0;
}

HCHANNEL CALL HGE_Impl::Effect_Play(HEFFECT eff)
{
	return Effect_PlayEx(eff, 100, 0, 1.0f, false);
}

HCHANNEL CALL HGE_Impl::Effect_PlayEx(HEFFECT eff, int volume, int pan, float pitch, bool loop)
{
	if(hOpenAL)
	{
		const ALuint sid = get_source(); // find an unused sid, or generate a new one.
		if (sid != 0)
		{
			if (volume < 0) volume = 0; else if (volume > 100) volume = 100;
			if (pan < -100) pan = -100; else if (pan > 100) pan = 100;
			alSourceStop(sid);
			alSourcei(sid, AL_BUFFER, (ALint) eff);
			alSourcef(sid, AL_GAIN, ((ALfloat) volume) / 100.0f);
			alSourcef(sid, AL_PITCH, pitch);
			alSource3f(sid, AL_POSITION, ((ALfloat) pan) / 100.0f, 0.0f, 0.0f);
			alSourcei(sid, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
			alSourcePlay(sid);
		}
		return sid;
	}
	else return 0;
}


void CALL HGE_Impl::Effect_Free(HEFFECT eff)
{
	if(hOpenAL)
	{
		ALuint bid = (ALuint) eff;
		alDeleteBuffers(1, &bid);
	}
}


HMUSIC CALL HGE_Impl::Music_Load(const char *filename, DWORD size)
{
	assert(false && "write me"); return 0;  // !!! FIXME: MOD (etc) music unsupported at the moment.
}

HCHANNEL CALL HGE_Impl::Music_Play(HMUSIC mus, bool loop, int volume, int order, int row)
{
	assert(false && "write me"); return 0;  // !!! FIXME: MOD (etc) music unsupported at the moment.
}

void CALL HGE_Impl::Music_Free(HMUSIC mus)
{
	assert(false && "write me"); // !!! FIXME: MOD (etc) music unsupported at the moment.
}

void CALL HGE_Impl::Music_SetAmplification(HMUSIC music, int ampl)
{
	assert(false && "write me"); // !!! FIXME: MOD (etc) music unsupported at the moment.
}

int CALL HGE_Impl::Music_GetAmplification(HMUSIC music)
{
	assert(false && "write me"); return -1;  // !!! FIXME: MOD (etc) music unsupported at the moment.
}

int CALL HGE_Impl::Music_GetLength(HMUSIC music)
{
	assert(false && "write me"); return -1;  // !!! FIXME: MOD (etc) music unsupported at the moment.
}

void CALL HGE_Impl::Music_SetPos(HMUSIC music, int order, int row)
{
	assert(false && "write me"); // !!! FIXME: MOD (etc) music unsupported at the moment.
}

bool CALL HGE_Impl::Music_GetPos(HMUSIC music, int *order, int *row)
{
	assert(false && "write me"); return false;  // !!! FIXME: MOD (etc) music unsupported at the moment.
}

void CALL HGE_Impl::Music_SetInstrVolume(HMUSIC music, int instr, int volume)
{
	assert(false && "write me"); // !!! FIXME: MOD (etc) music unsupported at the moment.
}

int CALL HGE_Impl::Music_GetInstrVolume(HMUSIC music, int instr)
{
	assert(false && "write me"); return -1;  // !!! FIXME: MOD (etc) music unsupported at the moment.
}

void CALL HGE_Impl::Music_SetChannelVolume(HMUSIC music, int channel, int volume)
{
	assert(false && "write me"); // !!! FIXME: MOD (etc) music unsupported at the moment.
}

int CALL HGE_Impl::Music_GetChannelVolume(HMUSIC music, int channel)
{
	assert(false && "write me"); return -1;  // !!! FIXME: MOD (etc) music unsupported at the moment.
}

HSTREAM CALL HGE_Impl::Stream_Load(const char *filename, DWORD size)
{
	assert(false && "write me"); return 0; // !!! FIXME: streaming unsupported at the moment.
}

void CALL HGE_Impl::Stream_Free(HSTREAM stream)
{
	assert(false && "write me");  // !!! FIXME: streaming unsupported at the moment.
}

HCHANNEL CALL HGE_Impl::Stream_Play(HSTREAM stream, bool loop, int volume)
{
	assert(false && "write me"); return 0; // !!! FIXME: streaming unsupported at the moment.
}

void CALL HGE_Impl::Channel_SetPanning(HCHANNEL chn, int pan)
{
	assert(pan >= -100);
	assert(pan <= 100);
	if(hOpenAL)
	{
		alSource3f((ALuint) chn, AL_POSITION, ((ALfloat) pan) / 100.0f, 0.0f, 0.0f);
	}
}

void CALL HGE_Impl::Channel_SetVolume(HCHANNEL chn, int volume)
{
	if(hOpenAL)
	{
		if (volume < 0) volume = 0; else if (volume > 100) volume = 100;
		alSourcef((ALuint) chn, AL_GAIN, ((ALfloat) volume) / 100.0f);
	}
}

void CALL HGE_Impl::Channel_SetPitch(HCHANNEL chn, float pitch)
{
	if(hOpenAL)
	{
		alSourcef((ALuint) chn, AL_PITCH, pitch);
	}
}

void CALL HGE_Impl::Channel_Pause(HCHANNEL chn)
{
	if(hOpenAL)
	{
		alSourcePause((ALuint) chn);
	}
}

void CALL HGE_Impl::Channel_Resume(HCHANNEL chn)
{
	if(hOpenAL)
	{
		alSourcePlay((ALuint) chn);
	}
}

void CALL HGE_Impl::Channel_Stop(HCHANNEL chn)
{
	if(hOpenAL)
	{
		alSourceStop((ALuint) chn);
	}
}

void CALL HGE_Impl::Channel_PauseAll()
{
	if(hOpenAL)
	{
		ALCcontext *ctx = alcGetCurrentContext();
		alcSuspendContext(ctx);
	}
}

void CALL HGE_Impl::Channel_ResumeAll()
{
	if(hOpenAL)
	{
		ALCcontext *ctx = alcGetCurrentContext();
		alcProcessContext(ctx);
	}
}

void CALL HGE_Impl::Channel_StopAll()
{
	if(hOpenAL)
	{
		for (int i = 0; i < sidcount; i++)
			alSourceStop(sids[i]);
	}
}

bool CALL HGE_Impl::Channel_IsPlaying(HCHANNEL chn)
{
	if(hOpenAL)
	{
		ALint state = AL_STOPPED;
		alGetSourceiv((ALuint) chn, AL_SOURCE_STATE, &state);
		return state == AL_PLAYING;
	}
	else return false;
}

float CALL HGE_Impl::Channel_GetLength(HCHANNEL chn) {
	assert(false && "write me"); return -1.0f;
}

float CALL HGE_Impl::Channel_GetPos(HCHANNEL chn) {
	assert(false && "write me"); return -1.0f;
}

void CALL HGE_Impl::Channel_SetPos(HCHANNEL chn, float fSeconds) {
	assert(false && "write me");
}

void CALL HGE_Impl::Channel_SlideTo(HCHANNEL channel, float time, int volume, int pan, float pitch)
{
	assert(false && "write me");
}

bool CALL HGE_Impl::Channel_IsSliding(HCHANNEL channel)
{
	assert(false && "write me"); return false;
}


//////// Implementation ////////


bool HGE_Impl::_SoundInit()
{
	if(!bUseSound || hOpenAL) return true;

	bSilent=false;

	sidcount = 0;
	memset(sids, '\0', sizeof (sids));

    System_Log("Starting OpenAL init");

	ALCdevice *dev = alcOpenDevice(NULL);
	if (!dev)
	{
		System_Log("alcOpenDevice(NULL) failed, using no sound");
		bSilent=true;
		return true;
	}

	ALint caps[] = { ALC_FREQUENCY, nSampleRate, 0 };
	ALCcontext *ctx = alcCreateContext(dev, caps);
	if (!ctx)
	{
		alcCloseDevice(dev);
		System_Log("alcCreateContext(NULL) failed, using no sound");
		bSilent=true;
		return true;
	}

	alcMakeContextCurrent(ctx);
	alcProcessContext(ctx);

    System_Log("OpenAL initialized");
    System_Log("AL_VENDOR: %s", (char *) alGetString(AL_VENDOR));
    System_Log("AL_RENDERER: %s", (char *) alGetString(AL_RENDERER));
    System_Log("AL_VERSION: %s", (char *) alGetString(AL_VERSION));
    System_Log("AL_EXTENSIONS: %s", (char *) alGetString(AL_EXTENSIONS));

	hOpenAL = (void *) 0x1;   // something non-NULL (!!! FIXME: this should eventually be a library handle).

	_SetFXVolume(nFXVolume);
	//_SetMusVolume(nMusVolume);
	//_SetStreamVolume(nStreamVolume);

	return true;
}

void HGE_Impl::_SoundDone()
{
	CStreamList *stmItem=streams, *stmNext;

	if(hOpenAL)
	{
		for (int i = 0; i < sidcount; i++)
			alSourceStop(sids[i]);
		alDeleteSources(sidcount, sids);
		sidcount = 0;
		memset(sids, '\0', sizeof (sids));

		ALCcontext *ctx = alcGetCurrentContext();
		ALCdevice *dev = alcGetContextsDevice(ctx);
		alcMakeContextCurrent(NULL);
		alcSuspendContext(ctx);
		alcDestroyContext(ctx);
		alcCloseDevice(dev);

		hOpenAL=0;

		while(stmItem)
		{
			stmNext=stmItem->next;
			Resource_Free(stmItem->data);
			delete stmItem;
			stmItem=stmNext;
		}
		streams=0;
	}
}

void HGE_Impl::_SetMusVolume(int vol)
{
	assert(false && "write me");
}

void HGE_Impl::_SetStreamVolume(int vol)
{
	assert(false && "write me");
}

void HGE_Impl::_SetFXVolume(int vol)
{
	if(hOpenAL)
	{
		alListenerf(AL_GAIN, ((ALfloat) vol) / 100.0f);
	}
}
