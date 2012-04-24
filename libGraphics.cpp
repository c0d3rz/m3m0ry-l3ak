#include "libGraphics.h"

using namespace std;

// ------------- variables ---------------------
int sysWidth, sysHeight;    // system resolution
// ---------------------------------------------

// ------------- BITMAPS -----------------------
BITMAP *dBuffer;   // double buffer
BITMAP *bootImg;    // boot sequence Image
BITMAP *tempStorage;    // temp storage
BITMAP *secTempStorage; // the secondary temporary storage
BITMAP *splashImg;  // the splash image
BITMAP *projNameImg;    // the project name displayer
BITMAP *consoleImg; // the command_prompt/terminal
BITMAP *creditImg;  // display credit image
BITMAP *loginBckImg;    // the login screen/uname_passwd login image background
BITMAP *upQueryImg;    // the username and passwd query image
BITMAP *mainBgImg;  // the main background image
BITMAP *webBrowserImg;  // the web browser image
BITMAP *prevDisplayImg;    // level zero pre display image
DATAFILE *gfxDat;   // the gfx_datafile
// ---------------------------------------------


// ------------ graphics initialisation functions -----------------------
void graphics_init(int mode, int widthReso, int heightReso)
{
    int ret_val;
    switch(mode)
    {
        case WINDOW:
            ret_val = set_gfx_mode(GFX_AUTODETECT_WINDOWED,widthReso, heightReso, 0, 0 );
            if(ret_val != 0)
                exit(0);
        break;

        case FULLSCR:
            ret_val = set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, widthReso, heightReso, 0, 0);
            //_check_err_(ret_val);
            if(ret_val != 0)
                exit(0);
        break;
        default:
        break;
    }
}

void create_instances()
{
    get_desktop_resolution(&sysWidth, &sysHeight);
    // here try to implement the header file to load the data from the DAT file.
    dBuffer = create_bitmap(sysWidth, sysHeight);
    tempStorage = create_bitmap(sysWidth, sysHeight);
    secTempStorage = create_bitmap(sysWidth, sysHeight);

    // load the datafile here
    gfxDat = load_datafile("./data/gfx_util.dat");

    bootImg = (BITMAP *)gfxDat[BOOTIMG_BMP].dat;
    splashImg = (BITMAP *)gfxDat[SPLASH_BMP].dat;
    projNameImg = (BITMAP *)gfxDat[PROJ_NAME_BMP].dat;
    consoleImg = (BITMAP *)gfxDat[CONSOLE_BMP].dat;
    creditImg = (BITMAP *)gfxDat[CREDITS_BMP].dat;
    loginBckImg = (BITMAP *)gfxDat[UNAME_LOGIN_BCK_BMP].dat;
    //upQueryImg = (BITMAP *)gfxDat[UN_PW_QUERY_BMP].dat;
    upQueryImg = (BITMAP *)gfxDat[UN_PW_QUERY_DUP_BMP].dat;
    mainBgImg = (BITMAP *)gfxDat[BCK_2_BMP].dat;
    webBrowserImg = (BITMAP *)gfxDat[WEBBROWSER_BMP].dat;
    prevDisplayImg = (BITMAP *)gfxDat[PREV_BMP].dat;

    // error checking part
    if(gfx_error_handler(bootImg) && gfx_error_handler(splashImg) && gfxDat && gfx_error_handler(projNameImg) && gfx_error_handler(consoleImg)\
    && gfx_error_handler(creditImg) && gfx_error_handler(secTempStorage) && gfx_error_handler(loginBckImg) && gfx_error_handler(upQueryImg)\
    && gfx_error_handler(mainBgImg) && gfx_error_handler(webBrowserImg) && gfx_error_handler(prevDisplayImg));
    else
    {
        allegro_message("Error loading game resource files in memory");
        exit(0);
    }
}

void destroy_instances()
{
    destroy_bitmap(dBuffer);
    destroy_bitmap(tempStorage);
    destroy_bitmap(secTempStorage);

    unload_datafile(gfxDat);    // SegFault removed -- make an update as soon as possible
    // a big hurdle is removed -- more tweakings require to be done
}

void update_screen()    // blits the double buffer on the screen
{
    blit(dBuffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}

void blit_on_dBuffer(BITMAP *inpBmp, int blitPosx, int blitPosy, int blitMode)
{
    switch(blitMode)
    {
        case OPAQ:
            blit(inpBmp, dBuffer, 0, 0, blitPosx, blitPosy, inpBmp->w, inpBmp->h);
        break;
        case TRANS:
            _blit_translucent_bmp_(inpBmp, 128, blitPosx, blitPosy);
        break;
    }
}
// ----------------------------------------------------------------------------------------


// --------------------------------- graphics display functions ---------------------------
void display_boot_seq()
{
    remove_keyboard();
    vector <string> bootSeq;    // the game boot sequence

    // populate the vector <string> variable here -- this will be the story
    // pass that to an internal implementation of the displayer

    bootSeq.push_back("Starting VMLinuz");    // the boot sequence story starts here
    bootSeq.push_back("Initializing cgroup subsys cpuset");
    bootSeq.push_back("Initializing cgroup subsys cpu");
    bootSeq.push_back("BIOS-provided physical RAM map:");
    bootSeq.push_back("BIOS-e820: 0000000000000000 - 000000000009f000 (usable)");
    bootSeq.push_back("BIOS-e820: 000000000009f000 - 00000000000a0000 (reserved)");
    bootSeq.push_back("BIOS-e820: 0000000000100000 - 000000003f6d3400 (usable)");
    bootSeq.push_back("BIOS-e820: 000000003f6d3400 - 0000000040000000 (reserved)");
    bootSeq.push_back("DMI 2.4 present.");
    bootSeq.push_back("last_pfn = 0x3f6d3 max_arch_pfn = 0x100000");
    bootSeq.push_back("MTRR default type: uncachable");
    bootSeq.push_back("init_memory_mapping: 0000000000000000-00000000377fe000");

    // the sequence has been populated
    // now let's pass this vector to some obscure function that will the work of displaying this

    _seq_display_(bootSeq, bootImg, 200, 100, 10, 10, 45, 30, false, CGREEN, LINEBYLN);  // lower the size of the allocation of the text
    // bitmap -- the faster the display
    install_keyboard();
}

void display_splash()
{
    // inpBitmap is the splash bitmap that will be displayed using the fade in and fade out
    // gfx effect

    // let the screwing up begin -- first I need to write the routines for the fade_out and the fade_in

    _fade_in_(splashImg, 0, 0, 64);
    _fade_out_(splashImg, 0, 0, 64);

    _fade_in_(projNameImg, 0, 0, 64);
    _fade_out_(projNameImg, 0, 0, 64);
}

int display_terminal(bool mode, const string& inpPromptContent)
{
    string _PROMPT = inpPromptContent;


    if(mode)
    {
        blit_on_dBuffer(loginBckImg, 0, 0, OPAQ);   // just to improve the looks -- another problem presolved
        _save_reblit_buffer_state_(CONSLSAV);   // <-- according to the blit state, make the change
        _blit_translucent_bmp_(consoleImg, 175, 100, 100);
        update_screen();


        // code for using only three commands -- first display the terminal image
        // save the screenshot before blitting the image
        //_save_reblit_buffer_state_(CONSLSAV);   // <-- according to the blit state, make the change
        //_blit_translucent_bmp_(consoleImg, 128, 100, 100);
        //update_screen();

        // need some variables for this experiment
        char asciiChar;
        int rdKey;
        int retVal; // CREDDISP macro will be used for the checking part
        string cli; // command line input
        string tempCli; // temp cli key value string storage

        bool contLoop = true;
        txtBox txtInst;

        BITMAP* consoleText = allocBITMAP(76, 27, text_length(font, "D"), text_height(font));
        txtInst.cursorVisible = true;
        txtInst.curColor = cWHITE;
        txtInst.txtColor = cGREEN;
        txtInst.init(76, 27, consoleText, font);
        int txtBoxPosx, txtBoxPosy; // for the position of the cursor

        /*
            Text Printing working with proper KEY_ENTER handling and corr text
            newline printing. Now to make it generic.--> made this partgeneric -- check out the handle_event function

            That is an internal function that will be handling the events -- now to remove the redundancies
            Also the changelog needs to be updated.
        */

        // write routine for the return of state as command is entered
        txtInst.writeText("Type the following commands\n");
        txtInst.writeText("1. 'startx' to start the boot\n2. 'poweroff' to exit the system from the present state\n3. 'credits' to see the credits\n");
        txtInst.writeText(const_cast<char *>(_PROMPT.c_str()));
        _translucent_bmp_txt_print_(consoleImg, consoleText, CONSLBLT, 10, 40, 175, 100, 100);
        while(contLoop)
        {
            while(keypressed())
            {
                rdKey = readkey();
                asciiChar = rdKey & 0xFF;
                // check for ascii values -- no unicode for now :-(

                // earlier text printing code
                // current code is far better than this implementation

                /*if(asciiChar >= 32 && asciiChar <= 126)
                {
                    txtInst.writeChar(asciiChar);
                    _translucent_bmp_txt_print_(consoleImg, consoleText, CONSLBLT, 10, 40, 128, 100, 100);
                    cli.push_back(asciiChar);   // check out insert

                    // might have to change the text pushing algorithm in the inpCliStr
                }*/

                if(asciiChar >= 32 && asciiChar <= 126)
                {
                    // get the current position of txtBoxPosx, txtBoxPosy
                    txtInst.getxy(txtBoxPosx, txtBoxPosy);
                    if((txtBoxPosx - _PROMPT.length() == 0) && (!cli.empty()))
                    {
                        txtInst.writeChar(asciiChar);
                        _translucent_bmp_txt_print_(consoleImg, consoleText, CONSLBLT, 10, 40, 175, 100, 100);

                        // first get the current cursor position
                        txtInst.getxy(txtBoxPosx, txtBoxPosy);
                        cli.insert(txtBoxPosx - _PROMPT.length() - 1, 1, asciiChar); // insert one char that has been pressed -- poll keyboard

                        // reset the cursor position again at the end of the prompt
                        clear_to_color(consoleText, makecol(0, 0, 0));
                        txtInst.reset_cursor_pos(_PROMPT.length());
                        txtInst.cursorVisible = false;
                        txtInst.writeText(const_cast<char *>(cli.c_str()));

                        txtInst.cursorVisible = true;
                        txtInst.reset_cursor_pos(txtBoxPosx++);
                    }
                    else if((txtBoxPosx - _PROMPT.length() > 0) && (txtBoxPosx - _PROMPT.length() < cli.length())) // if the position of the cursor is inside the command that has been input
                    {
                        txtInst.writeChar(asciiChar);
                        _translucent_bmp_txt_print_(consoleImg, consoleText, CONSLBLT, 10, 40, 175, 100, 100);

                        // first get the current cursor position
                        txtInst.getxy(txtBoxPosx, txtBoxPosy);
                        cli.insert(txtBoxPosx - _PROMPT.length() - 1, 1, asciiChar); // insert one char that has been pressed -- poll keyboard

                        // reset the cursor position again at the end of the prompt
                        clear_to_color(consoleText, makecol(0, 0, 0));
                        txtInst.reset_cursor_pos(_PROMPT.length());
                        txtInst.cursorVisible = false;
                        txtInst.writeText(const_cast<char *>(cli.c_str()));

                        txtInst.cursorVisible = true;
                        txtInst.reset_cursor_pos(txtBoxPosx++);
                    }
                    else
                    {
                        txtInst.writeChar(asciiChar);
                        _translucent_bmp_txt_print_(consoleImg, consoleText, CONSLBLT, 10, 40, 175, 100, 100);

                        // first get the current cursor position
                        txtInst.getxy(txtBoxPosx, txtBoxPosy);
                        cli.insert(txtBoxPosx - _PROMPT.length() - 1, 1, asciiChar);
                    }
                }

                // the handle event will be handling the events for the terminal display
                // including the preboot as well as the post boot ones

                // in the preboot one, it will be using a flag -- and if it false
                // in the post boot terminal display it will be passing the command to the
                // library libNxClTokenizer -- needs more tweaking

                _handle_event_(consoleText, rdKey, txtInst, cli, contLoop, retVal, _PROMPT, false);  // --> since preBoot level
                _translucent_bmp_txt_print_(consoleImg, consoleText, CONSLBLT, 10, 40, 175, 100, 100);
            }
            update_screen();
        }
        _save_reblit_buffer_state_(CONSLBLT);
        update_screen();
        return retVal;
    }
    else
    {
        // code for using every commnad that is available
        // the cliTokenizer will be used here
    }
}

void display_credits()
{
    // before blitting -- save the screenshot -- and reblit once the del key is pressed
    remove_keyboard();
    _save_reblit_buffer_state_(CREDSAV);
    vector<string> credVec;

    // now populate the credit display vector
    credVec.push_back("nb0dy");
    credVec.push_back("-----------------------------------------------------------");
    credVec.push_back("Currently pursuing his MS degree from University of Arizona, Tucson");
    credVec.push_back("A hobbyist programmer, electronics hobbyist -- developer of projects");
    credVec.push_back("EyeMp, Atmega32 Calculator and the author of the article - Pattern");
    credVec.push_back("Recognition using Principal Component Analysis.\n");
    credVec.push_back("Visit his website -- www.binarydigits10.com\n");
    credVec.push_back("Developer of libxTextParser, libTxtBox and keyboard handling engine.\n");

    credVec.push_back("cr4zy_d33p");
    credVec.push_back("-----------------------------------------------------------");
    credVec.push_back("Cugrrently pursuing his pre-graduation degree. A gamer by nature -- ");
    credVec.push_back("found out the SPLASH SCR bug when inducted into the project. Mainly ");
    credVec.push_back("managed the testing area of the project.\n");

    credVec.push_back("pr4jw41");
    credVec.push_back("-----------------------------------------------------------");
    credVec.push_back("Developer\n");

    credVec.push_back("[Hit any key to return back to the console]");

    _seq_display_(credVec, creditImg, 75, 20, 5, 20, 150, 250, false, CTXTCOL, CHBYCH);  // since it is not some vid display
    // Issue resolved using the remove and install keyboard functions
    install_keyboard(); // the bug that was here in the last release has been fixed
    // the following allegro built-in fucntion helped in solving this
    readkey();
    _save_reblit_buffer_state_(CREDBLT);
    // First save the blit state
}

string query_uname()
{
    // clearing the reblits -- all reblits completed till now
    clear_to_color(tempStorage, CBLACK);
    clear_to_color(secTempStorage, CBLACK);
    blit_on_dBuffer(loginBckImg, 0, 0, OPAQ);

    _save_reblit_buffer_state_(LOGINSAV);
    textout_ex(upQueryImg, font, "Username", 170, 0, CGREEN, -1);   // display at the middle of the query frame
    _blit_translucent_bmp_(upQueryImg, 200, 315, 265);
    update_screen();

    // follow the display_terminal function body
    char asciiChar;
    int rdKey;
    string inpUsrName;  // the input username
    string _PROMPT_ = "$> ";
    int alphaCount = 0; // for limiting the number of characters that can be inserted in the username
    // part

    // create the other things just like that of display_terminal
    bool contLoop = true;   // continue asking the username as long as the validation fails
    txtBox sTxt;

    //BITMAP *usrText = allocBITMAP(76, 27, text_length(font, "D"), text_height(font));
    BITMAP *usrText = allocBITMAP(46, 1, text_length(font, "D"), text_height(font));
    sTxt.cursorVisible = true;  // the cursor should be visible in this one
    sTxt.curColor = cWHITE;
    sTxt.txtColor = cGREEN;
    //sTxt.init(76, 27, usrText, font);
    sTxt.init(46, 1, usrText, font);
    int txtBoxPosx, txtBoxPosy; // the x,y pos of the cursor

    sTxt.writeText(const_cast<char *>(_PROMPT_.c_str()));
    _translucent_bmp_txt_print_(upQueryImg, usrText, LOGINBLT, 10, 10, 200, 315, 265);

    while(contLoop)
    {
        // the contLoop will run as long as the validation fails
        while(keypressed())
        {
            rdKey = readkey();
            asciiChar = rdKey & 0xFF;

            if(asciiChar >= 32 && asciiChar <= 126)
            {
                if(alphaCount < 9)
                    alphaCount++;
                sTxt.getxy(txtBoxPosx, txtBoxPosy);
                if((txtBoxPosx - _PROMPT_.length() == 0) && (!inpUsrName.empty()) && alphaCount < MAXCHAR)
                {
                    sTxt.writeChar(asciiChar);
                    _translucent_bmp_txt_print_(upQueryImg, usrText, LOGINBLT, 10, 10, 200, 315, 265);


                    // first get the current cursor position
                    sTxt.getxy(txtBoxPosx, txtBoxPosy);
                    inpUsrName.insert(txtBoxPosx - _PROMPT_.length() -1, 1, asciiChar);

                    // set cursor position at the appropriate position
                    clear_to_color(usrText, CBLACK);
                    sTxt.reset_cursor_pos(_PROMPT_.length());
                    sTxt.cursorVisible = false;
                    sTxt.writeText(const_cast<char *>(inpUsrName.c_str()));

                    sTxt.cursorVisible = true;
                    sTxt.reset_cursor_pos(txtBoxPosx++);
                }
                else if((txtBoxPosx - _PROMPT_.length() > 0) && (txtBoxPosx - _PROMPT_.length() < inpUsrName.length()) && alphaCount < 9)
                {
                    sTxt.writeChar(asciiChar);
                    _translucent_bmp_txt_print_(upQueryImg, usrText, LOGINBLT, 10, 10, 200, 315, 265);


                    // first get the current cursor position
                    sTxt.getxy(txtBoxPosx, txtBoxPosy);
                    inpUsrName.insert(txtBoxPosx - _PROMPT_.length() -1, 1, asciiChar);

                    // set cursor position at the appropriate position
                    clear_to_color(usrText, CBLACK);
                    sTxt.reset_cursor_pos(_PROMPT_.length());
                    sTxt.cursorVisible = false;
                    sTxt.writeText(const_cast<char *>(inpUsrName.c_str()));

                    sTxt.cursorVisible = true;
                    sTxt.reset_cursor_pos(txtBoxPosx++);
                }
                else if(alphaCount < 9)
                {
                    sTxt.writeChar(asciiChar);
                    _translucent_bmp_txt_print_(upQueryImg, usrText, LOGINBLT, 10, 10, 200, 315, 265);

                    // first get the current cursor position
                    sTxt.getxy(txtBoxPosx, txtBoxPosy);
                    inpUsrName.insert(txtBoxPosx - _PROMPT_.length() -1, 1, asciiChar);
                }
            }



            sTxt.getxy(txtBoxPosx, txtBoxPosy);
            int curPos = txtBoxPosx - _PROMPT_.length() - 1;    // point to the last of the string
            if(curPos == -1 && inpUsrName.empty())
                curPos = 0;

            // Write the event handler for this one -- incorporate this here itself
            switch(rdKey >> 8)
            {
                // now the last one remains -- the KEY_ENTER that will do the checking of the entered username
                case KEY_ENTER:
                    // do the validation check now
                    size_t irrevFound;
                    //if((inpUsrName.find("+") != string::npos) || (inpUsrName.find("-") != string::npos) || (inpUsrName.find("\\") != string::npos) || (inpUsrName.find("/") != string::npos) || (inpUsrName.find("?") == string::npos))
                        //contLoop = false;
                    //else
                        //inpUsrName.clear();
                    if(!inpUsrName.empty())
                    {
                        sTxt.writeChar('\n');
                        sTxt.writeText("Accepted Username> ");
                        sTxt.writeText(const_cast<char *>(inpUsrName.c_str()));
                        contLoop = false;
                    }
                    else
                    {
                        sTxt.writeChar('\n');
                        sTxt.writeText(const_cast<char *>(_PROMPT_.c_str()));
                        _translucent_bmp_txt_print_(upQueryImg, usrText, LOGINBLT, 10, 10, 200, 315, 265);
                    }

                    // now the loop execution will be stopping exactly after one iteration
                    // the next work will be done in the lubUsr.cpp

                    // Next task to be implemented
                    // 1. write the necessary details in the profile file that will be created
                    // See the encryption techniques and the sequences used in paste.ubuntu.com/884471
                break;

                case KEY_LEFT:
                    sTxt.getxy(txtBoxPosx, txtBoxPosy);

                    if(txtBoxPosx == _PROMPT_.length())
                    {
                        if((txtBoxPosx - _PROMPT_.length() -1) == 0)
                        {
                            sTxt.gotoxy(--txtBoxPosx, txtBoxPosy);
                            txtBoxPosx = _PROMPT_.length();
                        }
                        break;
                    }
                    sTxt.gotoxy(--txtBoxPosx, txtBoxPosy);
                break;

                case KEY_RIGHT:
                    sTxt.getxy(txtBoxPosx, txtBoxPosy);
                    if(((txtBoxPosx == _PROMPT_.length()) && inpUsrName.empty()) || (txtBoxPosx == _PROMPT_.length() + inpUsrName.length()))
                        break;
                    sTxt.gotoxy(++txtBoxPosx, txtBoxPosy);
                break;

                case KEY_BACKSPACE:
                    // first check only the first part
                    int curLength = inpUsrName.length();    // the current length of the string before removing the character
                    sTxt.getxy(txtBoxPosx, txtBoxPosy);
                    if(txtBoxPosx == _PROMPT_.length())
                        break;

                    sTxt.delChar(--txtBoxPosx, txtBoxPosy);
                    sTxt.gotoxy(txtBoxPosx, txtBoxPosy);

                    if(curPos >= 0 || curPos < inpUsrName.length())
                        inpUsrName.erase(curPos, 1);

                    // for the cursor
                    if(!inpUsrName.empty())
                    {
                        clear_to_color(usrText, CBLACK);
                        sTxt.reset_cursor_pos(_PROMPT_.length());

                        for(int count = 0; count < curLength; count++)
                            sTxt.writeText(" ");

                        sTxt.cursorVisible = false;
                        sTxt.reset_cursor_pos(_PROMPT_.length());
                        sTxt.writeText(const_cast<char *>(inpUsrName.c_str()));
                        sTxt.cursorVisible = true;
                        sTxt.reset_cursor_pos(txtBoxPosx);
                    }

                    alphaCount = inpUsrName.length();
                break;
            }
            _translucent_bmp_txt_print_(upQueryImg, usrText, LOGINBLT, 10, 10, 200, 315, 265);
        }
        update_screen();
    }
    return inpUsrName;
}

void display_intro(int mode, string inpEpName, string inpUserName)  // I might be needing the object to be passed
{
    // the mode will be for each and every mission rather than double checking mission and the level

    switch(mode)
    {
        case INTRO: // this is for the level zero part
            // display the required gfx and also play the appropriate sound for that part -- check
            // if the sound can be played properly played or not

            // create gfx for the INTRO -- level zero -- this will be a bit big cutscene.

            // first part will be containing a display of the terminal along with the blitting
            // of the webbrowser showing the arrest of the antagonist.

            // so first I need to display the display_terminal() -- as in I am not calling that function
            // I will just blit that image on the double buffer

            // before I proceed with the cutscenes always remember -- remove the keyboard
            // after finishing the cutscene -- install the keyboard again
            remove_keyboard();
            clear_to_color(screen, CBLACK);
            blit_on_dBuffer(mainBgImg, 0, 0, OPAQ);

            vector<string> lvlzIntroTxt;
            lvlzIntroTxt.push_back("n@$h> netmap -v -A static.internic.lan");
            lvlzIntroTxt.push_back("Starting netmap v1.0\n");
            lvlzIntroTxt.push_back("Loaded 30 scripts for scanning");
            lvlzIntroTxt.push_back("Initiating ping scan");
            lvlzIntroTxt.push_back("Scanning 218.92.64.48[2 ports]");
            lvlzIntroTxt.push_back("Completed ping scan -- ttl elapsed[total number of hosts 1]");
            lvlzIntroTxt.push_back("Initiating parallel DNS resolution of 1 host");
            lvlzIntroTxt.push_back("Completed parallel DNS resolution");
            lvlzIntroTxt.push_back("Initiating connect scan");
            lvlzIntroTxt.push_back("Scanning 218.92.64.48[100 ports]");
            lvlzIntroTxt.push_back("Discovered open port 80/tcp on 218.92.64.48\nCompleted Connect Scan");
            lvlzIntroTxt.push_back("NSE: Script Scanning completed.\nHost 218.92.64.48 is up (0.36s latency).\nInteresting ports on 216.218.248.135:\
Not shown: 997 filtered ports\n\nPORT    STATE  SERVICE VERSION\n22/tcp  closed ssh\n80/tcp  open   http    Apache httpd 2.2.20 ((Unix))\
\n|_ html-title: internic.lan: This is Secure Internic LAN\n\n443/tcp closed https");

            lvlzIntroTxt.push_back("n@$h> ");

            // the display for the terminal has been done -- now to display the web browser
            // I think I might be needing two displays as in two blits to display the end part
            // of the game. Whatever, I will check it when the appropriate time comes up

            // display the web-browser now -- This one will be displaying the main antagonists
            // capture to the user

            // I might also have to insert some time delay for this so that the user is able to read
            // the story properly

            // displaying the web-browser after the call to the seq_displayer function for the first
            // instance


            // now call the seq_displayer function to display the aforewritten text
            _seq_display_(lvlzIntroTxt, consoleImg, 76, 27, 10, 40, 100, 100, true, CGREEN, LINEBYLN);
            update_screen();

            // display and blit on the web-browser -- done
            blit_on_dBuffer(webBrowserImg, 250, 250, OPAQ);

            // write the website address at the top of the image where the space has been created
            // another concept needs to be checked for this web browser that might be implemented in case
            // the concept works out fine
            // writing the web site address at the top of the webBrowser image
            textout_ex(webBrowserImg, font, "www.undergroundnews.com", 10, 8, CGREEN, -1);

            // making no change to the gfx of the webbrowser
            // writing new text to the webBrowser display

            // checking another concept
            vector<string> brwDisplayVec;   // this is the display for the first browser window
            brwDisplayVec.push_back("Breaking News\n");
            brwDisplayVec.push_back("----------------------------------------\n\n");
            brwDisplayVec.push_back("Revered Head of Security of Internic was today arrested");
            brwDisplayVec.push_back("on multiple accounts of espionage and revealing of");
            brwDisplayVec.push_back("information to rival companies for extra money. Apart from");
            brwDisplayVec.push_back("that his accomplice was the head of Management of Secure");
            brwDisplayVec.push_back("Digital Corp which had tried to sneak into the operations");
            brwDisplayVec.push_back("as well as used the information to play the companies' resources");
            //brwDisplayVec.push_back("\n\n\n\nPress a key to continue"); // better write this text in some
            // other part of the screen


            _seq_display_(brwDisplayVec, webBrowserImg, 76, 27, 10, 40, 250, 250, false, CGREEN, LINEBYLN);
            textout_ex(dBuffer, font, "Press a key to continue", 10, 10, CGREEN, -1);
            update_screen();

            // allowing the user to carry on with the cut scene display
            install_keyboard();
            readkey();  // this is working fine
            remove_keyboard();

            // more text needs to be written for the first display of the web browser
            // plus trying to show another character image in that

            textout_ex(dBuffer, font, "Press a key to continue", 10, 10, CBLACK, -1);
            // the action event will be displayed at the top left corner of the background image
            // will be displayed when the user action will be required and then it will go back again
            blit_on_dBuffer(webBrowserImg, 150, 150, OPAQ);

            // creating another vector to display some other text to the user
            vector<string> brDisplayVec;
            brDisplayVec.push_back("Breaking news");
            brDisplayVec.push_back("-------------------------------------------------------\n");
            brDisplayVec.push_back("Jim Lee's adjutant was also arrested last night from his home");
            brDisplayVec.push_back("on aiding and abetting his employer in numerous cases of fraud");
            brDisplayVec.push_back("The 26 year old Security specialist is also known as r4pt0r");
            brDisplayVec.push_back("in the underground community. A lot of news came up with the ");
            brDisplayVec.push_back("arrest of these people. Some underground hacker named " + inpUserName);
            brDisplayVec.push_back("has given up information about these activities. A special source");
            brDisplayVec.push_back("said that this " + inpUserName + " once was among the elite in the ");
            brDisplayVec.push_back("community, who left the scene and re-emerged just 6 weeks back");

            // now since the function requires the username to be provided -- the cutscenes
            // and the objective display screen text needs to be changed accordingly


            _seq_display_(brDisplayVec, webBrowserImg, 76, 27, 10, 40, 150, 150, false, CGREEN, LINEBYLN);
            // allow the user to carry on with the cut scene display

            install_keyboard();
            textout_ex(dBuffer, font, "Press a key to continue", 10, 10, CGREEN, -1);
            update_screen();
            readkey();
            textout_ex(dBuffer, font, "Press a key to continue", 10, 10, CBLACK, -1);
            update_screen();
            remove_keyboard();

            // let's start the next part of the coding
            _save_reblit_buffer_state_(FULLSAV);
            clear_to_color(dBuffer, CWHITE);
            update_screen();

            _handle_screen_tear(FULLBLT);

            for(long counter = 0; counter < 999999999; counter++);
            // I might have to make the screen_tear() function -- a generic one is what I mean
            // Let's start by building that -- need to play more music

            // making the screen tear function generic -- before that another implementation

            // now start the fade sequence
            clear_to_color(dBuffer, CBLACK);
            _fade_in_(prevDisplayImg, 0, 0, 64);
            _fade_out_(prevDisplayImg, 0, 0, 64);

            // Now to show what had happened 8 years before
            // In this part of the cut scene the display will contain the following components
            // 1. terminal_display() showing the typing of some commands
            // 2. A approve box will appear asking for access to some servers
            // 3. The NP main character will be allowing the access to that
            // 4. and after that -- there will be some warning boxes that will be appearing
            // 5. the whole space will be filled up with warning boxes saying the message
            // "WARNING! MEMORY LEAK"


            // Issues to be resolved:
            // 1. display HmFace to the user in WebBrowser
            // 2. Change the web address to something more realistic
            // 3. Change text display content of web browser -- check out some of the news papers
            // 4. If possible -- also display the name of the web browser -- WebTerminal[as suggested by cr4zy_d33p]

            // update code base to git and google code dump
            // google code will be done later -- git hub will be done now

            // Changelog will be changed after update to google code
            // bringing into sync both the code dumps

            // github dump updated -- now to write the other codes

            // the clear_dBuffer function needs to be called before the display is shifted
            // from one function to another -- some display issues with the FULLSCR mode

            // have to check out the issues
            install_keyboard();
        break;
    }
}

void clear_dBuffer()
{
    clear_to_color(dBuffer, CBLACK);
}

// ------------ the internal functions ----------------------------------------------------------------------
void _seq_display_(vector<string> inpVector, BITMAP *inpBitmap, int allocWidth, int allocHeight, int inpBmpBlitx, int inpBmpBlity, int dBufBlitx, int dBufBlity, bool cursorVisibility, int txtColor, int mode)
{
    // inpBitmap - the bitmap on which the text will be displayed
    // inpVector - the vector stack containing the display text content
    // allocWidth and allocHeight - for the allocation of the useImg, the allocation of the resolution
    // inpBmpBlitx and inpBmpBlity - blitting position for blitting the text blitted image on the input BITMAP image
    // dBufBlitx and dBufBlity - for blitting on the dBuffer at the specified location

    // The above part describes the vars that are being used for this function -- the algorithm in a nut shell
    BITMAP *useImg = allocBITMAP(allocWidth, allocHeight, text_length(font, "D"), text_height(font));
    txtBox sTxt;

    sTxt.cursorVisible = cursorVisibility;
    sTxt.curColor = CURCOLOR;
    sTxt.txtColor = txtColor;
    sTxt.init(allocWidth, allocHeight, useImg, font);

    // BITMAP *testImg = allocBITMAP(600, 400, text_length(font, "D"), text_height(font));

    vector<string>::iterator iter;
    unsigned int index;

    switch(mode)
    {
        case CHBYCH:
            for(iter = inpVector.begin(); iter != inpVector.end(); iter++)
            {
                /*sTxt.writeText(const_cast<char *>((*iter).c_str()));
                blit(useImg, inpBitmap, 0, 0, inpBmpBlitx, inpBmpBlity, useImg->w, useImg->h);
                blit_on_dBuffer(inpBitmap, dBufBlitx, dBufBlity);
                update_screen();*/
                for(index = 0; index < (*iter).length(); index++)
                {
                    sTxt.writeChar((*iter).at(index));
                    blit(useImg, inpBitmap, 0, 0, inpBmpBlitx, inpBmpBlity, useImg->w, useImg->h);
                    blit_on_dBuffer(inpBitmap, dBufBlitx, dBufBlity, OPAQ);
                    update_screen();
                }
                sTxt.writeChar('\n');
            }
        break;

        case LINEBYLN:
            for(iter = inpVector.begin(); iter != inpVector.end(); iter++)
            {
                sTxt.writeText(const_cast<char *>((*iter).c_str()));
                blit(useImg, inpBitmap, 0, 0, inpBmpBlitx, inpBmpBlity, useImg->w, useImg->h);
                blit_on_dBuffer(inpBitmap, dBufBlitx, dBufBlity, OPAQ);
                sTxt.writeChar('\n');
                update_screen();
                /*for(index = 0; index < (*iter).length(); index++)
                {
                    sTxt.writeChar((*iter).at(index));
                    blit(useImg, inpBitmap, 0, 0, inpBmpBlitx, inpBmpBlity, useImg->w, useImg->h);
                    blit_on_dBuffer(inpBitmap, dBufBlitx, dBufBlity, OPAQ);
                    update_screen();
                }*/
            }
        break;
    }
}

void _blit_translucent_bmp_(BITMAP *inpBitmap, int alphaGradVal, int blitPosx, int blitPosy)
{
    // the input bitmap is the bitmap that needs to be made translucent
    // the alphaGradVal var is the alphavalue that needs to be set

    set_alpha_blender();
    set_trans_blender(0, 0, 0, alphaGradVal);

    draw_trans_sprite(dBuffer, inpBitmap, blitPosx, blitPosy);
}

void _blit_translucent_bmp_(BITMAP *inpGuestBitmap, BITMAP *inpHostBitmap, int alphaGradVal, int blitPosx, int blitPosy)
{
    set_alpha_blender();
    set_trans_blender(0, 0, 0, alphaGradVal);

    draw_trans_sprite(inpHostBitmap, inpGuestBitmap, blitPosx, blitPosy);
}

void _fade_in_(BITMAP *inpBitmap, int blitPosx, int blitPosy, int fadeRate)
{
    _save_reblit_buffer_state_(SPLASHSAV);
    // fade in an image that is supplied as parameter
    for(; fadeRate < 256; fadeRate++)
    {
        _blit_translucent_bmp_(inpBitmap, fadeRate, 0, 0);
        usleep(50000);
        update_screen();
    }
}

void _fade_out_(BITMAP *inpBitmap, int blitPosx, int blitPosy, int fadeRate)
{
    for(fadeRate = 255 - fadeRate; fadeRate >= 0; fadeRate--)
    {
        _save_reblit_buffer_state_(SPLASHBLT);
        _blit_translucent_bmp_(inpBitmap, fadeRate, 0, 0);
        update_screen();
    }
}

void _save_reblit_buffer_state_(int blitState)
{
    // this will perform a switch operation based on the blit state provided
    // I think I might have to clear the tempStorage and the secTempStorage once the reblitting
    // has been done -- some check parameter needs to be created while saving the dBuf state

    // give some thought to this part of the code -- it is here where all the magic numbers and
    //hard coded stuff remains -- needs some more tweaking

    // Finalising the entry part of the game -- bugs removed from the console text printing
    // proper display of the credits.

    // Internal bug exits only in this part of the code -- CHECK IT OUT as early as possible
    switch(blitState)
    {
        case SPLASHSAV:
            blit(dBuffer, tempStorage, 0, 0, 0, 0, splashImg->w, splashImg->h); // a bit hard coded
        break;
        case SPLASHBLT:
            blit(tempStorage, dBuffer, 0, 0, 0, 0, splashImg->w, splashImg->h);
        break;

        case CONSLSAV:
            blit(dBuffer, tempStorage, 100, 100, 0, 0, consoleImg->w, consoleImg->h);
        break;
        case CONSLBLT:
            blit(tempStorage, dBuffer, 0, 0, 100, 100, consoleImg->w, consoleImg->h);
        break;

        case CREDSAV:
            blit(dBuffer, secTempStorage, 150, 250, 0, 0, creditImg->w, creditImg->h);
        break;
        case CREDBLT:
            blit(secTempStorage, dBuffer, 0, 0, 150, 250, creditImg->w, creditImg->h);
        break;

        case LOGINSAV:
            blit(dBuffer, tempStorage, 315, 265, 0, 0, upQueryImg->w, upQueryImg->h);
        break;
        case LOGINBLT:
            blit(tempStorage, dBuffer, 0, 0, 315, 265, upQueryImg->w, upQueryImg->h);
        break;

        case FULLSAV:
            blit(dBuffer, tempStorage, 0, 0, 0, 0, dBuffer->w, dBuffer->h);
        break;

        case FULLBLT:
            blit(tempStorage, dBuffer, 0, 0, 0, 0, dBuffer->w, dBuffer->h);
        break;
    }
}

void _translucent_bmp_txt_print_(BITMAP *inpHostBmp, BITMAP *inpTxtBmp, int reblitState, int blitTxtBmpPosx, int blitTxtBmpPosy, int alphaGradVal, int blitTransBmpPosx, int blitTransBmpPosy)
{
    // for this function to work properly, the coder needs to save the blank image space
    // on the tempStorage BMP and then specify a specific bitstate

    blit(inpTxtBmp, inpHostBmp, 0, 0, blitTxtBmpPosx, blitTxtBmpPosy, inpTxtBmp->w, inpTxtBmp->h);
    _save_reblit_buffer_state_(reblitState);
    _blit_translucent_bmp_(inpHostBmp, alphaGradVal, blitTransBmpPosx, blitTransBmpPosy);
}

void _handle_event_(BITMAP *consoleTextBmp, int keyRead, txtBox& inpObj, string& inpCliStr, bool& inpLoopCont, int &returnVal, string& desPromptStr, bool checkBootLvl)
{
    // will be handling the keyEvents -- display_terminal()

    // Key notes to be remembered while using/calling this function -- the last boolean value decides[checkBootLvl]
    // whether the it is preBoot or postBoot sequence -- if the value is false --> it is preBoot
    // else if the value is true --> it is postBoot
    int txtBoxPosx, txtBoxPosy; // cursorPosx, cursorPosy of the txtBox printing the text supplied
    inpObj.getxy(txtBoxPosx, txtBoxPosy);
    int curPos = txtBoxPosx - desPromptStr.length() - 1;    // point to the last of the string
    if(curPos == -1 && inpCliStr.empty())
        curPos = 0; // when the position is negative -- move the cursor pos to the zeroth index


    switch(keyRead >> 8)
    {
        case KEY_ENTER:
            // check this part -- needs tweaking
            inpObj.writeChar('\n');
            inpObj.writeText(const_cast<char *>(desPromptStr.c_str()));
            if(inpCliStr == "startx" && (!checkBootLvl))
            {
                returnVal = STARTX;
                inpCliStr.clear();
                inpLoopCont = false;
            }
            else if(inpCliStr == "poweroff" && (!checkBootLvl))
            {
                returnVal = POWEROFF;
                inpCliStr.clear();
                inpLoopCont = false;
            }
            else if(inpCliStr == "credits" && (!checkBootLvl))   // clear this part before moving in more and more
            {
                inpCliStr.clear();
                inpLoopCont = true;
                display_credits();

                inpObj.getxy(txtBoxPosx, txtBoxPosy);
                // cout<<txtBoxPosx<<endl; // even the cursor is not getting updated here
                // but the garbage command is getting displayed while the keys are being pressed after the
                // end of the text display
                // the bug still exists -- need to eradicate this problem

                // One solution is to make the credits display go away immediately
                // There will be some delay provided so that the display is there for the user to read
                // and there will be no keyboard esacpe from the credits

                // or the key delete functionality can be given externally -- in the handle event session

                // check out the aforementioned solutions today


                // The credits display will be done -- hit the KEY_DEL for going back to the console
                // for issuing further instructions

                // After completing the display of the text in the credits part -- any key pressed
                // gets displayed in the terminal -- better clear the terminal screen after dislaying the credits
            }
            else if(checkBootLvl)
            {
                // pass the input command to the tokenizer -- the tokenizer still needs some more tweaking to be done
                // the file path separator is throwing errors leading to the stoppage of the tokenizing
                cout<<"Will be sending the inpCliStr to the tokenizer\n";
                inpCliStr.clear();
            }
            else
                inpCliStr.clear();
        break;
        case KEY_LEFT:
            inpObj.getxy(txtBoxPosx, txtBoxPosy);

            if(txtBoxPosx == desPromptStr.length())
            {
                if((txtBoxPosx - desPromptStr.length() - 1) == 0)
                {
                    inpObj.gotoxy(--txtBoxPosx, txtBoxPosy);
                    txtBoxPosx = desPromptStr.length();
                }
                break;
            }
            inpObj.gotoxy(--txtBoxPosx, txtBoxPosy);
        break;
        case KEY_RIGHT:
            inpObj.getxy(txtBoxPosx, txtBoxPosy);
            // make a check
            if(((txtBoxPosx == desPromptStr.length()) && inpCliStr.empty()) || (txtBoxPosx == desPromptStr.length() + inpCliStr.length()))
                break;
            inpObj.gotoxy(++txtBoxPosx, txtBoxPosy);
        break;
        case KEY_BACKSPACE:
            int curLength = inpCliStr.length();
            inpObj.getxy(txtBoxPosx, txtBoxPosy);
            if(txtBoxPosx == desPromptStr.length())
                break;
            inpObj.delChar(--txtBoxPosx, txtBoxPosy);
            inpObj.gotoxy(txtBoxPosx, txtBoxPosy);


            if(curPos >= 0 || curPos < inpCliStr.length())
                inpCliStr.erase(curPos, 1);




            if(!inpCliStr.empty())
            {
                clear_to_color(consoleTextBmp, CBLACK);
                inpObj.reset_cursor_pos(desPromptStr.length());

                for(int count = 0; count < curLength; count++)
                    inpObj.writeText(" ");
                inpObj.cursorVisible = false;
                inpObj.reset_cursor_pos(desPromptStr.length());
                inpObj.writeText(const_cast<char *>(inpCliStr.c_str()));
                inpObj.cursorVisible = true;
                inpObj.reset_cursor_pos(txtBoxPosx);

                // enhancements are already listed in the changelog
            }
        break;
    }
}

void _handle_screen_tear(int blitMode)
{
    // some genericity issue is remaining with this one
    // like this function doesn't work properly while called anywhere else

    // check out the way the screen tear was being implemented
    for(int counter = 0; counter < 2; counter++)
    {
        _save_reblit_buffer_state_(blitMode);
        clear_to_color(dBuffer, CBLACK);
        update_screen();
        for(long counter = 0; counter < 9999999; counter++);
        // stretched blit
        stretch_blit(tempStorage, dBuffer, 0, 0, tempStorage->w, tempStorage->h, 0, 0, 2048, 640);
        stretch_blit(tempStorage, dBuffer, 0, 0, tempStorage->w, tempStorage->h, 0, 0, 2048, 800);

        update_screen();

        for(long counter = 0; counter < 9999999; counter++);
        _save_reblit_buffer_state_(blitMode);
        update_screen();
    }
}

// --------------------------------------- bitmap error checker ----------------------------------------------------
bool gfx_error_handler(BITMAP *inpBmp)
{
    if(!inpBmp)
        return false;
    else
        return true;
}/**/
