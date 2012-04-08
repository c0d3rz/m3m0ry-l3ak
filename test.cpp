#include <iostream>
#include <cstdlib>

#include <allegro.h>
#include "libGraphics.h"
#include "libUsr.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout<<"Working!!!\n";

    allegro_init();
    install_keyboard();

    int scrWidthReso, scrHeightReso;
    get_desktop_resolution(&scrWidthReso, &scrHeightReso);

    set_color_depth(32);
    int retVal = set_gfx_mode(GFX_AUTODETECT_WINDOWED, scrWidthReso, scrHeightReso, 0, 0);
    if(retVal != 0)
    {
        allegro_message("Error while setting resolution -- program will exit");
        destroy_instances();
        allegro_exit();
    }

    create_instances();

    bool loadOnce = false;
    bool showedOnce = false;
    usrProfile profileInst;
    profileInst.usrProfileInit();
    while(!key[KEY_ESC])
    {
        if(!loadOnce)
        {
            profileInst.load_profile();
            loadOnce = true;
        }

        // now comes the display_story part
        if(!showedOnce) // there should also be a check on whether the mission has been failed or not
        // in that case again show the level intro
        {
            profileInst.display_level_intro();  // start debugging from this part of the code
            showedOnce = true;
        }
    }
    destroy_instances();
    allegro_exit();
    return 0;
}
END_OF_MAIN();/**/
