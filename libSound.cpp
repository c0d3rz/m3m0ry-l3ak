#include "libSound.h"

using namespace std;

void init_sfx(FMOD::System*& inpSystem, FMOD_RESULT &inpResult)
{
    inpResult = FMOD::System_Create(&inpSystem);
    _sfx_error_check_(inpResult);

    // init the system
    inpResult = inpSystem->init(100, FMOD_INIT_NORMAL, 0);
    _sfx_error_check_(inpResult);
}

void create_sfx_instances(FMOD::System*& inpSystem, FMOD_RESULT &inpResult, FMOD::Sound*& inpSfxState, int mode, int playMode)
{
    string filePath;    // remember that string <var> != NULL at the time of declaring
    switch(mode)
    {
        case MENUSFX:
            filePath.clear();
            filePath = "./msdata/menusnd.wav";
        break;

        case MAINSFX:
            filePath.clear();
            filePath = "./msdata/mainsnd1.wav";
        break;

        case DISTORTSFX:
            filePath.clear();
            filePath = "./msdata/distortframe.mp3";
        break;

        case CUTSCSFX:
            filePath.clear();
            filePath = "./msdata/cutscmain.wav";
        break;
    }
    if(playMode == NORMAL)
    {
        inpResult = inpSystem->createSound(filePath.c_str(), FMOD_DEFAULT, 0, &inpSfxState);
        _sfx_error_check_(inpResult);
    }
    else if(playMode == REPEAT)
    {
        inpResult = inpSystem->createSound(filePath.c_str(), FMOD_LOOP_NORMAL, 0, &inpSfxState);
        _sfx_error_check_(inpResult);
    }
    else
    {
        // have to think of something
    }

    // create another sound
}

void play_sfx(FMOD::System*& inpSystem, FMOD_RESULT &inpResult, FMOD::Sound*& inpSfxState, FMOD::Channel*& inpChannel)
{
    inpResult = inpSystem->playSound(FMOD_CHANNEL_FREE, inpSfxState, false, &inpChannel);
    _sfx_error_check_(inpResult);
}


void release_channel(FMOD::System*& inpSystem, FMOD_RESULT &inpResult, FMOD::Channel*& inpChannel)
{
    // deprecated code -- right now working but still with bugs

    unsigned int ms = 0;    // no idea what it is supposed to do
    unsigned int lenms = 0; // again no idea what the hell is this going to do
    bool playing = false;
    bool paused = false;    // default value == false;

    int channelIsPlaying = 0;   // why do people show off

    if(inpChannel)
    {
        FMOD::Sound *currentSfx = NULL;

        inpResult = inpChannel->isPlaying(&playing);
        if((inpResult != FMOD_OK) && (inpResult == FMOD_ERR_INVALID_HANDLE) && (inpResult == FMOD_ERR_CHANNEL_STOLEN))
            _sfx_error_check_(inpResult);

        inpResult = inpChannel->getPaused(&paused);
        if((inpResult != FMOD_OK) && (inpResult == FMOD_ERR_INVALID_HANDLE) && (inpResult == FMOD_ERR_CHANNEL_STOLEN))
            _sfx_error_check_(inpResult);

        inpResult = inpChannel->getPosition(&ms, FMOD_TIMEUNIT_MS);
        if((inpResult != FMOD_OK) && (inpResult == FMOD_ERR_INVALID_HANDLE) && (inpResult == FMOD_ERR_CHANNEL_STOLEN))
            _sfx_error_check_(inpResult);

        inpChannel->getCurrentSound(&currentSfx);
        if(currentSfx)
        {
            inpResult = currentSfx->getLength(&lenms, FMOD_TIMEUNIT_MS);
            if((inpResult != FMOD_OK) && (inpResult == FMOD_ERR_INVALID_HANDLE) && (inpResult == FMOD_ERR_CHANNEL_STOLEN))
                _sfx_error_check_(inpResult);
        }
    }
    inpSystem->getChannelsPlaying(&channelIsPlaying);
}

void stop_play_sfx(FMOD::Channel*& inpPlayChannel, FMOD_RESULT &inpResult)
{
    bool playStat = false;
    inpResult = inpPlayChannel->isPlaying(&playStat);
    if(playStat)
        inpPlayChannel->stop();
    //inpPlayChannel->setPriority(0);
}

void reset_play_sfx_pos(FMOD::Channel*& inpChannel, FMOD_RESULT &inpResult)
{
    inpResult = inpChannel->setPosition(0, FMOD_TIMEUNIT_MS);
    _sfx_error_check_(inpResult);
}

void destroy_sfx_instances(FMOD::System*& inpSystem, FMOD::Sound*& inpSfxState, FMOD_RESULT &inpResult, FMOD::Channel*& inpPlayChannel)
{
    stop_play_sfx(inpPlayChannel, inpResult);   // I am not sure I will be keeping this
    // since I will have to call the stop playing function many times to stop all the channels

    inpResult = inpSfxState->release();
    _sfx_error_check_(inpResult);
    inpResult = inpSystem->close();
    _sfx_error_check_(inpResult);
    inpResult = inpSystem->release();
    _sfx_error_check_(inpResult);
}

// Internal sfx function
void _sfx_error_check_(FMOD_RESULT &inpResult)
{
    if(inpResult != FMOD_OK)
    {
        // exit from allegro
        allegro_message("Something went wrong with the sfx routines");
        allegro_exit();
    }
}
