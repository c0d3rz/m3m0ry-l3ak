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
#define STRKEY "nb0dy_war10ck@m3m0ry_l3ak"
#define LONGKEY 64000
#define INTKEY 90

#define COMPLETE 1
#define INCOMPLETE 0

#define INTRO 0
#define INIT 10

#define NONE 0  // no file present
#define FILER 1 // file is present -- read the file in this case

#define TAB "\t"

#define CPU1 1
#define CPU2 2
#define CPU3 3
#define CPU4 4
#define CPU5 5
#define CPU6 6
#define CPU7 7
#define CPU8 8

#define NIC1 1
#define NIC2 2
#define NIC3 3

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
        int cpuNameDef; // for switching the name based on the macro stored in this var
        int cpuOpFreq;  // CPU Operating frequency
        std::string NICCardName;
        int nicCardNamedef;

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
        std::string cfgDirPath; // for creating and reading the cfg file
        bool loadProfile;
        bool loadCfg;
        int isNotCfgExist;    // check for cfgFileExist

        // the user values that will be written in the profile file
        long hackVal;   // the hack value obtained by the user
        long accBal;  // the anon account that will be proided to the user at the start of the game
        int usrLvl; // the game level in which the user is presently playing
        int dynVal;

        int dynCpuStrVal;
        int dynNicStrVal;   // these are for the cpu and the nir card name


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

        // cfgFile write overloaded function definition -- write routine for the following
        void _filewrite_(std::string &inpCpuName, int &inpOpFreq, std::string &inpNicCardName, int &inpNicCapability, long &inpRamCapac, int &inpModTxRate);
        void _fileread_(std::string &inpCpuName, int &inpOpFreq, std::string &inpNicCardName, int &inpNicCapability, long &inpRamCapac, int &inpModTxRate);

        void _populate_sys_var_(int &inpCpuNameDef, int &inpNicCardNameDef);    // switch and populate system display variables

        // Solution to the string read problem

        // Write a unique data in the packFile with encryption
        // on read -- do a switch and populate the string data variable

        // Soution 2
        // Create two cfg files for the same -- the problem will be solved either ways


        // Design pattern for the cfgFileWrite needs to be changed

        // The following will be the design pattern:
        // 1. rather than writing the string variable data -- write some MACRO onto to the cfgFile
        // 2. after the cfgFileRead -- do a switch operation to populate the string variables

        // remove all the strings that were written in the cfg file

        // Changes required to be done:
        // 1. change the call to the overloaded fileWrite and fileRead functions
        // 2. change the call to the selectItem functions
        // 3. Create MACROS over which the switching will be done
        // 4. Inside the display_cfg_unitts function do the switching of the dataMacro and then display the same to the user
        // when the disp pmode is given
};

#endif
