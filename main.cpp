#include "main.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout<<"Working!!!\n";

    allegro_init();

    FMOD::System *sfxSystem;
    FMOD_RESULT sfxResult;

    set_color_depth(COLORDEPTH);
    graphics_init(WINDOW, 1024, 768);   // for testing -- default == WINDOWED mode
    init_sfx(sfxSystem, sfxResult);

    // sounds -- first creating only the sounds
    FMOD::Sound *menuSfx;   // the sound that will be played for the menu
    FMOD::Sound *cutscMainSfx;  // sound that will be played while showing the cutscenes
    FMOD::Sound *distortFrameSfx;   // distort frame sfx
    FMOD::Sound *mainSfx;   // The music that will be played primarily for this game -- though I have doubt on that

    // channels -- corresponding to the sounds that will be played
    FMOD::Channel *menuChannel; // menu sfx channel
    FMOD::Channel *custscMainChannel;   // cutscene bg music
    FMOD::Channel *distortChannel;  // channel for playing the distort sound
    FMOD::Channel *mainChannel; // Main channel -- will play most of the music

    create_instances();
    // create sfx instances
    create_sfx_instances(sfxSystem, sfxResult, menuSfx, MENUSFX, REPEAT);
    create_sfx_instances(sfxSystem, sfxResult, mainSfx, MAINSFX, REPEAT);

    // load distort_frame_sfx
    create_sfx_instances(sfxSystem, sfxResult, distortFrameSfx, DISTORTSFX, NORMAL);
    create_sfx_instances(sfxSystem, sfxResult, cutscMainSfx, CUTSCSFX, REPEAT);


    //display_splash();
    // an issue to be resolved -- slowly increase the volume of the sound that will be played here
    play_sfx(sfxSystem, sfxResult, menuSfx, menuChannel);
    install_keyboard();

    //sfx.play_sound(MENU);
    int dispRetVal = display_terminal(true, "n@$h> ");
    clear_dBuffer();
    if(dispRetVal == STARTX) // decide on the return type
    {
        graphics_init(WINDOW, 600, 400);
        display_boot_seq();
    }
    else if(dispRetVal == POWEROFF)
    {
        allegro_exit();
        exit(0);
    }
    //sfx.stop_sound(MENU);

    /*
        The following modules have been planned and will be implemented in the near future.
        Current improvements/modules to be implemented:
            1. libClParser -- this will be a commandline parser for parsing the command, renamed : libClTokenizer
            2. libxParser -- this will be the expression parser for the toy programming language

        libClParser -- implementation started, renamed: libClTokenizer

        The libClTokenizer is mostly using the tokenizing technique used by libTxtParser created
        by nb0dy. It's implementation is slightly tweaked to help the accumulation of tokens easier.

        Level design:
        1. Now when the maini_bg() has been set up, display the terminal first -- the display terminal
        will be the basic thing the user will have at his/her disposal. This terminal will allow the
        user to call different functions. Incase the user presses the delete key -- the terminal window
        will go away but can be brought back using the F5 key from the main game engine[This part
        seems to a bit tricky]

        2. Create the lvlDesign documents using LaTeX[if possible include detailed information about
        the steps to be performed]
    */

    clear_dBuffer();
    graphics_init(WINDOW, 1024, 768);
    //sfx.play_sound(FSND);   // No level check for this -- the music will be played one after the other

    // redesigning the sound library first

    // tasks to be done:
    // 1. Redesign the libSound
    // 2. create the appropriate profile file and read & write from that file

    // the problem is with the type of converter that are being used to convert the files
    // create the user profile

    // need to check the issue in other laptops with better display
    // though it looks fine from my side

    // tasks neede to be completed
    // 1. first solve the blitting problem in fullscreen mode for desktops with higher
    // resolution
    usrProfile usrInst;
    bool calledOnce = false;    // not yet called
    bool isShown = false;   // not yet shown
    bool isDisplayed = false;   // the cutscene is not yet shown
    bool setBck = false;    // the background by default not set

    usrInst.usrProfileInit();   // about to add more sounds for the key presses
    while(!key[KEY_ESC])
    {
        // the key checking routine will be here
        if(!calledOnce)
        {
            usrInst.load_profile();
            usrInst.load_cfg(); // also loading the configuration file
            calledOnce = true;
        }

        if(!isShown)
        {
            // stop the previous sound playing function
            menuChannel->setPaused(true);

            usrInst.display_level_intro(sfxSystem, sfxResult, cutscMainSfx, distortFrameSfx, custscMainChannel, distortChannel, isDisplayed);  // passing the system and others to this function

            isShown = true;
        }
        sfxSystem->update();
        menuChannel->setPaused(false);

        // Issues to be resolved:
        // 1. display the current day cutscene and the objectives for the current mission and Level

        // New tweaking to be done
        // Show the present scenario in the level_intro display function -- as well as the objectives too

        // setting up the next screen for the game play
        if(isDisplayed)
        {
            // background set -- now dislay the present day cutscene and the display of the objectives
            set_gfx_background();
            isDisplayed = false;    // so this is also working
            setBck = true;
        }

        // since the levelNum has been incremented -- now there will be fileWrite routine for another
        // type of file -- usrSysConfig.cfg
        if(setBck)    // meaning that the cutscene display has been done
        {
            // call the usrProfile function for testing
            usrInst.checkUsrCfg();
            setBck = false; // the background image has been and hence the flag value reset
        }

        //play_sfx(sfxSystem, sfxResult, mainSfx, mainChannel);
        // implementing the code that was written here
        update_screen();
    }
    stop_play_sfx(mainChannel, sfxResult);
    // Now to implement the next part that was creating the problem

    // porting code written in testSfx to the libSound module
    // porting done properly -- working version

    // This version will be going as a upload.
    // now to add/remove some sound -- have to remove the skyrim music

    // next issue to be resolved needs to be reported

    // Till now the internet is working fine -- hope it works out fine

    //sfx.destroy_sound_instances();  // this is theer because of the load_sound() routine
    destroy_sfx_instances(sfxSystem, menuSfx, sfxResult, mainChannel);
    destroy_instances();    // back_end seg_fault existing at this point -- probing inside for
    // more information
    allegro_exit();
    return EXIT_SUCCESS;
}
END_OF_MAIN();/**/
