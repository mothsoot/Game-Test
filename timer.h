#pragma once

#include "main.h"

const int FPS = 60;
const int SKIP_TICKS = 1000 / FPS;

// application time based timer
class timer
{
    public:
		//Initializes variables
		timer();

		//The various clock actions
		void start();
		void stop();

		//Gets the timer's time
		int getTicks();

		//Checks the status of the timer
		bool isStarted();

    private:
		//The clock time when the timer started
		int startTicks;

		//The timer status
		bool started;
};