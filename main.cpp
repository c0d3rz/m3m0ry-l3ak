#include "main.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout<<"Working!!!\n";

    // init all the primitives required for allegro to startup
    allegro_init();

    FMOD::System *sfxSystem;
    FMOD_RESULT sfxResult;

    set_color_depth(COLORDEPTH);
    graphics_init(WINDOW, 1024, 768);   // for testing -- default == WINDOWED mode
    init_sfx(sfxSystem, sfxResult);    // till this part this is working fine

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

    // Now let's play some music

    // there is some issue with the console text image that is being blitted on top of the
    // console image -- index out of range Seg fault is occuring -- most probable solution might be
    // to set the position of the console text image on the console image.

    create_instances();
    // create the sound instances
    create_sfx_instances(sfxSystem, sfxResult, menuSfx, MENUSFX, REPEAT);
    create_sfx_instances(sfxSystem, sfxResult, mainSfx, MAINSFX, REPEAT);
    // create the sfx channels after putting the appropriate
    // loading the distort frame sound
    create_sfx_instances(sfxSystem, sfxResult, distortFrameSfx, DISTORTSFX, NORMAL);   // have to check about this part
    create_sfx_instances(sfxSystem, sfxResult, cutscMainSfx, CUTSCSFX, REPEAT);  // this will be played in normal loop


    //display_splash(); // commenting this for the purpose of writing new code for this
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
        The levels will be as follows:
        1. First check the level num; if the level num is zero then display the following sequence to the user.

        First the screen will be shown with some other background image, the terminal will be there.
        The user will see the main protagonist carrying on his usual work as head of the security
        organisation -- A pop up message will be shown asking for some log access and after the user
        as in the character accepts the request -- a large number of error messages will open up
        showing the following warning:

        WARNING!!! MEMORY LEAK!!! -- I need to create this part of the graphics -- Most probably I will be storing
        the functions that will be handling these in the levelHeader file. That would make it easy for mainta
        -ining. Hope this one works out.

        After this there will be a transition and the user will be seeing another video. In the next video the
        user will see through the eyes of the main character in whose role the user will step into the game.

        The eyes will open up in the prison -- thereby displaying a prison wall. After that the user will be
        hearing the voice of some person probably the jailor asking the main character to get out of prison
        since his time is up. The main character will be getting up and start to leave. That's when the
        screen will fade in black. After that a small screen will open up and there will be written what
        happened after that.

        So I need to concentrate on the first video that will be shown in case the level
        of the player is 0. Draw screens and also prepare the sequences that will be required for the first
        intro blitting of images.


        Next work to be done -- decide the variable values that need to be written in the profile file
        This profile file will also be used as the save game state file.

        Data to be written for checking whether the mission has been completed.
        int isMissionComplete;
        int missionNum;    --> the mission number, will be stroing the value of the last mission
        completed
        int isLevelComplete;

        Level cutscene display function has been created.
        Plus the libSound module has been redesigned. Though that requires a bit of tweaking.

        Oh, BTW I almost forgot, I installed UNIX env in my VirtualBox distro. That is really cool
        operating system. A bit difficult for an idiot like me though.
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

    usrInst.usrProfileInit();   // about to add more sounds for the key presses
    while(!key[KEY_ESC])
    {
        // the key checking routine will be here
        if(!calledOnce)
        {
            usrInst.load_profile();
            calledOnce = true;
        }

        if(!isShown)
        {
            // stop the previous sound playing function
            menuChannel->setPaused(true);

            // changing the music for the game
            // pass to function to be relayed to another one
            usrInst.display_level_intro(sfxSystem, sfxResult, cutscMainSfx, distortFrameSfx, custscMainChannel, distortChannel, isDisplayed);  // passing the system and others to this function
            // the userInstance display_level_intro will be passing two channels and two sounds
            // one will be the cutscene bg music and the other will be sfx music

            // Tweaking for the display_level_intro function
            // Display the present scenario and the objective of that mission and Level

            // Have to decide on the number of levels to be implemented in the game
            // plus have to make a network map as well as decide the boss names and the corp names
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
        }

        // creating the main key_event handler
        int rdKey;
        char asciiChar;
        char scanCode;
        while(keypressed())
        {
            rdKey = readkey();
            asciiChar = rdKey & 0xFF;
            scanCode = rdKey >> 8;

            // switiching the scanned code from the keyBuf
            switch(scanCode)
            {
                case KEY_F5:
                break;

                case KEY_F6:
                break;

                default:
                break;  // oopsie, this will be a bit of drag -- setting up the background
                // this will need some more tinkering
            }
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
