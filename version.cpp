#include <stdio.h>
#include <cv.h>
#include "IntroConfig.h"

void ver::printVersion()
{
    // fprintf(stdout, "Version %d.%d\n",
    //         Intro_VERSION_MAJOR,
    //         Intro_VERSION_MINOR);
    printf("Scratch Version %d.%d\n", Intro_VERSION_MAJOR, Intro_VERSION_MINOR);

    return; 
}


int main(void)
{
    ver::printVersion();
    //for fun
    return 0;
}
