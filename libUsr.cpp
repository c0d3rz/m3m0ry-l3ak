#include "libUsr.h"

using namespace std;

void usrProfile::usrProfileInit()
{
    // before even the essentials come up -- display the basic background

    // some of the essentials that might be required to carry out these tasks
    struct dirent *dirHnd = NULL;
	DIR* dirPtr = NULL;
    profileDirPath = PROFILEDIRPATH;
    fileCount = 0;  // set filecount to be zero at the start of each game instance

    cout<<"Before checking the profile dir existence\n";
    if(_is_dir_exist_(profileDirPath))  // if the dir exists
    {
        cout<<"profile dir found\n";
        profileDirPath.push_back('/');
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
        }

        // close the directory reading pointer
        closedir(dirPtr);
    }
    else
    {
        // create the directory named profile and then create the profile file inside that dir
        cout<<"Will be creating the profile dir as well as the file\n";
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
    loadProfile = false;
    isNewProfileCreated = false;    // assuming that new profile is not created till now
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
        cout<<"Before the username print\n";
        cout<<_usrName_<<endl;  // username obtained -- create profile

        // set the other variables that need to be set to proper values
        hackVal = 0;  // the special case has been implemented
        usrLvl = 0;
        accBal = 20000; // the amount is in 20k dollars -- Don't take in the westernization impact
        // using packfile functions to write the values in a file

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

        // display the values that are read from the profile file
        cout<<hackVal<<"\t"<<accBal<<"\t"<<usrLvl<<"\t"<<_usrName_<<"\t"<<missionNum<<"\t"<<isMissionComplete<<"\t"<<isLevelComplete<<endl;
    }
}

void usrProfile::display_level_intro()
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
    //cout<<usrLvl<<endl;
    if(isNewProfileCreated)
    {
        cout<<"New Profile created\n";  // now read from the newly created profile file
        _usrName_.clear();
        _fileread_(_usrName_, hackVal, accBal, usrLvl, missionNum, isMissionComplete, isLevelComplete);
    }
    else
        cout<<"Reading pre created profile\n";
    cout<<hackVal<<"\t"<<accBal<<"\t"<<usrLvl<<"\t"<<_usrName_<<"\t"<<missionNum<<"\t"<<isMissionComplete<<"\t"<<isLevelComplete<<endl;

    if(usrLvl == 0)
    {
        // check if the usrLvl is zero or not
        cout<<"UsrLvl is zero\n";   // usrLvl is checked
        if(missionNum == 0)   // that's good
        {
            // call the function that will display the first cutscenes
            display_intro(INTRO, ".Init");

            // cleaned up the debug part that was implemented here
            // cleaning up other files that were debugged
        }
        else
        {
            allegro_message("Profile file corrupted");
            destroy_instances();
            allegro_exit();
        }
    }
}

// ---------------------------------- Internal functions ----------------------------------------------------
void usrProfile::_filewrite_(std::string &inpUname, long &inpHackVal, long &inpAccBal, int &inpUsrLevel, int &inpMissionNum, int &inpIsMissionComplete, int &inpIsLevelComplete)
{
    // create the path for the profile file
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
    cout<<encUname<<endl;
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
    cout<<profileDirPath<<endl; // the profile dir path variable has the name of the profile file
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
        allegro_message("Profile file could not be read");  // check out why inclusion of the libSound
        // header is making the compiler to stop compiling and throwing an error for duplication
        // of libSound_sfx class
        destroy_instances();
        allegro_exit();
    }
    cout<<"After readFile check\n";

    // read the values accordingly
    inpHackVal = pack_igetl(readFile);
    inpAccBal = pack_igetl(readFile);
    inpUsrLevel = pack_igetw(readFile);
    dynVal = pack_igetw(readFile);

    inpMissionNum = pack_igetw(readFile);
    inpIsMissionComplete = pack_igetw(readFile);
    inpIsLevelComplete = pack_igetw(readFile);
    cout<<"After reading the basic files\n";

    dynAr = new char[dynVal];   // dynamically allocate memory
    pack_fgets(dynAr, (dynVal + 1), readFile);

    // copy from the memory into the string that is provided
    for(int index = 0; index < (dynVal + 1); index++)
        inpUname.push_back(dynAr[index]);
    cout<<"After reading the userName from the file\n";

    pack_fclose(readFile);  // close the pack_read_file_instance
    delete []dynAr; // free the dynamically allocated memory

    cout<<"deleting the memory taken for dynamic memory allocation\n";

    // after this I will have to deploy the decoding techniques
    inpHackVal = _ver_decode_(inpHackVal, longKey);
    inpAccBal = _ver_decode_(inpAccBal, longKey);
    inpUsrLevel = _ver_decode_(inpUsrLevel, intKey);

    // decoding the mission and level related data
    inpMissionNum = _ver_decode_(inpMissionNum, intKey);
    inpIsMissionComplete = _ver_decode_(inpIsMissionComplete, intKey);
    inpIsLevelComplete = _ver_decode_(inpIsLevelComplete, intKey);
    cout<<"decoding the non-string variables\n";

    // Now release the decoding functions related to string
    inpUname = base64_decode(inpUname);
    cout<<inpUname<<endl;
    inpUname = _ver_decode_(inpUname, strKey);
    _unpad_string_(inpUname);   // proper string value done

    cout<<"String operations done\n";
}
