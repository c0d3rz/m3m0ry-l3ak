#ifndef LIBCOMP_H_INCLUDED
#define LIBCOMP_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>

#include "libGraphics.h"

class libComponents
{
    private:
        time_t rawtime;
        struct tm *timeinfo;

    public:
        void display_time();    // displays the system time
};

#endif // LIBCOMP_H_INCLUDED
