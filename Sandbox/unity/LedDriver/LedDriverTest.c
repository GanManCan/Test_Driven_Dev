#include "unity_fixture.h"

//Test Descriptions:
//	All LEDS are off after intialization
//	A Single LED can be turned on
// 	A single LED can be turned off
//	Multiple LEDs can be turned on/off
//	Turn on all LEDs
//	Turn off all LEDs
// 	Query LED state
// 	Check boundary values
//	Check for out-of-bounds values

TEST_GROUP(LedDriver); 

TEST_SETUP(LedDriver){
}

TEST_TEAR_DOWN(LedDriver){
}

TEST(LedDriver, LedsOffAfterCreate){
	TEST_FAIL_MESSAGE("Start here"); 
}


