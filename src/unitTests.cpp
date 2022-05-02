#include <iostream>
#include <gtest/gtest.h>

#include "timedEventTracker.h"
#include <unistd.h>
#include <chrono>

// Sanity check on google test
TEST(GoogleTest, basics) {
	ASSERT_EQ(0, 0);
}

TEST(TimedEventTracker, EasyCase) {
	TimedEventTracker * testingObj = new TimedEventTracker();

	int timerDuration = 1;
	testingObj->setTimerDuration(timerDuration);

	EXPECT_EQ(testingObj->event(), false);
	EXPECT_EQ(testingObj->getCount(), 0);

	testingObj->startTimer();

	int numEvents = 10;

	for (int i = 0; i < numEvents; i++) {
		EXPECT_EQ(testingObj->event(), true);
	}
	// This will let tests run without the delay
	testingObj->startTime -= std::chrono::seconds(timerDuration);

	EXPECT_EQ(testingObj->event(), false);

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
		EXPECT_EQ(testingObj->event(), false);
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

	EXPECT_EQ(testingObj->event(), true);
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
		EXPECT_EQ(testingObj->event(), true);
	}
	EXPECT_EQ(testingObj->getCount(), numEvents);

	testingObj->startTimer();
	EXPECT_EQ(testingObj->getCount(), 0);
	
	EXPECT_EQ(testingObj->event(), true);

	EXPECT_EQ(testingObj->getCount(), 1);
	// This will let tests run without the delay
	testingObj->startTime -= std::chrono::seconds(timerDuration);

	EXPECT_EQ(testingObj->event(), false);
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
		EXPECT_EQ(testingObj->event(), false);
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
		EXPECT_EQ(testingObj->event(), true);
	}
	testingObj->startTime -= std::chrono::seconds(timerDuration);

	EXPECT_EQ(testingObj->event(), false);

	EXPECT_EQ(testingObj->getCount(), numEvents);
	
	delete testingObj;
}

TEST(TimedEventTracker, ChangingDurationDuringTimer) {
	TimedEventTracker * testingObj = new TimedEventTracker();

	uint32_t timerDurationA = 1;
	uint32_t timerDurationB = 2;
	
	EXPECT_EQ(testingObj->setTimerDuration(timerDurationA), true);
	testingObj->startTimer();
	EXPECT_EQ(testingObj->getTimerDuration(), timerDurationA);

	EXPECT_EQ(testingObj->setTimerDuration(timerDurationB), false);
	EXPECT_EQ(testingObj->getTimerDuration(), timerDurationA);

	testingObj->startTime -= std::chrono::seconds(timerDurationA);

	EXPECT_EQ(testingObj->setTimerDuration(timerDurationB), true);
	EXPECT_EQ(testingObj->getTimerDuration(), timerDurationB);
	
	delete testingObj;
}

TEST(TimedEventTracker, GetTimerActive) {
	TimedEventTracker * testingObj = new TimedEventTracker();

	int timerDuration = 1;
	testingObj->setTimerDuration(timerDuration);

	EXPECT_EQ(testingObj->event(), false);

	EXPECT_EQ(testingObj->getTimerActive(), false);
	testingObj->startTimer();

	EXPECT_EQ(testingObj->getTimerActive(), true);
		
	testingObj->startTime -= std::chrono::seconds(timerDuration);
	EXPECT_EQ(testingObj->getTimerActive(), false);

	delete testingObj;


}