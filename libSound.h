#ifndef LIBSOUND_H_INCLUDED
#define LIBSOUND_H_INCLUDED


#include <iostream>
#include <cstdlib>
#include <string>

#include <allegro.h>
#include <fmodex/fmod.hpp>
#include <fmodex/fmod_errors.h>

// define the modes that will define what will be played
#define MENUSFX 1
#define MAINSFX 2
#define DISTORTSFX 3
#define CUTSCSFX 4

#define REPEAT 10
#define NORMAL 20

// sfx_functions
void init_sfx(FMOD::System*& inpSystem, FMOD_RESULT &inpResult);
void create_sfx_instances(FMOD::System*& inpSystem, FMOD_RESULT &inpResult, FMOD::Sound*& inpSfxState, int mode, int playMode);
void play_sfx(FMOD::System*& inpSystem, FMOD_RESULT &inpResult, FMOD::Sound*& inpSfxState, FMOD::Channel*& inpChannel);
void stop_play_sfx(FMOD::Channel*& inpPlayChannel, FMOD_RESULT &inpResult);
void destroy_sfx_instances(FMOD::System*& inpSystem, FMOD::Sound*& inpSfxState, FMOD_RESULT &inpResult, FMOD::Channel*& inpPlayChannel);
void reset_play_sfx_pos(FMOD::Channel*& inpChannel, FMOD_RESULT &inpResult);

// experimentation
void release_channel(FMOD::System*& inpSystem, FMOD_RESULT &inpResult, FMOD::Channel*& inpChannel);


// internal sfx functions
void _sfx_error_check_(FMOD_RESULT &inpResult);

#endif
