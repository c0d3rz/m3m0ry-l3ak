#include "libUsr.h"

using namespace std;

void usrProfile::usrProfileInit()
{
    // before even the essentials come up -- display the basic background
    // Also check the cfgFile along with it

    // some of the essentials that might be required to carry out these tasks
    struct dirent *dirHnd = NULL;
	DIR* dirPtr = NULL;
    profileDirPath = PROFILEDIRPATH;
    string secCfgFilePath = PROFILEDIRPATH;
    fileCount = 0;  // set filecount to be zero at the start of each game instance
    cfgFileCount = 0;


    if(_is_dir_exist_(profileDirPath))  // if the dir exists
    {
        profileDirPath.push_back('/');
        //secCfgFilePath.push_back('/');
        // now check if any profile file exists or not -- set the profileExists boolean accordingly
        dirPtr = opendir(profileDirPath.c_str());

        // check if the directory can be opened or not
        if(dirPtr == NULL)
        {
            allegro_message("No dir -- exiting");
            allegro_exit();
        }

        while(dirHnd = readdir(dirPtr))
        {
            // store the file names in that cirectory and increment the counter
            if(fnmatch("*.profile", dirHnd->d_name, FNM_CASEFOLD) == 0)	// check files only with the <>.profile extension
            {
                ++fileCount;
                profileExists = true;
            }

            if(fnmatch("*.cfg", dirHnd->d_name, FNM_CASEFOLD) == 0)	// check files only with the <>.profile extension
            {
                ++cfgFileCount;
                profileExists = true;
            }
        }

        // close the directory reading pointer
        closedir(dirPtr);
    }
    else
    {
        // create the directory named profile and then create the profile file inside that dir
        // create the directory
        mode_t process_mask = umask(0);
		if(mkdir(profileDirPath.c_str(), S_IRWXU | S_IRWXG | S_IRWXO) == 0);	// means dir created
		else
		{
            allegro_message("Could not create profile dir");
            allegro_exit();
		}

		// profile directory is now created
		profileDirPath.push_back('/');
    }
}

bool usrProfile::_is_dir_exist_(string inpDirPath)
{
    // check the dir existence
    struct stat dirStat;
	if(stat(const_cast<char *>(inpDirPath.c_str()), &dirStat) == 0)
		return true;
	else
		return false;
}

usrProfile::usrProfile()
{
    profileExists = false;
    fileCount = 0;
    profileDirPath = PROFILEDIRPATH;
    cfgDirPath = PROFILEDIRPATH;
    loadProfile = false;
    isNewProfileCreated = false;    // assuming that new profile is not created till now

    loadCfg = false;    // cfg file not loaded by default
    cfgFileCount = 0;
    isNotCfgExist = NONE; // default no cfgFile exists

    // the cfgRequirements
    cpuOpFreq = 0;
    nicCapability = 0;
    ramCapac = 0;
    modTxRate = 0;
}

void usrProfile::load_profile()
{
    // load the profile file here
    // check the fileCount var for the number of profile files found in that directory
    if(loadProfile)
        return;

    if(fileCount > 1)
    {
        allegro_message("Only one profile can be handled");
        destroy_instances();
        allegro_exit();
    }
    else if(fileCount < 1)
    {
        // call the query username function to get the desired username from the user
        if(_usrName_.empty())
            _usrName_ = query_uname();

        // set the other variables that need to be set to proper values
        hackVal = 0;  // the special case has been implemented
        usrLvl = 0;
        accBal = 5000; // Reducing the accBal allocated to the user -- for the time being -- only 5k$
        // rest of the amount will be earned by the user while playing the game

        // starting part hence no check is required
        missionNum = 0;
        isMissionComplete = INCOMPLETE;   // MACRO created see header file for that
        isLevelComplete = INCOMPLETE;

        // call the filewrite function and pass the values that need to be written
        // The things that will be written at the moment
        // username::std::string, long HackVal, long accBal, int usrLvl, int dynVal
        // the dynVal is the one that will be used to do the dynamic memory allocation

        _filewrite_(_usrName_, hackVal, accBal, usrLvl, missionNum, isMissionComplete, isLevelComplete);    // write the code for this function
        isNewProfileCreated = true; // indicates that the new profile has been created
    }
    else if (fileCount == 1)
    {
        // load the profile and set loadProfile == true

        // first display the profile path -- as in set the appropriate profile path
        profileDirPath = PROFILEDIRPATH;    // reset to default
        profileDirPath.push_back('/');

        // profile dir Set -- set the name of the file in the vector stack
        vector<string> fileList;    // store the file names
        DIR *dirPtr;
        struct dirent *dirp;

        if((dirPtr = opendir(profileDirPath.c_str())) == NULL)
        {
            allegro_message("Error opening directory");

            destroy_instances();
            allegro_exit();
        }

        while((dirp = readdir(dirPtr)) != NULL)
            fileList.push_back(dirp->d_name);

        vector<string>::iterator iter = fileList.begin();
        for(; iter != fileList.end(); iter++)
        {
            if((*iter).find(".profile") != string::npos)
                profileDirPath.append(*iter);
        }

        // now start reading the profile file with proper decoding function call
        // read the values accordingly
        _fileread_(_usrName_, hackVal, accBal, usrLvl, missionNum, isMissionComplete, isLevelComplete);   // write the file read code

        closedir(dirPtr);   // close the directory pointer after all the loading has taken place
    }
}

void usrProfile::load_cfg()
{
    if(loadCfg)    // check bool
        return;
    else
    {
        if(cfgFileCount < 1)
            isNotCfgExist = NONE;
        else if(cfgFileCount == 1)
            isNotCfgExist = FILER;  // read the file
        else
        {
            allegro_message("Multiple cfgFile detected");
            destroy_instances();
            // destroy sfx issues remaining here -- needs to be resolved
            allegro_exit();
        }
    }
}

void usrProfile::display_level_intro(FMOD::System*& inpSystem, FMOD_RESULT &inpResult, FMOD::Sound*& inpBgSfxState, FMOD::Sound*& inpExSfxState, FMOD::Channel*& inpBgChannel, FMOD::Channel*& inpExChannel)
{
    // working principle of this function
    // This function will be checking the usrLvl and based on this variable as well as the
    // missionNum

    // if the level number is zero -- that means that the profile was created for the first time
    // player -- still make a check of the missionNum -- the value should be zero for level 0
    // after displaying the intro gfx -- this should increment the usrLvl variable to 1 and
    // the mission num for level num should be zero at first -- the maximum number of
    // missions available for the user in level 1 is 6

    // let the coding begin
    if(isNewProfileCreated)
    {
        cout<<"New Profile created\n";  // now read from the newly created profile file
        _usrName_.clear();
        _fileread_(_usrName_, hackVal, accBal, usrLvl, missionNum, isMissionComplete, isLevelComplete);
    }
    else
    {
        cout<<"Reading pre created profile\n";
    }

    if(usrLvl == 0)
    {
        if(missionNum == 0)   // that's good
        {
            // call the function that will display the first cutscenes
            display_intro(INTRO, ".Init", _usrName_, inpSystem, inpResult, inpBgSfxState, inpExSfxState, inpBgChannel, inpExChannel);

            // now to do the other part of the code -- checking the return of control
            cout<<"After the libGraphics::function to display_intro\n";

            // increment the usrLvl
            usrLvl++;   // write this in the profile file

            // calling the fileWrite function
            _filewrite_(_usrName_, hackVal, accBal, usrLvl, missionNum, isMissionComplete, isLevelComplete);
        }
        else
        {
            allegro_message("Profile file corrupted");
            destroy_instances();
            allegro_exit();
        }
    }   // have to write the else if clause for processing and displaying the appropriate
    // cutscene by sending the correct params to the called function
}

string usrProfile::getUserName()
{
    return _usrName_;
}

void usrProfile::checkUsrCfg()
{
    vector<string> fileList;    // the list of files in that directory
    string secCfgFilePath = PROFILEDIRPATH; // set to default

    // Keep the variables named nicCardName and the sysCpuName -- make the change in the values
    // after performing the switch operation on the integer parameters

    if((isNotCfgExist == NONE) && (usrLvl == 1))
    {
        // Additional parameter -- internal HDD selection -- needs to be added
        cout<<"Before calling displayCfgUnits function\n";  // segFault occuring in display_cfg_units()

        // First create variables that will fill up the string values
        // pass these to the display_cfg_units() function rather than the sysCpuName, NICCardName

        display_cfg_units(GET, cpuNameDef, cpuOpFreq, nicCardNamedef, nicCapability, ramCapac, modTxRate, accBal);
        _populate_sys_var_(cpuNameDef, nicCardNamedef);

        // change the file write function -- write the Def inp variable data -- switch run after
        // cfg file read
        //_filewrite_(sysCpuName, cpuOpFreq, NICCardName, nicCapability, ramCapac, modTxRate);
        //_filewrite_(_usrName_, hackVal, accBal, usrLvl, missionNum, isMissionComplete, isLevelComplete);
    }
    else if(isNotCfgExist == FILER)
    {
        // first process the cfgDirPath variable
        cfgDirPath = PROFILEDIRPATH;    // reset to original variable
        cfgDirPath.push_back('/');

        vector<string> fileList;
        DIR *dirPtr;
        struct dirent *dirp;

        if((dirPtr = opendir(cfgDirPath.c_str())) == NULL)
        {
            allegro_message("Error Opening Directory");
            destroy_instances();
            // also need to destroy the sfx instances
            allegro_exit();
        }

        while((dirp = readdir(dirPtr)) != NULL)
            fileList.push_back(dirp->d_name);

        vector<string>::iterator iter = fileList.begin();
        for(; iter != fileList.end(); iter++)
        {
            if((*iter).find(".cfg") != string::npos)
                cfgDirPath.append(*iter);
        }
        // check the value of the cfgDirPath
        cout<<"cfg dir path "<<cfgDirPath<<endl;
        _fileread_(sysCpuName, cpuOpFreq,NICCardName, nicCapability, ramCapac, modTxRate);
    }

    // checking whether the data read from the profile file is still there in the memory or not
    //cout<<hackVal<<"\t"<<accBal<<"\t"<<usrLvl<<"\t"<<_usrName_<<"\t"<<missionNum<<"\t"<<isMissionComplete<<"\t"<<isLevelComplete<<endl;
}

// ---------------------------------- Internal functions ----------------------------------------------------
void usrProfile::_filewrite_(std::string &inpUname, long &inpHackVal, long &inpAccBal, int &inpUsrLevel, int &inpMissionNum, int &inpIsMissionComplete, int &inpIsLevelComplete)
{
    // create the path for the profile file
    if(profileDirPath.find(".profile") == string::npos)
        (profileDirPath.append(inpUname)).append(".profile");

    // populate the key values
    string strKey = STRKEY;
    long longKey = LONGKEY;
    int intKey = INTKEY;

    // now do the appropriate encoding required for the specific variables
    // apply padding from here only

    // also remember to restrict the users to give names that are at the max some limited characters
    if(inpUname.length() < strKey.length())
        // do the padding and then proceed for the vernam encryption
        _pad_string_(inpUname, strKey.size());
    else if(inpUname.length() == strKey.length());  // no padding required

    // now for the vernam and base64 encoding of the string
    string encUname = _ver_encode_(inpUname, strKey);
    encUname = base64_encode(reinterpret_cast<const unsigned char *>(encUname.c_str()), encUname.length());

    // populate the magic dynVal variable
    dynVal = encUname.length();

    // do the encoding for the other variables
    long encHackVal = _ver_encode_(inpHackVal, longKey);
    long encAccBal = _ver_encode_(inpAccBal, longKey);
    int encUsrLvl = _ver_encode_(inpUsrLevel, intKey);
    int encDynVal = _ver_encode_(dynVal, intKey);

    // mission and level related variables
    int encMissionNum = _ver_encode_(inpMissionNum, intKey);
    int encIsMissionComplete = _ver_encode_(inpIsMissionComplete, intKey);
    int encIsLevelComplete = _ver_encode_(inpIsLevelComplete, intKey);

    // Now to start writing to the profile file
    char *dynArr;
    dynArr = new char[dynVal];

    for(int index = 0; index < encUname.length(); index++)
		dynArr[index] = encUname[index];

    PACKFILE *inpFile;
	inpFile = pack_fopen(profileDirPath.c_str(), "wp");

	// check if the file is loaded or not
	if(!inpFile)
		allegro_exit();

    // now start writing in the file
	pack_iputl(encHackVal, inpFile);
	pack_iputl(encAccBal, inpFile);
	pack_iputw(encUsrLvl, inpFile);
	pack_iputw(encDynVal, inpFile);

	//writing the mission status related data
	pack_iputw(encMissionNum, inpFile);
	pack_iputw(encIsMissionComplete, inpFile);
	pack_iputw(encIsLevelComplete, inpFile);

	// now write the string
	pack_fwrite(dynArr, dynVal, inpFile);

	// close the file handling session and free the memory
	pack_fclose(inpFile);
	delete []dynArr;

    // also try to resolve the segFault at the ending of the game display
    // Writing file read code
}

void usrProfile::_fileread_(std::string &inpUname, long &inpHackVal, long &inpAccBal, int &inpUsrLevel, int &inpMissionNum, int &inpIsMissionComplete, int &inpIsLevelComplete)
{
    // clear the variables of the previous data while reading profile file
    //inpUname.clear();
    //inpHackVal = 0;
    //inpAccBal = 0;
    //inpUsrLevel = 0;

    // clearing the mission and level related variables
    //inpMissionNum = 0;
    //inpIsMissionComplete = 0;
    //inpIsLevelComplete = 0;


    dynVal = 0; // before any mishap happens better make it zero
    PACKFILE *readFile;

    // populate the key values
    string strKey = STRKEY;
    long longKey = LONGKEY;
    int intKey = INTKEY;

    readFile = pack_fopen(profileDirPath.c_str(), "rp");    // read with compression
    char *dynAr;

    // check if the file is read properly or not
    if(!readFile)
    {
        allegro_message("Profile file could not be read");  // also destroy sfx_instances -- unresolved
        destroy_instances();
        allegro_exit();
    }

    // read the values accordingly
    inpHackVal = pack_igetl(readFile);
    inpAccBal = pack_igetl(readFile);
    inpUsrLevel = pack_igetw(readFile);
    dynVal = pack_igetw(readFile);

    inpMissionNum = pack_igetw(readFile);
    inpIsMissionComplete = pack_igetw(readFile);
    inpIsLevelComplete = pack_igetw(readFile);

    dynAr = new char[dynVal];   // dynamically allocate memory
    pack_fgets(dynAr, (dynVal + 1), readFile);

    // copy from the memory into the string that is provided
    for(int index = 0; index < (dynVal + 1); index++)
        inpUname.push_back(dynAr[index]);

    pack_fclose(readFile);  // close the pack_read_file_instance
    delete []dynAr; // free the dynamically allocated memory

    // after this I will have to deploy the decoding techniques
    inpHackVal = _ver_decode_(inpHackVal, longKey);
    inpAccBal = _ver_decode_(inpAccBal, longKey);
    inpUsrLevel = _ver_decode_(inpUsrLevel, intKey);

    // decoding the mission and level related data
    inpMissionNum = _ver_decode_(inpMissionNum, intKey);
    inpIsMissionComplete = _ver_decode_(inpIsMissionComplete, intKey);
    inpIsLevelComplete = _ver_decode_(inpIsLevelComplete, intKey);

    // Now release the decoding functions related to string
    inpUname = base64_decode(inpUname);
    inpUname = _ver_decode_(inpUname, strKey);
    _unpad_string_(inpUname);   // proper string value done
}

void usrProfile::_filewrite_(std::string &inpCpuName, int &inpOpFreq, std::string &inpNicCardName, int &inpNicCapability, long &inpRamCapac, int &inpModTxRate)
{
    cfgDirPath = PROFILEDIRPATH;
    cfgDirPath.append("/");
    (cfgDirPath.append(getUserName())).append(".cfg"); // This part also needs to be done in the
    // place before the fileRead function call -- will be doing that after fileRead

    // Now since both of them are int type -- just do the encryption on the int types
    string strKey = STRKEY;
    long longKey = LONGKEY;
    int intKey = INTKEY;


    if(inpCpuName.length() < strKey.length())
        _pad_string_(inpCpuName, strKey.size());
    else if(inpCpuName.length() == strKey.length());    // no padding required

    // same for the inpNicCardName
    if(inpNicCardName.length() < strKey.length())
        _pad_string_(inpNicCardName, strKey.size());
    else if(inpNicCardName.length() == strKey.length());

    string encCpuName = _ver_encode_(inpCpuName, strKey);
    string encNicCardName = _ver_encode_(inpNicCardName, strKey);
    encCpuName = base64_encode(reinterpret_cast<const unsigned char *>(encCpuName.c_str()), encCpuName.length());
    encNicCardName = base64_encode(reinterpret_cast<const unsigned char*>(encNicCardName.c_str()), encNicCardName.length());

    // now start writing the next part of the cfgFileWrite function
    char *dynCpuArr;
    dynCpuStrVal = encCpuName.length();
    dynNicStrVal = encNicCardName.length();
    cout<<dynCpuStrVal<<endl;   // need to check the reading of file in the basic test bed

    dynCpuArr = new char[dynCpuStrVal];

    char *dynNicArr;
    dynNicArr = new char[dynNicStrVal];

    for(int index = 0; index < dynCpuStrVal; index++)
        dynCpuArr[index] = encCpuName[index];
    for(int index = 0; index < dynNicStrVal; index++)
        dynNicArr[index] = encNicCardName[index];

    // encode the other values too
    // processing the double variable contents

    int encOpFreq = _ver_encode_(inpOpFreq, intKey);

    int encNicCapability = _ver_encode_(inpNicCapability, intKey);
    long encRamCapac = _ver_encode_(inpRamCapac, longKey);
    int encModTxRate = _ver_encode_(inpModTxRate, intKey);

    // encode the string lengths
    int encCpuStrVal = _ver_encode_(dynCpuStrVal, intKey);
    int encNicStrVal = _ver_encode_(dynNicStrVal, intKey);

    cout<<encNicCardName<<endl;

    // create the packfile instance
    PACKFILE *cfgFileInst;
    cfgFileInst = pack_fopen(cfgDirPath.c_str(), "wp");

    if(!cfgFileInst)
    {
        delete []dynNicArr;
        delete []dynCpuArr;
        destroy_instances();
        allegro_exit();
    }

    // start writing data in the file.
    pack_iputl(encRamCapac, cfgFileInst);
    pack_iputw(encOpFreq, cfgFileInst);
    pack_iputw(encNicCapability, cfgFileInst);
    pack_iputw(encModTxRate, cfgFileInst);

    // dynVals of strings
    pack_iputw(encCpuStrVal, cfgFileInst);
    pack_iputw(encNicStrVal, cfgFileInst);

    // start writing the string variables
    pack_fwrite(dynCpuArr, dynCpuStrVal, cfgFileInst);
    pack_fwrite(dynNicArr, dynNicStrVal, cfgFileInst);

    // close instances and free memory
    pack_fclose(cfgFileInst);
    delete []dynCpuArr;
    delete []dynNicArr;
}


void usrProfile::_fileread_(std::string &inpCpuName, int &inpOpFreq, std::string &inpNicCardName, int &inpNicCapability, long &inpRamCapac, int &inpModTxRate)
{
    // cfgDirPath has been set up before
    // just checking whether the cfgDirPath is fine or not
    cout<<"Current cfgDirPath "<<cfgDirPath<<endl;

    // problem solved
    // before any mishap
    dynCpuStrVal = 0;
    dynNicStrVal = 0;

    // open up the packFile instance
    PACKFILE *readCfg;

    string strKey = STRKEY;
    long longKey = LONGKEY;
    int intKey = INTKEY;

    readCfg = pack_fopen(cfgDirPath.c_str(), "rp");
    char *dynCpuArr;
    char *dynNicArr;    // these are for the strings of CpuName and the NicCardName

    // check if file
    if(!readCfg)
    {
        // cleanup
        allegro_message("Config file could not be read");
        destroy_instances();
        allegro_exit();
    }

    // Read the values accordingly -- This is the part that makes the things tricky
    inpRamCapac = pack_igetl(readCfg);
    inpOpFreq = pack_igetw(readCfg);

    inpNicCapability = pack_igetw(readCfg);
    inpModTxRate = pack_igetw(readCfg);

    // read the dynamic values of strings
    dynCpuStrVal = pack_igetw(readCfg);
    dynNicStrVal = pack_igetw(readCfg);

    // need to read the strings
    //dynCpuStrVal = _ver_decode_(dynCpuStrVal, intKey);
    cout<<dynNicStrVal<<endl;

    dynCpuArr = new char[dynCpuStrVal];
    pack_fgets(dynCpuArr, (dynCpuStrVal + 1), readCfg);

    for(int index = 0; index < (dynCpuStrVal + 1); index++)
        inpCpuName.push_back(dynCpuArr[index]);
    inpCpuName = base64_decode(inpCpuName);
    inpCpuName = _ver_decode_(inpCpuName, strKey);
    _unpad_string_(inpCpuName);

    dynNicStrVal = _ver_decode_(dynNicStrVal, intKey);
    dynNicArr = new char[dynNicStrVal];
    pack_fgets(dynNicArr, (dynNicStrVal + 1), readCfg);

    for(int index = 0; index < (dynNicStrVal + 1); index++)
        inpNicCardName.push_back(dynNicArr[index]);

    cout<<inpCpuName<<endl;

    //inpNicCardName = base64_decode(inpNicCardName); // the string is NULL here -- why?
    //inpNicCardName = _ver_decode_(inpNicCardName, strKey);
    //_unpad_string_(inpNicCardName);

    cout<<inpNicCardName<<endl;

    // string still not read -- closing off the cfgRead instance
    pack_fclose(readCfg);
    delete []dynCpuArr; // This is where the problem keeps creeping up
    delete []dynNicArr;
    // free memory will be done later

    // debugging section
    //cout<<(_ver_decode_(inpRamCapac, longKey)/1024)/1024<<endl;
    //cout<<_ver_decode_(inpOpFreq, intKey)<<endl;

    // changed inpOpFreq to short int -- read is working fine
}

void usrProfile::_populate_sys_var_(int &inpCpuNameDef, int &inpNicCardNameDef)
{
    switch(inpCpuNameDef)
    {
        case CPU1:
            sysCpuName = "Intel Core Duo T2700";
        break;

        case CPU2:
            sysCpuName = "Intel Core Duo T2600";
        break;

        case CPU3:
            sysCpuName = "Intel Xeon 5160";
        break;

        case CPU4:
            sysCpuName = "Intel Xeon 5150";
        break;

        case CPU5:
            sysCpuName = "Intel Xeon X5355";
        break;

        case CPU6:
            sysCpuName = "AMD Turion 64 X2";
        break;

        case CPU7:
            sysCpuName = "AMD Athlon Regor";
        break;

        case CPU8:
            sysCpuName = "AMD Athlon Propus";
            break;
    }

    switch(inpNicCardNameDef)
    {
        case NIC1:
            NICCardName = "Allied Telesis AT-2712FX";
        break;

        case NIC2:
            NICCardName = "Allied Telesis AT-2912T";
        break;

        case NIC3:
            NICCardName = "Allied Telesis AT-2500";
        break;
    }
}
