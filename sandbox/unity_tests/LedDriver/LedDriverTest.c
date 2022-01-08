#include "unity_fixture.h"
#include "LedDriver.h"
#include "RuntimeErrorStub.h"

//Test Descriptions:
//	All LEDS are off after intialization
//	A Single LED can be turned on
// 	A single LED can be turned off
//	Multiple LEDs can be turned on/off
//	Turn on all LEDs
//	Turn off all LEDs
//	Check that it is read only
// 	Query LED state
// 	Check boundary values
//	Check for out-of-bounds values

TEST_GROUP(LedDriver); 

static uint16_t virtualLeds;

TEST_SETUP(LedDriver){

	LedDriver_Create(&virtualLeds);
}

TEST_TEAR_DOWN(LedDriver){
}


TEST(LedDriver, LedsOffAfterCreate){
	uint16_t virtualLeds = 0xffff;
	LedDriver_Create(&virtualLeds);
	TEST_ASSERT_EQUAL_HEX16(0,virtualLeds);
}


TEST(LedDriver, TurnOnLedOne){
	uint16_t virtualLeds;
	LedDriver_Create(&virtualLeds);
	LedDriver_TurnOn(1);
	TEST_ASSERT_EQUAL_HEX16(1,virtualLeds);
}


TEST(LedDriver, TurnOffLedOne){
	uint16_t virtualLeds;
	LedDriver_Create(&virtualLeds);
	LedDriver_TurnOn(1);
	LedDriver_TurnOff(1);
	TEST_ASSERT_EQUAL_HEX16(0,virtualLeds);
}

TEST(LedDriver, TurnOnMultipleLeds){
	LedDriver_TurnOn(9);
	LedDriver_TurnOn(8);
	TEST_ASSERT_EQUAL_HEX16(0X180, virtualLeds);
}

TEST(LedDriver, TurnOnAllLeds){
	LedDriver_TurnAllOn();
	TEST_ASSERT_EQUAL_HEX16(0xffff, virtualLeds);
}

TEST(LedDriver, TurnOffAnyLed){
	LedDriver_TurnAllOn();
	LedDriver_TurnOff(8);
	TEST_ASSERT_EQUAL_HEX16(0Xff7f, virtualLeds);
}

TEST(LedDriver, LedMemoryIsNotReadable){
	virtualLeds = 0xffff;
	LedDriver_TurnOn(8);
	TEST_ASSERT_EQUAL_HEX16(0x80, virtualLeds);
}

TEST(LedDriver, UpperAndLowerBounds){
	LedDriver_TurnOn(1);
	LedDriver_TurnOn(16);
	TEST_ASSERT_EQUAL_HEX16(0X8001,virtualLeds);
}

TEST(LedDriver, OutOfBoundsChangesNothing){
	LedDriver_TurnOn(-1);
	LedDriver_TurnOn(0);
	LedDriver_TurnOn(17);
	LedDriver_TurnOn(3141);
	TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}

TEST(LedDriver, OutOfBoundsTurnOffDoesNoHarm){
	LedDriver_TurnAllOn();
	LedDriver_TurnOff(-1);
	LedDriver_TurnOff(0);
	LedDriver_TurnOff(17);
	LedDriver_TurnOff(3141);
	TEST_ASSERT_EQUAL_HEX16(0xffff, virtualLeds);
}

TEST(LedDriver, OutOfBoundsProducesRuntimeError){
	RuntimeErrorStub_Reset();
	LedDriver_TurnOn(-1);
	TEST_ASSERT_EQUAL_STRING("LED Driver: out-of-bounds LED",
		RuntimeErrorStub_GetLastError());
	TEST_ASSERT_EQUAL(-1, RuntimeErrorStub_GetLastParameter());
}

IGNORE_TEST(LedDriver, OutOfBoundsToDo){
	/* TODO: what should we do during runtime? */
}