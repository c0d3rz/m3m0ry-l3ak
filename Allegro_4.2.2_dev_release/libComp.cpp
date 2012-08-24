#include "libComp.h"

using namespace std;    // just for the debugging purpose

void libComponents::display_time()
{
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    // pass a string to a display function in libGraphics module
    string ascTime = asctime(timeinfo);

    // checking the printing of the string
    _display_time_(ascTime);
    // time display working fine -- genericize the function now
}
