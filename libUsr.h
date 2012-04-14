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

// MACROS
#define PROFILEDIRPATH "./profile"  // this is a relative path
#define STRKEY "ncpw@m3m0ry_l3ak"
#define LONGKEY 64000
#define INTKEY 90

#define COMPLETE 1
#define INCOMPLETE 0

#define INTRO 0
#define INIT 10

class usrProfile
{
    public:
        void usrProfileInit();   // initialize profile creation
        usrProfile();
        void load_profile();  // load the profile
        void display_level_intro(); // check the level, mission num and display the level story
        std::string getUserName();  // return the username of the player

    private:
        std::string _usrName_;
        bool profileExists;
        int fileCount;
        std::string profileDirPath;
        bool loadProfile;

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
