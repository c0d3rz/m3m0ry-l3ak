#include "main.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout<<"Working!!!\n";

    // init all the primitives required for allegro to startup
    allegro_init();


    set_color_depth(COLORDEPTH);
    graphics_init(WINDOW, 1024, 768);   // for testing -- default == WINDOWED mode

    create_instances();
    sndfx sfx;
    sfx.init_load_sound();
    //display_splash(); // commenting this for the purpose of writing new code for this
    install_keyboard();

    sfx.play_sound(MENU);
    int dispRetVal = display_terminal(true, "n@$h>>> ");
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
    sfx.stop_sound(MENU);

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

        In short I have write three more variables of integer type. The above part has been completed
        The writing of these data variables needs to be done -- as in the comditions that needs to be
        checked before the values are modified.

        Next to create the graphics for the intro cutscene.
        Create the function that will display the story based on the level number the user is in.
    */

    graphics_init(WINDOW, 1024, 768);
    sfx.play_sound(FSND);   // No level check for this -- the music will be played one after the other

    // redesigning the sound library first

    // tasks to be done:
    // 1. Redesign the libSound
    // 2. create the appropriate profile file and read & write from that file

    // the problem is with the type of converter that are being used to convert the files
    // create the user profile

    usrProfile usrInst;
    bool calledOnce = false;    // not yet called
    bool isShown = false;   // not yet shown

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
            usrInst.display_level_intro();
            isShown = true;
        }
        // some seg fault is occuring leading to the crash of the program
        // check out the crash of that -- checking to be done in the testBed
        update_screen();
    }
    sfx.stop_sound(FSND);

    sfx.destroy_sound_instances();
    destroy_instances();    // back_end seg_fault existing at this point -- probing inside for
    // more information
    allegro_exit();
    return EXIT_SUCCESS;
}
END_OF_MAIN();/**/
