#include "timer.h"

// constructor
Timer::Timer()
{
    // initialize variables
    startTicks = 0;
    pausedTicks = 0;

    started = false;
    paused = false;
}

// destructor
Timer::~Timer()
{
    // no action needed
}

void Timer::start()
{
    // start timer
    started = true;

    paused = false;

    // get current clock time
    startTicks = SDL_GetTicks();
    pausedTicks = 0;
}

void Timer::stop()
{
    // stop timer
    started = false;

    paused = false;

	// clear tick variables
	startTicks = 0;
    pausedTicks = 0;
}

void Timer::pause()
{
    // if timer is running and isn't already paused
    if(started && !paused) {
        // pause timer
        paused = true;

        // calculate paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
		startTicks = 0;
    }
}

void Timer::unpause()
{
    // if the timer is running and paused
    if(started && paused) {
        // unpause timer
        paused = false;

        // reset starting ticks
        startTicks = SDL_GetTicks() - pausedTicks;

        // reset paused ticks
        pausedTicks = 0;
    }
}

int Timer::getTicks()
{
	// actual timer time
	int time = 0;

    if(started) { // if timer running
        if(paused) { // if timer paused
            // return ticks when timer was paused
            time = pausedTicks;
        } else {
            // return current time minus start time
            time = SDL_GetTicks() - startTicks;
        }
    }

    return time;
}

bool Timer::isStarted()
{
	// timer is running and paused or unpaused
    return started;
}

bool Timer::isPaused()
{
	// timer is running and paused
    return paused && started;
}