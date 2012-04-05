#ifndef LIBGRAPHICS_H_INCLUDED
#define LIBGRAPHICS_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

#include <allegro.h>
#include <unistd.h>
#include "txtBox.h"
#include "libSound.h"   // why the hell is this not working????!!!!!
#include "data/gfx_util.h"

// Macros
#define WINDOW 0
#define FULLSCR 1

#define CURCOLOR makecol(255, 255, 255)
#define TXTCOLOR makecol(230, 230, 230)
#define CBLACK makecol(0, 0, 0)

#define COLORDEPTH 32

#define OPAQ 1
#define TRANS 0
#define STARTX 1
#define POWEROFF 2
#define CREDDISP 3
#define DISPEND 99

#define SPLASHSAV 10
#define SPLASHBLT 11
#define CONSLSAV 20
#define CONSLBLT 21
#define CREDSAV 30
#define CREDBLT 31
#define LOGINSAV 40
#define LOGINBLT 41

#define UNAME 1
#define PASWD 2

#define CBLACK makecol(0, 0, 0)
#define CWHITE makecol(255, 255, 255)
#define CGREEN makecol(0, 255, 0)
#define CTXTCOL makecol(255, 242, 138)
#define MAXCHAR 8

void graphics_init(int mode, int widthReso, int heightReso);   // calls all other funstions for setting up the grahics primitives

void create_instances();
void destroy_instances();

void update_screen();   // overall update of the screen
void blit_on_dBuffer(BITMAP *inpBmp, int blitPosx, int blitPosy, int blitMode); // blit the provided bitmap at the location specified in the double buffer

void display_boot_seq();    // display the starting boot sequence
void display_splash();  // show the splash image for this game
int display_terminal(bool mode, const std::string& inpPromptContent);    // for some commands
void display_credits(); // display the credits -- removing the display_login function
std::string query_uname(); // username query
void display_intro(int mode, std::string inpEpName);   // give the mode to display that intro -- decide other modes too

// internal functions
void _seq_display_(std::vector<std::string> inpVector, BITMAP *inpBitmap, int allocWidth, int allocHeight, int inpBmpBlitx, int inpBmpBlity, int dBufBlitx, int dBufBlity, bool cursorVisibility, int txtColor); // character by character display
void _blit_translucent_bmp_(BITMAP *inpBitmap, int alphaGradVal, int blitPosx, int blitPosy); // set the translucency value and draw the translucent sprite
void _blit_translucent_bmp_(BITMAP *inpGuestBitmap, BITMAP *inpHostBitmap, int alphaGradVal, int blitPosx, int blitPosy);  // function overloaded here -- makes bmp translucent with respect to the hostBmp
void _fade_in_(BITMAP *inpBitmap, int blitPosx, int blitPosy, int fadeRate);   // fade in an image
void _fade_out_(BITMAP *inpBitmap, int blitPosx, int blitPosy, int fadeRate);  // fade out an image
void _save_reblit_buffer_state_(int blitState); // saves the buffer state before the image is being
void _translucent_bmp_txt_print_(BITMAP *inpHostBmp, BITMAP *inpTxtBmp, int reblitState, int blitTxtBmpPosx, int blitTxtBmpPosy, int alphaGradVal, int blitTransBmpPosx, int blitTransBmpPosy); // display the text on translucent BMP without losing the translucency
void _handle_event_(BITMAP *consoleTextBmp, int keyRead, txtBox& inpObj, std::string& inpCliStr, bool& inpLoopCont, int &returnVal, std::string& desPromptStr, bool checkBootLvl);  // handle key_events --> non main Engine

bool gfx_error_handler(BITMAP *inpBmp); // bitmap error checker

#endif // LIBGRAPHICS_H_INCLUDED
