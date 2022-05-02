# Timed Event Tracker 
This library is meant to count the number of events that occur within a user defined amount of time. 

## Functions
Here is a table with all of the functions and descriptions for how to use the library

| Function | Return Value| Description |
|--|--|--|
| TimedEventTracker() | TimedEventTracker | constructs a TimedEventTracker with all parameters initialized to zero |
|setTimerDuration(uint32_t duration) | bool | This will set the duration in seconds for the timer object if it not currently active. It will return true if it is able to set the time and false if it is not|
|getTimerDuration() | uint32_t | This will return the current timer duration|
|startTimer()| n/a | This will start the timer and will allow the TimedEventTracker to start counting events. This will also reset the counter to zero|
|event() | bool | This will iterate the counter if a timer is active and it is within the time window. If it is counted then it will return True otherwise if it was not recorded will return false|
|getCount()| unsigned  long | This will return the current count for the TimedEventTracker. It will range from 0 to ULLONG_MAX |
|getTimerActive()| bool | This will return if the timer is active or not |

## Example usage
Here is a breif example of how the library could be implemented. 
```
TimedEventTracker * testingObj = new  TimedEventTracker();
testingObj->setTimerDuration(10);
testingObj->event();

std::cout<< "Counter = " << testingObj->getCount() << std::endl;

testingObj->startTimer();
int  numEvents = 10;
for (int  i = 0; i < numEvents; i++) {
	testingObj->event();
}
std::cout<< "Counter = " << testingObj->getCount() << std::endl;

```
The above code will give an output of the following:
```
Counter = 0
Counter = 10
```
For more examples refer to the unit tests

## Building
To compile the library using `cmake` follow the instructions

 1. Go to build directory
	```
	cd <Timed Event Tracker library path>/build
	```
 2. Run cmake
	 ```
	 cmake ../src
	 ```
3. Configure the build for whether you want to build the test scripts by toggling `BuildTests` field in ccmake
	```
	ccmake .
	```
4. Build
	```
	cmake --build .
	```
	 

## Testing 
There are unit tests implemented for the library using google test. Inorder to run the tests first build the library with the `BuildTests` option set to `ON`. Then simply run one two commands within the build directory
```
./runUnitTests 
```
or
```
ctest
```
