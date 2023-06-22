#include "timer.h"

// constructor
timer::timer()
{
    // initialize variables
    startTicks = 0;
    started = false;
}

// destructor
timer::~timer()
{
    // no action needed
}

void timer::start()
{
    // start timer
    started = true;

    // get current clock time
    startTicks = SDL_GetTicks();
}

void timer::stop()
{
    // stop timer
    started = false;

	// clear tick variables
	startTicks = 0;
}

int timer::getTicks()
{
	// actual timer time
	int time = 0;

    // if timer running
    if(started)
    {
        // current time - start time
        time = SDL_GetTicks() - startTicks;
    }

    return time;
}