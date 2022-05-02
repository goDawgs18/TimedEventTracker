#include <iostream>
#include <gtest/gtest.h>

#include "timedEventTracker.h"
#include <unistd.h>
#include <chrono>

// Sanity check on google test
TEST(GoogleTest, basics) {
	ASSERT_EQ(0, 0);
}

TEST(TimedEventTrackerTest, EasyCase) {
	TimedEventTracker * testingObj = new TimedEventTracker();

	int timerDuration = 1;
	testingObj->setTimerDuration(timerDuration);

	testingObj->event();
	EXPECT_EQ(testingObj->getCount(), 0);

	testingObj->startTimer();

	int numEvents = 10;

	for (int i = 0; i < numEvents; i++) {
		testingObj->event();
	}
	// This will let tests run without the delay
	testingObj->startTime -= std::chrono::seconds(timerDuration);

	testingObj->event();

	EXPECT_EQ(testingObj->getCount(), numEvents);
	
	delete testingObj;
}



TEST(TimedEventTracker, ZeroTimer) {
	TimedEventTracker * testingObj = new TimedEventTracker();

	int timerDuration = 0;
	testingObj->setTimerDuration(timerDuration);
	
	testingObj->startTimer();

	int numEvents = 10;

	for (int i = 0; i < numEvents; i++) {
		testingObj->event();
	}
	
	EXPECT_EQ(testingObj->getCount(), 0);
	
	delete testingObj;
}

TEST(TimedEventTracker, CountOverFlow) {
	TimedEventTracker * testingObj = new TimedEventTracker();

	int timerDuration = 10;
	testingObj->setTimerDuration(timerDuration);
	testingObj->startTimer();
	
	testingObj->count = ULLONG_MAX;
	
	EXPECT_EQ(testingObj->getCount(), ULLONG_MAX);

	testingObj->event();
	EXPECT_EQ(testingObj->getCount(), ULLONG_MAX);
	
	delete testingObj;
}

TEST(TimedEventTracker, ReUseTimer) {
	TimedEventTracker * testingObj = new TimedEventTracker();

	int timerDuration = 1;
	int numEvents = 10;

	testingObj->setTimerDuration(timerDuration);
	testingObj->startTimer();
	
	for (int i = 0; i < numEvents; i++) {
		testingObj->event();
	}
	EXPECT_EQ(testingObj->getCount(), numEvents);

	testingObj->startTimer();
	EXPECT_EQ(testingObj->getCount(), 0);
	
	testingObj->event();

	EXPECT_EQ(testingObj->getCount(), 1);
	// This will let tests run without the delay
	testingObj->startTime -= std::chrono::seconds(timerDuration);

	testingObj->event();
	EXPECT_EQ(testingObj->getCount(), 1);
	
	delete testingObj;
}

TEST(TimedEventTracker, TimerRunOut) {
	TimedEventTracker * testingObj = new TimedEventTracker();

	int timerDuration = 1;
	testingObj->setTimerDuration(timerDuration);
	testingObj->startTimer();
	testingObj->startTime -= std::chrono::seconds(timerDuration);

	int numEvents = 10;

	for (int i = 0; i < numEvents; i++) {
		testingObj->event();
	}

	EXPECT_EQ(testingObj->getCount(), 0);
	
	delete testingObj;
}

TEST(TimedEventTracker, TimerMax) {
	TimedEventTracker * testingObj = new TimedEventTracker();

	uint32_t timerDuration = UINT32_MAX;
	testingObj->setTimerDuration(timerDuration);
	testingObj->startTimer();
	
	int numEvents = 10;

	for (int i = 0; i < numEvents; i++) {
		testingObj->event();
	}
	testingObj->startTime -= std::chrono::seconds(timerDuration);

	testingObj->event();

	EXPECT_EQ(testingObj->getCount(), numEvents);
	
	delete testingObj;
}