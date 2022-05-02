#ifndef PROJECT1_H_
#define PROJECT1_H_

#include <chrono>
#include <climits> 
#include <iostream>


using namespace std::chrono;

class TimedEventTracker {

public:
	// These are public to allow for faster unit testing
	steady_clock::time_point startTime;
	unsigned long count;

	TimedEventTracker() {
		this->timerDuration = 0;
		this->count = 0;
		this->active = false;
		this->startTime = steady_clock::now();
	}

	/*
	If a countable event happens this will return true,
	otherwise it will return false
	*/
	bool event() {
		uint32_t timePassed = getSecondsPassed();

 		if (active && timePassed < this->timerDuration) {
			this->count = ULLONG_MAX == this->count ? ULLONG_MAX : this->count + 1;
			return true;
		} else {
			active = false;
			return false;
		}
	}

	/*
	Sets the duration for the timer if the timer is not active.
	If it is successful at setting the time it will return true,
	else it returns false;
	*/
	bool setTimerDuration(uint32_t duration) {
		if (!this->getTimerActive()) {
			this->timerDuration = duration;
			return true;
		}
		return false;
	}

	/*
	returns the current timer duration
	*/
	uint32_t getTimerDuration() {
		return this->timerDuration;
	}

	/*
	Starts the timer and resets the count to zero
	*/
	void startTimer() {
		this->startTime = steady_clock::now();;
		count = 0;
		active = true;
	}

	/*
	returns the current count
	*/
	unsigned long getCount() {
		return count;
	}

	/*
	returns the activity of the timer
	*/
	bool getTimerActive() {
		uint32_t timePassed = getSecondsPassed();
		this->active = (active && timePassed < this->timerDuration);
		return this->active;
	}

	/*
	Deconstructor
	*/
	~TimedEventTracker() {};

private:
	uint32_t timerDuration;
	bool active;

	uint32_t getSecondsPassed() {
		steady_clock::time_point currTime = steady_clock::now();
		return duration_cast<duration<int> >(currTime - startTime).count();
	} 
};
#endif /* PROJECT1_H_ */