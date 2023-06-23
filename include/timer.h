#pragma once

#include "main.h"

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