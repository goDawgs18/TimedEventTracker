#ifndef PROJECT1_H_
#define PROJECT1_H_

#include <chrono>
#include <climits> 

#include <iostream>


using namespace std::chrono;

class TimedEventTracker {
private:
	uint32_t timerDuration;
	bool active;

public:
	steady_clock::time_point startTime;
	unsigned long count;

	TimedEventTracker() {
		this->timerDuration = 0;
		this->count = 0;
		this->active = false;
		this->startTime = steady_clock::now();
	}

	bool event() {
		// std::cout << "currTime: " << startTime << std::endl;
		// std::cout << "currTime: " << startTime +  << std::endl;

		steady_clock::time_point currTime = steady_clock::now();
		int timePassed = duration_cast<duration<int> >(currTime - startTime).count();

 		if (active && timePassed < this->timerDuration) {
			this->count = ULLONG_MAX == this->count ? ULLONG_MAX : this->count + 1;
			return true;
		} else {
			active = false;
			return false;
		}
	}

	void setTimerDuration(uint32_t duration) {
		if (duration < std::chrono::steady_clock::duration::max().count()) {
			this->timerDuration = duration;
		}
	}

	void startTimer() {
		this->startTime = steady_clock::now();;
		count = 0;
		active = true;
	}

	unsigned long getCount() {
		return count;
	}

	~TimedEventTracker() {};

};
#endif /* PROJECT1_H_ */