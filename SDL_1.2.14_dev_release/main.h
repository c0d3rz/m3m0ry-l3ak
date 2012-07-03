#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#ifdef __cplusplus
    #include <iostream>
    #include <cstdlib>
#else
    #include <stdio.h>
    #include <stdlib.h>
#endif

#ifdef __APPLE__
    #include <SDL/SDL.h>
#else
    #include <SDL.h>
#endif

#endif // MAIN_H_INCLUDED
