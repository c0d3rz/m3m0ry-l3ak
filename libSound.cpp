#include "libSound.h"

using namespace std;

void sndfx::init_load_sound()
{
    result = FMOD::System_Create(&system);
    error_check(result);
    result = system->init(1024, FMOD_INIT_NORMAL, 0);    // later check about the values in this function
    // the values might be determining the sound volume and the like -- if it is -- create a cfg file
    // for this -- read the file and then populate the appropriate values
    error_check(result);

    // now load the sound for the menu
    result = system->createSound(MENUSND, FMOD_LOOP_NORMAL, 0, &menuSound);
    error_check(result);    // the file has been loaded now
    result = system->createSound(FIRSTSND, FMOD_LOOP_NORMAL, 0, &firstSound);
    error_check(result);
}

void sndfx::play_sound(int mode)
{
    switch(mode)
    {
        case MENU:
            // channel free is something that I will be using in this case
            result = system->playSound(FMOD_CHANNEL_FREE, menuSound, 0, &channel);
        break;
        case FSND:
            result = system->playSound(FMOD_CHANNEL_FREE, firstSound, 0, &channel);
        break;
    }
}

void sndfx::stop_sound(int mode)
{
    // check if the channel is playing or not
    bool playStat = false;  // default -- channel is not playing
    result = channel->isPlaying(&playStat);
    switch(mode)
    {
        case MENU:
            if(playStat)
                channel->stop();
        break;

        case FSND:
            if(playStat)
                channel->stop();
        break;
    }
}

void sndfx::destroy_sound_instances()
{
    bool playStat = false;
    result = channel->isPlaying(&playStat);


    if(playStat)
        channel->stop();

    result = menuSound->release();
    error_check(result);
    result = system->close();
    error_check(result);
    result = system->release();
    error_check(result);
}

bool sndfx::isPlaying(int mode) // function to be called while interfering with another sound instance
{
    bool playStat;  // No default value -- unknown part while calling this function
    switch(mode)
    {
        case FSND:
            result = channel->isPlaying(&playStat);
        break;
    }
    cout<<playStat<<endl;   // just to check the value
    // a pause sound might also be required -- or some way to reduce the volume of the sound to zero
    // creating the visual for the alert box -- created, adding to the data file
    return playStat;
}

void sndfx::error_check(FMOD_RESULT result)
{
    if(result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        destroy_instances();
        allegro_exit();
    }
}
