#ifndef _KEY_H
#define _KEY_H

#include "main.h"


#define SCANNER_PERIOD	10
#define SHORTTICKS	200/SCANNER_PERIOD
#define LONGTICKS		500/SCANNER_PERIOD

#define KEY_IS_PRESSING			0

#define KEYNUM			4

typedef enum 
{
	State0 = 0,
	State1,
	State2,
	State3,
	State4
}KEYSTATE_ENUM;

typedef enum {
	NonePress = 0,
	PressDown,
	PressUp,
	PressRepeat,
	LongPressStart,
	LongPressHold
}KEYMOVEMENT_ENUM;

typedef enum {
	NoneEvent = 0,
	SingleClick,
	DoubleClick,
	LongHold,
}KEYEVENT_ENUM;

typedef struct KEY
{
	uint32_t 	PressTime;
	uint32_t 	ReleaseTime;
	uint8_t		KeyState;
	uint8_t		KeyMovement;
	uint8_t		KeyEvent;
	uint8_t 	ClickNum;
}KEY;

extern KEY myKey[KEYNUM];

void Key_Scanner(void);
void Key_EventClean(KEY* Key);

#endif
