#include "main.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout<<"Working!!!\n";

    // create the surfaces
    SDL_Surface *screen = NULL; // the screen that will be handling all the problems
    SDL_Surface *mainBg = NULL;

    // Init SDL
    SDL_Init(SDL_INIT_EVERYTHING);

    // setting up the screen
    screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);

    // Load the local image
    mainBg = SDL_LoadBMP("./cb.bmp");

    // Blit SurfaceOnScreen
    SDL_BlitSurface(mainBg, NULL, screen, NULL);

    // update the screen
    SDL_Flip(screen);

    // Pause for some time
    SDL_Delay(2000);

    // free Mem
    SDL_FreeSurface(mainBg);

    // Quit SDL -- making sure SDL cleans up before quitting
    atexit(SDL_Quit);


    return EXIT_SUCCESS;
}
