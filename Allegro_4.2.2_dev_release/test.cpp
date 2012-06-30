/*#include "main.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout<<"Working!!!\n";

    allegro_init();
    install_keyboard();
    install_mouse();

    set_color_depth(32);
    if(set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1024, 760, 0, 0) != 0)
    {
        allegro_message("Resolution not set");
        allegro_exit();
    }

    BITMAP *dBuffer = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP *mainbgImg = load_bitmap("./data/bck_2.bmp", NULL);
    BITMAP *consoleImg = load_bitmap("./data/console.bmp", NULL);

    // the upper part is working fine -- this is just a POC that I have -- rather a COC
    // start designing and implementing the game engine -- the main one

    BITMAP *firstConsoleAlloc;
    BITMAP *secConsoleAlloc;

    BITMAP *tempStorage = create_bitmap(dBuffer->w, dBuffer->h);    // This is for saving the screen state
    int rdKey;
    char scancode;
    char asciiChar;

    txtBox sTxt;
    firstConsoleAlloc = allocBITMAP(76, 27, text_length(font, "D"), text_height(font));
    sTxt.cursorVisible = true;
    sTxt.curColor = makecol(255, 255, 255);
    sTxt.txtColor = makecol(0, 255, 0); // the text will be of green color
    sTxt.init(76, 27, firstConsoleAlloc, font);
    bool isDisplayed = false;   // the console image has not been shown till now

    while(!key[KEY_ESC])
    {
        // from here write the code that was used for the writing the routines of uname_accept() function
        // in the main project space
        while(keypressed())
        {
            rdKey = readkey();
            asciiChar = rdKey & 0xFF;   // create the txtBox instance -- created
            scancode = rdKey >> 8;

            switch(scancode)
            {
                case KEY_F5:
                    // display the console image
                    // take the necessary steps for the same -- screen state might be required to be saved
                    if(!isDisplayed)
                    {
                        // display the images

                        // first save the screen state
                        blit(dBuffer, tempStorage, 100, 100, 0, 0, consoleImg->w, consoleImg->h);

                        // display the firstAllocImg on the consoleImg -- here is another problem --
                        // the parent image for the text image is the same -- hence the new image for the
                        // subsequent call for the display_terminal will be a big problem -- I will also be
                        // unable to clear the bitmap -- since all the things might go away from the parent
                        // image -- have to find out a different way

                        // One way that is coming in mind -- use separate parent images -- pointing to the same
                        // image and then do the same.

                        // Another approach -- on_key_Press(KEY_F5) -- just display the consoleImg and then check
                        // another variable whether that is the first occurence of the consoleImg or not -- in case
                        // the first -- allocFirstImg will be placed. Inc(consoleImg occurrence) -- check again and
                        // repeat -- have to check this approach -- this might work out

                        // Will be checked out later
                    }
                break;

                case KEY_DEL:
                break;
            }
        }
    }
    allegro_exit();
    return EXIT_SUCCESS;
}
END_OF_MAIN();/**/
