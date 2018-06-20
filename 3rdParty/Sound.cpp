#include "Sound.h"
#include "System.h"
#include "Assert.h"

static const unsigned int g_maxNumberOfSounds = 16;
struct Sample
{
    Uint8* data;
    Uint32 position;
    Uint32 length;
} g_sounds[g_maxNumberOfSounds];

void
mixaudio(void *unused, Uint8 *stream, int len)
{
    Uint32 amount;
	unused = unused;

    for (unsigned int i = 0; i < g_maxNumberOfSounds; ++i) 
	{
        amount = (g_sounds[i].length - g_sounds[i].position);
        if ( (int)amount > len ) 
		{
            amount = len;
        }
        SDL_MixAudio(stream, &g_sounds[i].data[g_sounds[i].position], amount, SDL_MIX_MAXVOLUME);
        g_sounds[i].position += amount;
    }
}

void
Sound::init()
{
    for (unsigned int i = 0; i < g_maxNumberOfSounds; ++i) 
	{
		g_sounds[i].data = 0;
		g_sounds[i].position = 0;
		g_sounds[i].length = 0;
	}
}

Sound::Sound()
{
	m_audioCvt.buf = 0;
}

Sound::~Sound()
{
	delete[] m_audioCvt.buf;
}

void
Sound::loadWav(const std::string& filename)
{
    SDL_AudioSpec audioSpec;
    Uint8 *audioBuffer;
    Uint32 audioLength;
	
    ASSERT_RESULT_DECL(const SDL_AudioSpec* audioSpecPtr, SDL_LoadWAV(filename.c_str(), &audioSpec, &audioBuffer, &audioLength));
	ASSERT_DESCRIPTION(audioSpecPtr, "SDL_LoadWAV failed: " << SDL_GetError());

	ASSERT_RESULT_DECL(const int sdlBuildAudioResult, SDL_BuildAudioCVT(&m_audioCvt, audioSpec.format, audioSpec.channels, 
																		audioSpec.freq, AUDIO_S16, 2, 22050));
	ASSERT_DESCRIPTION(sdlBuildAudioResult != 0, "SDL_BuildAudioCVT failed: " << SDL_GetError());

	m_audioCvt.len = audioLength;
	m_audioCvt.buf = new Uint8[audioLength * m_audioCvt.len_mult];
    memcpy(m_audioCvt.buf, audioBuffer, audioLength);
    
	ASSERT_RESULT_DECL(const int sdlConvertAudioResult, SDL_ConvertAudio(&m_audioCvt));
	ASSERT_DESCRIPTION(sdlConvertAudioResult == 0, "SDL_ConvertAudio failed: " << SDL_GetError());
   
	SDL_FreeWAV(audioBuffer);
 }

void
Sound::play() const
{
	unsigned int index;
    /* Look for an empty (or finished) sound slot */
    for (index = 0; index < g_maxNumberOfSounds; ++index) 
	{
        if (g_sounds[index].position == g_sounds[index].length) 
		{
            break;
        }
    }

	if (index == g_maxNumberOfSounds)
	{
        return;
	}

     /* Put the sound data in the slot (it starts playing immediately) */
    if (g_sounds[index].data) 
	{
        delete[] g_sounds[index].data;
    }
    
	SDL_LockAudio();
		g_sounds[index].length = m_audioCvt.len_cvt;
		g_sounds[index].position = 0;
		g_sounds[index].data = new Uint8[m_audioCvt.len_cvt];
		memcpy(g_sounds[index].data, m_audioCvt.buf, m_audioCvt.len_cvt);
    SDL_UnlockAudio();
}
