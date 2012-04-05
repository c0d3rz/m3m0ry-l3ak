#ifndef TXTBOX_H_INCLUDED
#define TXTBOX_H_INCLUDED

#include <iostream>
#include <climits>

#include <allegro.h>

#define TRANSPARENT -1              // Transparency of text written on the BITMAP
#define EDGE_WIDTH 5                // Width of the border (px)- the invisible "box" around the text area
#define LINE_GAP 5                  // Gap between successive lines in px
#define CURSOR_H 8                  // Height of cursor in px

// Default color definitions
#define cWHITE makecol(255,255,255)
#define cBLACK makecol(0,0,0)
#define cBROWN makecol(51,0,0)
#define cGREEN makecol(0,255,0)
class txtBox
{
    private:
        // Check if object is properly initialized
        bool isInit;

        // BITMAP buffer for the entire textbox
        BITMAP* txtBMP;

        // FONT to be used by the textbox
        FONT* txtFONT;

        // Buffer to store the text (2D dynamically allocated array)
        char** buffer;

        // Shifted origin
        int xOrigin;
        int yOrigin;

        // Current position of cursor in the buffer
        int xCur;
        int yCur;

        // Stores the ordinate of each line to be drawn on the screen
        int dYCur;

        // Number of characters along the width and height
        int nWidth;
        int nHeight;

        // Dimensions of the bitmap
        int dWidth;
        int dHeight;

        // Height and width of the font (assumed to be a fixed width font)
        int fWidth;
        int fHeight;

        // Shift all lines up by one
        void scrollDown();

        // Deallocate the buffer
        void delBuffer();

        // Function to update the bitmap
        void updateBitmap();

    public:
        // Toggle for cursor visibility
        bool cursorVisible;

        // Color of text
        int txtColor;

        // Color of cursor
        int curColor;

        txtBox();
        ~txtBox();

        void init(int _nWidth, int _nHeight, BITMAP* _txtBMP, FONT* _txtFONT);
        void gotoxy(int x, int y);
        void writeText(char* str);
        void writeText(char* str, int x, int y);
        void writeChar(char chr, int x, int y);
        void writeChar(char chr);
        void cls();
        void getxy(int& x, int& y);
        void delChar(int x, int y);

        // war10ck custom code
        void reset_cursor_pos(int inpPos);
};

// To externally allocate memory for the BITMAP - THIS CANNOT BE DONE IN A CLASS >_<
BITMAP* allocBITMAP(int _nWidth, int _nHeight, int _fWidth, int _fHeight);

#endif // TXTBOX_H_INCLUDED
