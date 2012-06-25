#ifndef LIBUSR_H_INCLUDED
#define LIBUSR_H_INCLUDED


#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <dirent.h>
#include <fnmatch.h>
#include <sys/stat.h>

#include <allegro.h>
#include "libGraphics.h"
#include "libCrypt.h"
#include <fmodex/fmod.hpp>
#include <fmodex/fmod_errors.h> // just for passing the arguments of the FMOD::System and channel

// MACROS
#define PROFILEDIRPATH "./profile"  // this is a relative path
#define STRKEY "ncpw@m3m0ry_l3ak"
#define LONGKEY 64000
#define INTKEY 90

#define COMPLETE 1
#define INCOMPLETE 0

#define INTRO 0
#define INIT 10

#define NONE 0  // no file present
#define FILER 1 // file is present -- read the file in this case

class usrProfile
{
    public:
        void usrProfileInit();   // initialize profile creation
        usrProfile();
        void load_profile();  // load the profile
        void load_cfg();    // load the usr cfg file
        void display_level_intro(FMOD::System*& inpSystem, FMOD_RESULT &inpResult, FMOD::Sound*& inpBgSfxState, FMOD::Sound*& inpExSfxState, FMOD::Channel*& inpBgChannel, FMOD::Channel*& inpExChannel); // check the level, mission num and display the level story
        std::string getUserName();  // return the username of the player
        void checkUsrCfg(); // usrSysConfig file -- This will be created later

        // for simplcity
        std::string sysCpuName;  // system CPU name
        int cpuOpFreq;  // CPU Operating frequency
        std::string NICCardName; // Network Interface Card Name -- another enhancement coming to mind
        // maybe we can remove all the strings that are about to be written -- will see that later

        // number matching -- remember that freeKevin -- for aforesaid enhancement
        int nicCapability; // the data rate
        long ramCapac;   // the RAM size
        int modTxRate;  // modem transfer rate

        // init vars in the constructor -- done
        // check passing of such variables by reference to another function

    private:
        std::string _usrName_;
        bool profileExists;
        int fileCount;
        int cfgFileCount;
        std::string profileDirPath;
        bool loadProfile;
        bool loadCfg;
        int isNotCfgExist;    // check for cfgFileExist

        // the user values that will be written in the profile file
        long hackVal;   // the hack value obtained by the user
        long accBal;  // the anon account that will be proided to the user at the start of the game
        int usrLvl; // the game level in which the user is presently playing
        int dynVal;


        // Other mission and level related variables
        int missionNum; // store the value of the last mission completed -- default value at the start
        // will be zero
        int isMissionComplete;  // 0 -> not completed, 1 -> not completed, default value will be set
        // after checking the missionNum variable value -- if missionNum = 0 --> value = 0
        int isLevelComplete;    // same as the aforewritten
        bool isNewProfileCreated;

        bool _is_dir_exist_(std::string inpDirPath);    // check dir existence
        void _filewrite_(std::string &inpUname, long &inpHackVal, long &inpAccBal, int &inpUsrLevel, int &inpMissionNum, int &inpIsMissionComplete, int &inpIsLevelComplete);
        void _fileread_(std::string &inpUname, long &inpHackVal, long &inpAccBal, int &inpUsrLevel, int &inpMissionNum, int &inpIsMissionComplete, int &inpIsLevelComplete);
        // Now next code would be written for manData --> manipulates user data
        // For now --> search for the segfault that is being displayed at the back-end console
        // Less sleep has rendered me saturated -- I might be needing some nap time
};

#endif
