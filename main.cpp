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

    clear_dBuffer();
    graphics_init(WINDOW, 1024, 768);
    //sfx.play_sound(FSND);   // No level check for this -- the music will be played one after the other


    usrProfile usrInst;
    bool calledOnce = false;    // for load_profile and for load_cfg(), true --> done
    bool isShown = false;   // not yet shown -- cutSceneDisplay, true --> done
    bool isDisplayed = false;   // the cfg_file part is not yet shown or the cfg has not been read
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

            isShown = true; // level_intro has been displayed
        }
        sfxSystem->update();
        menuChannel->setPaused(false);  // This might be required to be kept true

        if(!setBck)
        {
            set_gfx_background();
            setBck = true;
        }

        // now show the user to display the stored CPU names
        // clearing the bitmap
        if(!isDisplayed)    // only if background has been set
        {
            // call the usrProfile function for testing
            usrInst.checkUsrCfg(); // Seg Fault occuring -- checking -- removed
            // one more test -- if no profile and cfgFileCount >= 1 -- delete cfg file, ask user to create another
            // cfg -- display_cfg_components

            // the aforesaid enhancement needs to be implemented
            isDisplayed = true; // set to true to display gfx_background
        }

        // since the levelNum has been incremented -- now there will be fileWrite routine for another
        // type of file -- usrSysConfig.cfg


        // Enhancement -- to be implemented
        // Remove the setting of display for the booting part, draw the same in the gfx_small_bmp,
        // stretch blit the textBmp on the screen

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
