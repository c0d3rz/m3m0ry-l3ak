#ifndef LIBSOUND_H_INCLUDED
#define LIBSOUND_H_INCLUDED


#include <iostream>
#include <cstdlib>
#include <stdio.h>

#include <fmodex/fmod.hpp>
#include <fmodex/fmod_errors.h>
#include "libGraphics.h"

#define MENUSND "./msdata/menusnd.wav"
#define FIRSTSND "./msdata/lvlzsnd.wav" // have to change them
#define MENU 99
#define FSND 0

// class concept -- hope this works out
class sndfx
{
    public:
        void init_load_sound(); // initialize and load the sounds
        void play_sound(int mode);  // play the specific sound
        void stop_sound(int mode);  // stop that specific sound -- free the channel
        void destroy_sound_instances(); // release all the channels and the sounds as well as the system
        bool isPlaying(int mode);   // check channel.isPlaying()
        // write the code for the isPLaying() function


        // sound module is semi complete -- but work will go on in this respect
        // now for the acceptance of the username and the playing of the keysounds -- key presses
        // need some function to pause the sound and also some bool isPlaying(&channel) type function

    private:
        FMOD::System *system;
        FMOD::Channel *channel;
        FMOD::Sound *menuSound;
        FMOD::Sound *firstSound;
        FMOD_RESULT result;

        void error_check(FMOD_RESULT result);
};
// Aim : just play the menu snd as of now

#endif
