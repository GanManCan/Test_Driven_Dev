
#include "LedDriver.h"
#include "RuntimeError.h"
#include <stdlib.h>
#include <memory.h>
#include <stdint.h>

/***  Variables ***/
static uint16_t * ledAddress;
static uint16_t ledsImage;
enum {ALL_LEDS_ON = ~0, ALL_LEDS_OFF = ~ALL_LEDS_ON};

/*** Static Function Declarations ***/
static uint16_t convertLedNumberToBit(int ledNumber);
static void updateHardware(void);

/*** Functions ***/ 

void LedDriver_Create(uint16_t * address){

	ledAddress = address;
	ledsImage = ALL_LEDS_OFF;
	updateHardware();
}


void LedDriver_Destroy(void){
}

void LedDriver_TurnOn(int ledNumber){

	if(ledNumber <= 0 || ledNumber > 16){
		RUNTIME_ERROR("LED Driver: out-of-bounds LED", ledNumber);
		return;
	}

	ledsImage |= convertLedNumberToBit(ledNumber);
	updateHardware();

}

void LedDriver_TurnOff(int ledNumber){

	if(ledNumber <= 0 || ledNumber > 16){
		RUNTIME_ERROR("LED Driver: out-of-bounds LED", ledNumber);
		return;
	}

	ledsImage &= ~(convertLedNumberToBit(ledNumber)); 
	updateHardware();
}

void LedDriver_TurnAllOn(void){
	ledsImage = ALL_LEDS_ON;
	updateHardware();
}

/*** Support Functions ***/
static uint16_t	convertLedNumberToBit(int ledNumber){
	return (1 << (ledNumber-1));
}

static void updateHardware(void){
	*ledAddress = ledsImage;
}

