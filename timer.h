#pragma once

#include "main.h"

const int FPS = 60;
const int SKIP_TICKS = 1000 / FPS;

// application time based timer
class timer
{
    public:
		// constructor
		timer();
        // destructor
        ~timer();

		void start();
		void stop();

		// gets timer's time
		int getTicks();

    private:
		// clock time when timer started
		int startTicks;

		// timer status
		bool started;
};