#pragma once

#include "screen.h"

// application time based timer
class Timer
{
	public:
		Timer();
		~Timer() {}

		void start();
		void stop();
		void pause();
		void unpause();

		// gets timer's time
		int getTicks();

		// check timer status
		bool isStarted();
		bool isPaused();

	private:
		// clock time when timer started
		int startTicks;

		// ticks stored when timer paused
		int pausedTicks;

		// timer status
		bool started;
		bool paused;
};