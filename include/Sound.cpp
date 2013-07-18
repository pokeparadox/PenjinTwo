/*
	Penjin is Copyright (c)2005, 2006, 2007, 2008, 2009, 2010 Kevin Winfield-Pantoja

	This file is part of Penjin.

	Penjin is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Penjin is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with Penjin.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "Sound.h"
#if !(PENJIN_NO_SOUND)
using Penjin::Sound;
void Penjin::SoundSystem::init()
{
#ifdef PLATFORM_GP2X
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, AUDIO_S16, MIX_DEFAULT_CHANNELS, 128);			// Initialize SDL_mixer for GP2X, buffer is set lower than PC
#elif PLATFORM_PC
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, AUDIO_S16, MIX_DEFAULT_CHANNELS, 512);		// Initialize SDL_mixer for PC, buffer is set higher
#elif PLATFORM_PANDORA
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, AUDIO_S16, MIX_DEFAULT_CHANNELS, 512);
#elif PLATFORM_DINGOO
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, AUDIO_S16, MIX_DEFAULT_CHANNELS, 256);
#else
#error "Audio setup is not defined for this platform!"
#endif
}

void Penjin::SoundSystem::deInit()
{
    Mix_CloseAudio();																// Close SDL_Mixer Audio
}

void Penjin::SoundSystem::setGlobalVolume(CRuint volume)
{
    Mix_Volume(-1,volume);
}

uint Penjin::SoundSystem::getGlobalVolume()
{
    return Mix_Volume(-1,-1);
}

void Penjin::SoundSystem::stopAll()
{
    Mix_HaltChannel(-1);
};

/// ---

Sound::Sound()
{
    sound = NULL;
    defLoops = 0;
    simultaneousPlay = false;
}

Sound::~Sound()
{
    freeAll();
}

void Sound::freeAll()
{
    if(sound)
    {
        for (int I = 0; I < instances.size(); ++I)
            if(isPlaying(I))
                stop(I);
        Mix_FreeChunk(sound);															// Release the memory allocated to sound
    }
    sound = NULL;
    instances.clear();
}

ERRORS Sound::load(CRstring soundName)
{
    freeAll();
    sound = Mix_LoadWAV(soundName.c_str());										// load sound.wav from sdcard

    if(sound)
        return PENJIN_OK;
    return PENJIN_FILE_NOT_FOUND;
}

void Sound::setVolume(CRuint volume, CRint id)
{
    if (id > (int)instances.size())
        return;
    if (id >= 0)
    {
        Mix_Volume(instances.at(id).first,volume);
    }
    else
    {
        for (int I = 0; I < instances.size(); ++I)
            Mix_Volume(instances.at(I).first,volume);
    }
}

uint Sound::getVolume(CRint id) const
{
    if (instances.size() == 0)
        return -1;
    int useID = id;
    if (id < 0 || id > instances.size()-1)
        useID = 0;
    return Mix_Volume(instances.at(useID).first,-1);
}

bool Sound::isPaused(CRint id) const
{
    if (instances.size() == 0 || id > (int)instances.size()-1 || id < -1)
        return false;
    else
    {
        if (id < 0)
        {
            for (vector<pair<int,int> >::const_iterator iter = instances.begin(); iter != instances.end(); ++iter)
                if (Mix_Paused(iter->first))
                    return true;
            return false;
        }
        else
            return Mix_Paused(instances.at(id).first);
    }
}

bool Sound::isPlaying(CRint id) const
{
    if (instances.size() == 0 || (int)id > (int)(instances.size()-1) || id < -1)
        return false;
    else
    {
        if (id < 0)
        {
            for (vector<pair<int,int> >::const_iterator iter = instances.begin(); iter != instances.end(); ++iter)
                if (Mix_Playing(iter->first))
                    return true;
            return false;
        }
        else
            return Mix_Playing(instances.at(id).first);
    }
}

void Sound::play(int loops, CRint id)
{
    if (simultaneousPlay)
    {
        // do some cleanup
        for (int I = 0; I < instances.size(); ++I)
            if (not isPlaying(I) && not isPaused(I))
                instances.erase(instances.begin()+I);
    }
    if (loops == -2)
        loops = defLoops;
    if(id < 0)
    {
        if (not simultaneousPlay && instances.size() > 0)
        {
            if (not isPlaying())
                Mix_PlayChannel(instances.begin()->first,sound,instances.begin()->second);
        }
        else
        {
            // Add another instance to the list
            int channel = Mix_PlayChannel(-1, sound, loops);
            if (channel != -1)
                instances.push_back(make_pair(channel,loops));
            // TODO: Spit out Penjin error string otherwise
        }
    }
    else if (isPaused(id))
        Mix_Resume(instances.at(id).first);
    else if (id < instances.size())
        Mix_PlayChannel(instances.at(id).first,sound,instances.at(id).second);
}

void Sound::pause(CRint id)
{
    if (id >= 0)
    {
        if(isPlaying(id))
            Mix_Pause(instances.at(id).first);
    }
    else
    {
        for (int I = 0; I < instances.size(); ++I)
            pause(I);
    }
}

void Sound::playPause(CRint id)
{
    if (id >= 0)
    {
        if(isPaused(id))
            play(id);
        else if(isPlaying(id))
            pause(id);
    }
    else
        playPause(0);
}

void Sound::stop(CRint id)
{
    if (id >= 0)
    {
        if(isPlaying(id))
            Mix_HaltChannel(instances.at(id).first);
    }
    else
    {
        for (int I = 0; I < instances.size(); ++I)
            stop(I);
    }
}
#endif
