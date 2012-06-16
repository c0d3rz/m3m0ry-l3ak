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
BITMAP *queryBoxImg;    // the alert box query user
BITMAP *alertBoxImg;    // the alert box warning for the user
BITMAP *objImg;     // the objective display image
BITMAP *acPerfImg;     // action performed user -- previous action
BITMAP *warningmsgImg; // the warning message
BITMAP *selectImg;  // the menu selection image
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
    selectImg = create_bitmap((text_length(font, "D") + 4), (text_height(font) + 4));

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
    queryBoxImg = (BITMAP *)gfxDat[QUERYBOX_BMP].dat;
    alertBoxImg = (BITMAP *)gfxDat[ALERT_BOX_BMP].dat;
    objImg = (BITMAP *)gfxDat[L0S_BMP].dat;
    acPerfImg = (BITMAP *)gfxDat[UN_PW_QUERY_BMP].dat;
    warningmsgImg = (BITMAP *)gfxDat[WARNINGMSG_BMP].dat;

    // error checking part
    if(gfx_error_handler(bootImg) && gfx_error_handler(splashImg) && gfxDat && gfx_error_handler(projNameImg) && gfx_error_handler(consoleImg)\
    && gfx_error_handler(creditImg) && gfx_error_handler(secTempStorage) && gfx_error_handler(loginBckImg) && gfx_error_handler(upQueryImg)\
    && gfx_error_handler(mainBgImg) && gfx_error_handler(webBrowserImg) && gfx_error_handler(prevDisplayImg) &&\
    gfx_error_handler(queryBoxImg) && gfx_error_handler(alertBoxImg) && gfx_error_handler(objImg) &&\
    gfx_error_handler(acPerfImg) && gfx_error_handler(warningmsgImg) && gfx_error_handler(selectImg));
    else
    {
        allegro_message("Error loading game resource files in memory");
        exit(0);
    }
}

void destroy_instances()
{
    destroy_bitmap(selectImg);
    destroy_bitmap(dBuffer);
    destroy_bitmap(tempStorage);
    destroy_bitmap(secTempStorage);

    unload_datafile(gfxDat);    // SegFault removed -- make an update as soon as possible
    // a big hurdle is removed -- more tweakings require to be done

    // on a side note for the tweakings that might be done -- chapapapa, I have forgotten
    // what they were
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

    // clearing the dBuffer
    clear_dBuffer();
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

        int allocWidth = 76, allocHeight = 27;
        int txtBoxPosx, txtBoxPosy; // for the position of the cursor

        /*
            Text Printing working with proper KEY_ENTER handling and corr text
            newline printing. Now to make it generic.--> made this partgeneric -- check out the handle_event function

            That is an internal function that will be handling the events -- now to remove the redundancies
            Also the changelog needs to be updated.

            A bug has been found at the moment -- when the text entering reaches the end of the text
            bitmap the text printing gives a seg fault. Have to check that part

            Also need to try loading vector graphics in allegro.
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

                    // bug removed - bug existed at insertion of characters when cursor reaches
                    // the last border of the consoleText Image

                    // Solution : cli.length() < allocWidth - LINE_GAP

                    // prepare formula for allocWidth and allocHeight calculation
                    // moving on to the creation of the next part of the level Zero cutscene display
                    if((txtBoxPosx - _PROMPT.length() == 0) && (!cli.empty()) && (cli.length() < (allocWidth - LINE_GAP - 2)))
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
                    else if((txtBoxPosx - _PROMPT.length() > 0) && (txtBoxPosx - _PROMPT.length() < cli.length()) && (cli.length() < (allocWidth - LINE_GAP - 2))) // if the position of the cursor is inside the command that has been input
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
                    else if(cli.length() < (allocWidth - LINE_GAP - 2))
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
        clear_dBuffer();
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

void display_intro(int mode, string inpEpName, string inpUserName, FMOD::System*& inpSystem, FMOD_RESULT &inpResult, FMOD::Sound*& inpBgSfxState, FMOD::Sound*& inpExSfxState, FMOD::Channel*& inpBgChannel, FMOD::Channel*& inpExChannel)  // I might be needing the object to be passed
{
    // the mode will be for each and every mission rather than double checking mission and the level

    switch(mode)
    {
        case INTRO: // Level Zero
            remove_keyboard();
            clear_to_color(screen, CBLACK);
            blit_on_dBuffer(mainBgImg, 0, 0, OPAQ);

            play_sfx(inpSystem, inpResult, inpBgSfxState, inpBgChannel);

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

            lvlzIntroTxt.push_back("n@$h> ");   // removing unnecessary comments


            // display the first part of the cutscene text
            _seq_display_(lvlzIntroTxt, consoleImg, 76, 27, 10, 40, 100, 100, true, CGREEN, LINEBYLN);
            update_screen();

            // display and blit on the web-browser -- done
            blit_on_dBuffer(webBrowserImg, 250, 250, OPAQ);

            // write addr of the website that will be showing the news to the user
            textout_ex(webBrowserImg, font, "www.undergroundnews.com", 10, 8, CGREEN, -1);

            // rinse and repeat
            vector<string> brwDisplayVec;   // browser display vector
            brwDisplayVec.push_back("Breaking News\n");
            brwDisplayVec.push_back("----------------------------------------\n\n");
            brwDisplayVec.push_back("Revered Head of Security of Internic was today arrested");
            brwDisplayVec.push_back("on multiple accounts of espionage and revealing of");
            brwDisplayVec.push_back("information to rival companies for extra money. Apart from");
            brwDisplayVec.push_back("that his accomplice was the head of Management of Secure");
            brwDisplayVec.push_back("Digital Corp which had tried to sneak into the operations");
            brwDisplayVec.push_back("as well as used the information to play the companies' resources");

            // key event will be dispayed kat the top left corner of the screen -- done


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

            // browser display
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
            // the name of the user will be displayed in every cut scene display

            // screenDisturbance function will be handled later
            // trying to tweak the sound library


            _seq_display_(brDisplayVec, webBrowserImg, 76, 27, 10, 40, 150, 150, false, CGREEN, LINEBYLN);
            // allow the user to carry on with the cut scene display

            install_keyboard();
            textout_ex(dBuffer, font, "Press a key to continue", 10, 10, CGREEN, -1);
            update_screen();
            readkey();
            textout_ex(dBuffer, font, "Press a key to continue", 10, 10, CBLACK, -1);
            play_sfx(inpSystem, inpResult, inpExSfxState, inpExChannel);
            for(int counter = 0; counter != 5; counter++)
                for(long counter = 0; counter < 9999999L; counter++);
            update_screen();    // also need to change the bgCutScene music -- that sounds sloppy
            remove_keyboard();

            //_handle_screen_tear(FULLBLT);   // this is where the screen tear is being handled
            // now check out the fullBlt state in that save_screen_state

            // will be using the secTempStorage function
            _save_reblit_buffer_state_(FULLSAV);
            //play_sfx(inpSystem, inpResult, inpExSfxState, inpExChannel);
            _distort_frame_(dBuffer, secTempStorage, 0, 0, 45.5); // the implementation -- distort_frame -- screen disturbance
            // need to display the secTempStorage on the screen -- this is where the second sfx will
            // be played
            blit_on_dBuffer(secTempStorage, 0, 0, OPAQ);
            update_screen();
            stop_play_sfx(inpExChannel, inpResult);
            inpSystem->update();

            //for(long counter = 0; counter < 999999999L; counter++);
            for(long counter = 0; counter < 9999999L; counter++);
            _save_reblit_buffer_state_(FULLBLT);
            update_screen();
            for(long counter = 0; counter < 999999999L; counter++);
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

            // have to check out the issues


            // display the terminal image and display some text
            // after that create the alertbox window
            clear_dBuffer();
            blit_on_dBuffer(loginBckImg, 0, 0, OPAQ);
            blit_on_dBuffer(consoleImg, 100, 100, OPAQ);

            // populate the vector that will be displaying the next display
            // for the terminal

            vector<string> termDisplayLvlz;
            termDisplayLvlz.push_back("lCooper@internic> w");
            termDisplayLvlz.push_back("10:53:46 up 3 days, 12:38,  5 users,  load average: 0.00, 0.00, 0.00");
            termDisplayLvlz.push_back("USER   TTY     FROM             LOGIN@   IDLE   JCPU     PCPU WHAT");
            termDisplayLvlz.push_back("andrew tty7     :0               00:14   13:17  21.55s  0.16s gnome-session");
            termDisplayLvlz.push_back("jack   pts/0    :0               00:10   13:20  21.32s  0.19s gnome-session");
            termDisplayLvlz.push_back("lCooper@internic> snort -A full -c /etc/snort/snort.conf");
            termDisplayLvlz.push_back("Log directory = /var/log/snort");
            termDisplayLvlz.push_back("Frag3 global config:");
            termDisplayLvlz.push_back("    Max frags: 65536");
            termDisplayLvlz.push_back("    Fragment memory cap: 4194304 bytes");
            termDisplayLvlz.push_back("Frag3 engine config:");
            termDisplayLvlz.push_back("    Target-based policy: FIRST");
            termDisplayLvlz.push_back("    Fragment timeout: 60 seconds");
            termDisplayLvlz.push_back("    Fragment min_ttl:   1");
            termDisplayLvlz.push_back("    Fragment Problems: 1");
            termDisplayLvlz.push_back("    Overlap Limit:     10");
            termDisplayLvlz.push_back("    Min fragment Length:     0");
            termDisplayLvlz.push_back("Stream5 global config:");
            termDisplayLvlz.push_back("    Track TCP sessions: ACTIVE");
            termDisplayLvlz.push_back("    Max TCP sessions: 8192");
            termDisplayLvlz.push_back("    Memcap (for reassembly packet storage): 8388608");
            termDisplayLvlz.push_back("    Track UDP sessions: INACTIVE");
            termDisplayLvlz.push_back("    Track ICMP sessions: INACTIVE");
            termDisplayLvlz.push_back("    Log info if session memory consumption exceeds 1048576");
            termDisplayLvlz.push_back("Stream5 TCP Policy config:");
            termDisplayLvlz.push_back("    Reassembly Policy: FIRST");
            termDisplayLvlz.push_back("    Timeout: 30 seconds");
            termDisplayLvlz.push_back("    Min ttl:  1");
            termDisplayLvlz.push_back("    Maximum number of bytes to queue per session: 1048576");
            termDisplayLvlz.push_back("    Maximum number of segs to queue per session: 2621");
            termDisplayLvlz.push_back("    Reassembly Ports:");
            termDisplayLvlz.push_back("      21 client (Footprint) ");
            termDisplayLvlz.push_back("      23 client (Footprint) ");
            termDisplayLvlz.push_back("      25 client (Footprint) ");
            termDisplayLvlz.push_back("      42 client (Footprint) ");
            termDisplayLvlz.push_back("      53 client (Footprint) ");
            termDisplayLvlz.push_back("      80 client (Footprint) ");
            termDisplayLvlz.push_back("      110 client (Footprint) ");
            termDisplayLvlz.push_back("      111 client (Footprint) ");
            termDisplayLvlz.push_back("      135 client (Footprint) ");
            termDisplayLvlz.push_back("      136 client (Footprint) ");
            termDisplayLvlz.push_back("      137 client (Footprint) ");
            termDisplayLvlz.push_back("      139 client (Footprint) ");
            termDisplayLvlz.push_back("      143 client (Footprint) ");
            termDisplayLvlz.push_back("      445 client (Footprint) ");
            termDisplayLvlz.push_back("      513 client (Footprint) ");
            termDisplayLvlz.push_back("      514 client (Footprint) ");
            termDisplayLvlz.push_back("      1433 client (Footprint) ");
            termDisplayLvlz.push_back("      1433 client (Footprint) ");
            termDisplayLvlz.push_back("      2401 client (Footprint) ");
            termDisplayLvlz.push_back("      3306 client (Footprint) ");
            termDisplayLvlz.push_back("HttpInspect Config:");
            termDisplayLvlz.push_back("    GLOBAL CONFIG");
            termDisplayLvlz.push_back("      Max Pipeline Requests:    0");
            termDisplayLvlz.push_back("      Inspection Type:          STATELESS");
            termDisplayLvlz.push_back("      Detect Proxy Usage:       NO");
            termDisplayLvlz.push_back("      IIS Unicode Map Filename: /etc/snort/unicode.map");
            termDisplayLvlz.push_back("      IIS Unicode Map Codepage: 1252");
            termDisplayLvlz.push_back("    DEFAULT SERVER CONFIG:");
            termDisplayLvlz.push_back("      Server profile: All");
            termDisplayLvlz.push_back("      Ports: 80 8080 8180 ");
            termDisplayLvlz.push_back("      Server Flow Depth: 300");
            termDisplayLvlz.push_back("      Client Flow Depth: 300");
            termDisplayLvlz.push_back("      Max Chunk Length: 500000");
            termDisplayLvlz.push_back("      Max Header Field Length: 0");
            termDisplayLvlz.push_back("      Max Number Header Fields: 0");
            termDisplayLvlz.push_back("      Inspect Pipeline Requests: YES");
            termDisplayLvlz.push_back("      URI Discovery Strict Mode: NO");
            termDisplayLvlz.push_back("      Allow Proxy Usage: NO");
            termDisplayLvlz.push_back("      Disable Alerting: NO");
            termDisplayLvlz.push_back("      Oversize Dir Length: 500");
            termDisplayLvlz.push_back("      Only inspect URI: NO");
            termDisplayLvlz.push_back("      Normalize HTTP Headers: NO");
            termDisplayLvlz.push_back("      Normalize HTTP Cookies: NO");
            termDisplayLvlz.push_back("      Ascii: YES alert: NO");
            termDisplayLvlz.push_back("      Double Decoding: YES alert: YES");
            termDisplayLvlz.push_back("      %U Encoding: YES alert: YES");
            termDisplayLvlz.push_back("      Bare Byte: YES alert: YES");
            termDisplayLvlz.push_back("      Base36: OFF");
            termDisplayLvlz.push_back("      UTF 8: OFF");
            termDisplayLvlz.push_back("      IIS Unicode: YES alert: YES");
            termDisplayLvlz.push_back("      Multiple Slash: YES alert: NO");
            termDisplayLvlz.push_back("      IIS Backslash: YES alert: NO");
            termDisplayLvlz.push_back("      Directory Traversal: YES alert: NO");
            termDisplayLvlz.push_back("      Web Root Traversal: YES alert: YES");
            termDisplayLvlz.push_back("      Apache WhiteSpace: YES alert: NO");
            termDisplayLvlz.push_back("      IIS Delimiter: YES alert: NO");
            termDisplayLvlz.push_back("      IIS Unicode Map: GLOBAL IIS UNICODE MAP CONFIG");
            termDisplayLvlz.push_back("      Non-RFC Compliant Characters: NONE");
            termDisplayLvlz.push_back("      Whitespace Characters: 0x09 0x0b 0x0c 0x0d ");
            termDisplayLvlz.push_back("rpc_decode arguments:");
            termDisplayLvlz.push_back("    Ports to decode RPC on: 111 32771 ");
            termDisplayLvlz.push_back("    alert_fragments: INACTIVE");
            termDisplayLvlz.push_back("    alert_large_fragments: ACTIVE");
            termDisplayLvlz.push_back("    alert_incomplete: ACTIVE");
            termDisplayLvlz.push_back("    alert_multiple_requests: ACTIVE");
            termDisplayLvlz.push_back("Portscan Detection Config:");
            termDisplayLvlz.push_back("    Detect Protocols:  TCP UDP ICMP IP");
            termDisplayLvlz.push_back("    Detect Scan Type:  portscan portsweep decoy_portscan distributed_portscan");
            termDisplayLvlz.push_back("    Sensitivity Level: Low");
            termDisplayLvlz.push_back("    Memcap (in bytes): 10000000");
            termDisplayLvlz.push_back("    Number of Nodes:   36900");
            termDisplayLvlz.push_back("FTPTelnet Config:");
            termDisplayLvlz.push_back("    GLOBAL CONFIG");
            termDisplayLvlz.push_back("      Inspection Type: stateful");
            termDisplayLvlz.push_back("      Check for Encrypted Traffic: YES alert: YES");
            termDisplayLvlz.push_back("      Continue to check encrypted data: NO");
            termDisplayLvlz.push_back("    TELNET CONFIG:");
            termDisplayLvlz.push_back("      Ports: 23 ");
            termDisplayLvlz.push_back("      Are You There Threshold: 200");
            termDisplayLvlz.push_back("      Normalize: YES");
            termDisplayLvlz.push_back("      Detect Anomalies: NO");
            termDisplayLvlz.push_back("    FTP CONFIG:");
            termDisplayLvlz.push_back("      FTP Server: default");
            termDisplayLvlz.push_back("        Ports: 21 ");
            termDisplayLvlz.push_back("        Check for Telnet Cmds: YES alert: YES");
            termDisplayLvlz.push_back("        Ignore Telnet Cmd Operations: OFF");
            termDisplayLvlz.push_back("        Identify open data channels: YES");

            termDisplayLvlz.push_back("Server side data is trusted\n");
            termDisplayLvlz.push_back("+++++++++++++++++++++++++++++++++++++++++++++++++++");
            termDisplayLvlz.push_back("lCooper@internic> ");
            // current work to be done
            // 1. add the queryBox to the imageData file -- use the c2 compression

            _seq_display_(termDisplayLvlz, consoleImg, 76, 27, 10, 30, 100, 100, true, CGREEN, LINEBYLN);
            update_screen();

            // display the queryBoxImg -- show that a confirmation box appeared asking for some access
            // to come database/network -- the ip was a bit peculiar -- though seemed legit

            // clear the save_state storer
            clear_to_color(secTempStorage, CBLACK); // secTempStorage will be storing the dBuffer state
            // save the screen state
            _save_reblit_buffer_state_(ALERTCUTSCSAV);  // reblit this state -- rem_inportant

            blit_on_dBuffer(queryBoxImg, 250, 150, OPAQ);   // save the state of the screen in one
            // of the buffers other than dBuffer


            vector<string>dispQuerycsc; // display the query of the cutscene
            dispQuerycsc.push_back("hostname: subRoot on NixBox84");
            dispQuerycsc.push_back("user \"subRoot\" on hub node 48 is requesting access");
            dispQuerycsc.push_back("destination hub : DB82G66 on node 48");
            dispQuerycsc.push_back("\n         Press Y/N for accept/decline             ");

            _seq_display_(dispQuerycsc, queryBoxImg, 45, 10, 10, 30, 250, 150, false, CGREEN, LINEBYLN);

            // This is where the user will be told that "Hadn't you given access, hadn't you had pressed
            // y, this wouldn't have occured" -- for this another bitmap needs to be used. This bitmap
            // will also be used for displaying the objectives of the level the user is in. So the objective
            // screen will also be used for displaying some events that are bound to occur
            // displaying the next part of the cutscene

            // showing the user what had been done before

            // save the screen state before blitting the objective image -- actually this is not the
            // the objective that will be displayed
            clear_to_color(tempStorage, CBLACK);    // for the distort frame that will be done later
            // this distort_frame will be implemented after the alert box gets the go forward

            // save the display state
            _save_reblit_buffer_state_(FULLSAV);

            // blitting the image -- objective screen -- This objective screen has to be removed
            // from this part -- too big to fit the small amount of text to be displayed
            // might be using the previous username query image for this
            blit_on_dBuffer(acPerfImg, 550, 250, OPAQ);    // removing the objective image
            // also have to tweak the save_reblit state code -- not required -- that is a FULLSAV
            update_screen();

            // the text to be displayed
            vector<string> actionPerf;

            // pushing in the text data
            actionPerf.push_back("This was the moment that changed everything");
            actionPerf.push_back("in your life. Had you performed a detailed");
            actionPerf.push_back("network scanning on that port that had asked");
            actionPerf.push_back("for the access you might not have suffered");

            actionPerf.push_back("\n\n");   // 1 add auto mode
            actionPerf.push_back("You had given the access to that node thereby installing a");
            actionPerf.push_back("backdoor to your system. This led to the final mishap");

            _seq_display_(actionPerf, acPerfImg, 47, 14, 7, 7, 550, 250, false, CGREEN, LINEBYLN);
            // now to move on to the next part of the coding
            update_screen();

            install_keyboard();
            textout_ex(dBuffer, font, "Press a key to continue", 10, 10, CGREEN, -1);
            update_screen();
            readkey();

            // create the vector that will be displaying the cutscene display
            textout_ex(dBuffer, font, "Press a key to continue", 10, 10, CBLACK, -1);
            update_screen();
            remove_keyboard();

            // reblitting the previous state to the user -- to proceed with the cutscene display
            _save_reblit_buffer_state_(FULLBLT);    // so this is working fine -- now to write in the
            // objective image -- "If you hadn't given access to that user" and after that display the
            // warning message to the user/game player
            update_screen();

            install_keyboard();
            while(!key[KEY_Y]);
            _save_reblit_buffer_state_(ALERTCUTSCBLT);
            remove_keyboard();  // so this part is working -- next display the distort frame along with
            // the playing of the distort_frame gfx and then display m3m0ry-l3ak

            // play the sound
            play_sfx(inpSystem, inpResult, inpExSfxState, inpExChannel);

            // clearing the save_buffers incase any of them will be required
            clear_to_color(tempStorage, CBLACK);
            clear_to_color(secTempStorage, CBLACK);


            // save the screen state
            _save_reblit_buffer_state_(FULLSAV);

            // call to distort the frame
            _distort_frame_(dBuffer, secTempStorage, 0, 0, 18.0);
            blit_on_dBuffer(secTempStorage, 0, 0, OPAQ);
            update_screen();

            // insert another small delay here
            for(long counter = 0; counter < 9999999L; counter++);
            _save_reblit_buffer_state_(FULLBLT);
            update_screen();

            // creating the time dalay
            for(int cpuWaitTime = 0; cpuWaitTime != 1; ++cpuWaitTime)
                for(long counter = 0; counter < 99999999L; counter++);
            // the sfx playback is working -- hope everything goes alright and I can submit my
            // 250 th tweet

            // clear the buffer states once again since this time the distort_sfx will be played
            // fully
            clear_to_color(secTempStorage, CBLACK);


            _distort_frame_(dBuffer, secTempStorage, 0, 0, 90.0);
            blit_on_dBuffer(secTempStorage, 0, 0, OPAQ);
            update_screen();

            for(long counter = 0; counter < 9999999L; counter++);
            _save_reblit_buffer_state_(FULLBLT);
            update_screen();

            for(int waitTime = 0; waitTime < 2; waitTime++)
                for(long counter = 0; counter < 99999999L; counter++);

            // again repeating the above process
            clear_to_color(secTempStorage, CBLACK);
            _distort_frame_(dBuffer, secTempStorage, 0, 0, 45.5);
            blit_on_dBuffer(secTempStorage, 0, 0, OPAQ);
            update_screen();

            for(long counter = 0; counter < 9999999L; counter++);
            _save_reblit_buffer_state_(FULLBLT);
            update_screen();
            for(long counter = 0; counter < 9999999L; counter++);   // distort work completed
            // now to show the warning message

            stop_play_sfx(inpExChannel, inpResult);
            inpSystem->update();

            // some temp variables that will be required for the blitting
            int randPosX = rand();
            int randPosY = rand();
            int randDiv = rand();
            int randAdd = rand();

            randDiv = rand() % 563;
            randAdd = rand() % 422;
            // display the warning messages -- this part needs to be tweaked a bit
            // might have to use the rand() function
            for(int blitCounter = 1; blitCounter < 250; ++blitCounter)
            {
                randPosX = rand() % randDiv + randAdd;  // let's make the magic numbers embedded here rand()
                randPosY = rand() % randDiv + randAdd;  // I need some more

                blit_on_dBuffer(warningmsgImg, randPosX, randPosY, OPAQ);
                // also need other things to be displayed -- some extra things -- but this will
                // be done while moving/creating the game play -- for now -- this is just fine
                update_screen();
            } // bug resolved -- remainder reduced to zero -- floating point exception

            // let's do a fade out -- need some delay before performing the fade out
            for(int numCounter = 0; numCounter < 100; numCounter++)   // hope this is apt
                for(long counter = 0; counter < 9999999L; counter++);   // some delay inserted -- checking

            // first save the image on the secTempStorage dBuffer storage
            blit(dBuffer, secTempStorage, 0, 0, 0, 0,  dBuffer->w, dBuffer->h);

            // clear the dBuffer now
            clear_dBuffer();

            // save the state in the SPLASHSAV mode
            _save_reblit_buffer_state_(SPLASHSAV);
            _fade_out_(secTempStorage, 0, 0, 64);

            update_screen();    // update the screen -- for the final blitting part

            // display present condition and the objectives before the main background is setup
            vector<string> presentScene;
            presentScene.push_back("Present Scenario:");
            presentScene.push_back("You were framed for selling new designs and secure information");
            presentScene.push_back("to the rival companies, multiple charges of digital espionage");
            presentScene.push_back("and also leading an underground operation named m3m0ry-l3ak");
            presentScene.push_back("\n\nA harsh 8 years in the prison, that's what you had to endure.");
            presentScene.push_back("Now you are outside, free and the only thing that drives you is");
            presentScene.push_back("TO FIND THE PERSON WHO WAS BEHIND ALL OF IT");

            presentScene.push_back("\n\n\nPress any key to continue");

            // call the _seq_display_ function to display the aforementioned
            _seq_display_(presentScene, dBuffer, 100, 100, 150, 150, 150, 150, false, CGREEN, CHBYCH);

            // objectives will be displayed once the game play starts -- first the player has to
            // select the sysConfig that is going to be used as a base for the game. Later on
            // the upgrades can be applied.

            // AI to be written in Python -- will be trying to do that

            // wait for the user keypress
            install_keyboard();
            readkey();  // show the user to press a key
            update_screen();

            stop_play_sfx(inpBgChannel, inpResult);   // this will be stopping the bgMusic for the cutsc
            //release_channel(inpSystem, inpResult, inpChannel); -- deprecated function call
            // not required any more

            // Here I will be passing for the moment two channels and two sounds
            // one will be the master sound, the specialSfx. After that I need to
            // return ctrl to the calling function

            // gfx issue to be resolved:
            // 1. display the "Warning" part to the user
            // 2. properly playSound in the background
            inpSystem->update();    // after this return control back to the calling function

            // return control to the calling function
        break;
    }
}

void clear_dBuffer()
{
    clear_to_color(dBuffer, CBLACK);
}

void set_gfx_background()
{
    blit_on_dBuffer(mainBgImg, 0, 0, OPAQ);
    update_screen();
}

void display_cfg_units(int inpMode, string& inpCpuName, int& inpOpFreq, string& inpNicCardName, int& inpNicCapability, long& inpRamCapac, int& inpModTxRate, long& inpAccBal)
{
    if(inpMode == GET) // get from the user
    {
        // set up the gfx -- check if sound will be required for the same
        // create the selection bitmap -- selection image created and working properly
        // also need to have the accBal value in here -- the accBal needs to be transferred
        // by reference - trying -- if it comes out -- no error -- this is working fine
        // good for me -- no more pain in the ass
        // right now just passing some values -- testing mode

        // Question -- Should I do it in a function called market -- like sep markets for each
        // component -- that should work out
        // have to work on that part -- the showing of the additional info when the selectImg has been
        // moved to the particular CPU name
        inpCpuName = "warCPU v1.0";
        inpOpFreq = 31; // that is 31 Hz -- rem, make it a double var

        inpNicCardName = "BCM43xx";
        inpNicCapability = 32;    // just a dummy text

        inpRamCapac = 4294967296L;  // 4GB of RAM allocated for DUMMY!!!!!
        inpModTxRate = 16;  // This would be mbit/sec notation

        // print the same in the calling function -- calling function this part is working fine
        cout<<--inpAccBal<<endl;    // This is working fine

        // uploading in git
    }
    else if(inpMode == DISP); // display to the user the current chosen configuration

    // Now here we will be facing a problem
    // Problem : Transfer different types of vars from called func
    // and read and transfer different types of vars from calling function

    // check out solution for the same -- might have to use some public variables
    // or a friend function
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

        case ALERTCUTSCSAV:
            blit(dBuffer, secTempStorage, 250, 150, 0, 0, queryBoxImg->w, queryBoxImg->h);
        break;

        case ALERTCUTSCBLT:
            blit(secTempStorage, dBuffer, 0, 0, 250, 150, queryBoxImg->w, queryBoxImg->h);
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

void _distort_frame_(BITMAP* src, BITMAP* dst, int t, int type, float inpAmpli) // some changes need to be done
{
    // here the desination should be created when the source has been passed
    // the return type of the function should be changed to BITMAP *

    // destroy the returned bitmap after the use has completed to free the memory taken up by that
    // next issue to be resolved -- this is something that I should have completed a long time before
    // Also both the dumps need to updated

    // will have to update the dumps after compiling the same in another system

    // have to add the amplitude as an input parameter
    // plus I will have to change the music data into a data file

	ASSERT(source != dest);
	ASSERT(source != NULL && dest != NULL);
	ASSERT(source->w == dest->w && source->h == dest->h);
	ASSERT(type = 0 || type == 1 || type == 3);

	// Some hard-coded distortion parameters
	float A = inpAmpli;		// Amplitude
	float F = 0.1;		// Frequency
	float S = 0.1;		// Time scaling
	float C = 1.0;		// Compression (only used for vertical distortion)

	// Get pointers to raw bitmap data
	int* srcdata = (int*)src->line[0];
	int* dstdata = (int*)dst->line[0];

	int width = src->w;
	int height = src->h;

	// For each line...
	for(int y = 0; y < height; y++)
	{
		// Calculate the distortion offset for this line
		int offset = A * sinf(F * y + S * t);

		int src_x = 0;	// new x position
		int src_y = y;	// new y position

		if(type == 0)
			src_x = offset;
		else if(type == 1)
			src_x = (y % 2)? offset : -offset;
		else if(type == 2)
			src_y = y * C + offset;

		// Wrap the y offset correctly - e.g., -1 should become height-1
		src_y = (src_y + height) % height;

		// Copy the line into the destination with translation
		for(int x = 0; x < width; x++)
		{
			// Also need to wrap the x offset
			src_x = (src_x + width) % width;
			dstdata[y * width + x] = srcdata[src_y * width + src_x];
			src_x++;
		}
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
