#include "txtBox.h"

using namespace std;

txtBox::txtBox()
{
    isInit = false;
    cursorVisible = false;
    buffer = NULL;
    txtBMP = NULL;
}

void txtBox::init(int _nWidth, int _nHeight, BITMAP* _txtBMP, FONT* _txtFONT)
{
        if(isInit)
            delBuffer();

    buffer = NULL;

        if(!_txtFONT)
            txtFONT = font;
        else
            txtFONT = _txtFONT;

    txtBMP = _txtBMP;         // Allegro's 'create_bitmap' & 'destroy_bitmap' cannot be called in classes

    // Load the user parameters
    nWidth = _nWidth;
    nHeight = _nHeight;
    fHeight = text_height(txtFONT);
    fWidth = text_length(txtFONT, "D");

    // Offset the origin and set the initial drawing position of the cursor
    xOrigin = yOrigin = dYCur = EDGE_WIDTH;

        if(txtBMP)
        {
            // Load effective image height and width as calculated by 'allocBITMAP()'
            dWidth = txtBMP->w;
            dHeight = txtBMP->h;
        }

    // Set the initial position of the cursor in the buffer
    xCur = yCur = 0;

    // Dynamically allocate space for the buffer
    buffer = new char*[nHeight];
        for(int i=0; i<nHeight; i++)
        {
            buffer[i] = new char[nWidth+1];
            buffer[i][nWidth] = 0x00;
        }

    // Check if both the memory blocks have been allocated properly
        if(buffer && txtBMP)
        {
            isInit = true;
            cls();
        }
        else
            cerr<<"Insufficient memory"<<endl;
}

txtBox::~txtBox()
{
    delBuffer();
    if(txtFONT != font)
        destroy_font(txtFONT);
}

void txtBox::delBuffer()
{
    // Deallocate space
        if(buffer)
        {
                for(int i=0; i<nHeight; i++)
                    delete [] buffer[i];

            delete [] buffer;
        }
}

BITMAP* allocBITMAP(int _nWidth, int _nHeight, int _fWidth, int _fHeight)
{
    // Calculate effective bitmap dimensions for a textbox of size _nWidth x _nHeight
    int dWidth = 2*EDGE_WIDTH + _fWidth * _nWidth;
    int dHeight = 2*EDGE_WIDTH + (_fHeight + LINE_GAP) * (_nHeight-1) + _fHeight;

    BITMAP* txtBMP = create_bitmap(dWidth, dHeight);

    return txtBMP;
}

void txtBox::writeText(char* str)
{
        if(!isInit)
            return;

    // Write the text at the current cursor position
    // The newline on my system in a string is interpreted as '0x0A'
    int i;
        for(i=0; str[i]!='\0'; i++)
            writeChar(str[i]);
}

void txtBox::writeText(char* str, int x, int y)
{
        if(!isInit)
            return;

    // Write text to the postion denoted by the pair 'x' & 'y'
    int i;

    // Write the character to the buffer
        if(x >= 0 && x < nWidth && y >= 0 && y < nHeight)
        {
            xCur = x; yCur = y;
                for(i=0; str[i]!='\0'; i++)
                    writeChar(str[i]);
                    //writeChar((str[i] == 0x0A)?0x0D:str[i]);
        }
}

void txtBox::writeChar(char chr, int x, int y)
{
        if(!isInit)
            return;

    // Write the character to the buffer
        if(x >= 0 && x < nWidth && y >= 0 && y < nHeight)
        {
                if(chr != 0x0D && chr != 0x0A)
                    buffer[y][x] = chr;
        }
}

void txtBox::writeChar(char chr)
{
        if(!isInit)
            return;

    // Write the character into the buffer
    writeChar(chr, xCur, yCur);

    /*
        Update the position of the cursor accordingly i.e. if it is near the right edge
        or the character printed was a newline, move to the start of the next line, otherwise
        increment the abscissa of the cursor
    */
        if(xCur == nWidth-1 || chr == 0x0A) // '\n' = 0x0D 0x0A and  "..\n.." = .. 0x0A ..
        {
            xCur = 0;
            // If the cursor is in the bottom most line, scroll down. The top lines will be lost
                if(yCur == nHeight-1 && nHeight > 1)
                    scrollDown();
                else if(nHeight > 1)
                    yCur++;
        }
        else if(chr != 0x0A)
            xCur++;

    //cout<<(int)chr<<endl;
    // Update the screen
    updateBitmap();
}

void txtBox::scrollDown()
{
        if(!isInit)
            return;

    // Copy all lines to the previous line and replace the last line with spaces
    int i, j;
        for(i=0; i<nHeight-1; i++)
                for(j=0; j<nWidth; j++)
                    buffer[i][j] = buffer[i+1][j];

    // Blank out the last line
        for(i=0; i<nWidth; i++)
            buffer[nHeight-1][i] = 0x20;
}

void txtBox::updateBitmap()
{
        if(!isInit)
            return;

    // Clear the current bitmap
    clear_to_color(txtBMP, cBLACK);

    int i;
    //cout<<nHeight<<endl;
        for(i=0; i<nHeight; i++, dYCur+=(fHeight+LINE_GAP))
            textprintf_ex(txtBMP, txtFONT, EDGE_WIDTH, dYCur, txtColor, TRANSPARENT, "%s", buffer[i]);//, cout<<buffer[i]<<endl;

    dYCur = EDGE_WIDTH;

        // Draw the cursor depending on the control variable
        if(cursorVisible)
        {
            vline(txtBMP, xOrigin+xCur*fWidth, yOrigin+(fHeight+LINE_GAP)*yCur-3, \
            yOrigin+(fHeight+LINE_GAP)*yCur+CURSOR_H, curColor);
        }
}

void txtBox::gotoxy(int x, int y)
{
        if(x >= 0 && x < nWidth && y >= 0 && y < nHeight)
        {
            xCur=x;
            yCur=y;
        }
        else if(x == -1 && y > 0)
        {
            xCur = nWidth;
            yCur--;
        }
        else if(x >= nWidth && y < nHeight-1)
        {
            xCur = 0;
            yCur++;
        }
    updateBitmap();
}

void txtBox::getxy(int& x, int& y)
{
    x = xCur;
    y = yCur;
}

void txtBox::delChar(int x, int y)
{
        if(x >= 0 && x < nWidth && y >= 0 && y < nHeight)
                buffer[y][x] = 0x20;

    updateBitmap();
}

void txtBox::cls()
{
        if(!isInit)
            return;
    // Clear the screen by blanking it out with spaces
    int i,j;

        for(i=0; i<nHeight; i++)
                for(j=0; j<nWidth; j++)
                    buffer[i][j] = 0x20;

    xCur = yCur = 0;
    dYCur = EDGE_WIDTH;
    updateBitmap();
}

// war10ck custom function
void txtBox::reset_cursor_pos(int inpPos)
{
    if(!isInit)
        return;

    xCur = inpPos;
    dYCur = EDGE_WIDTH;

    // Draw the cursor depending on the control variable
    if(cursorVisible)
    {
        vline(txtBMP, xOrigin+xCur*fWidth, yOrigin+(fHeight+LINE_GAP)*yCur-3, \
        yOrigin+(fHeight+LINE_GAP)*yCur+CURSOR_H, curColor);
    }
}
