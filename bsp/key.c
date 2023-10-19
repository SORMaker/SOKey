#include "key.h"

KEY myKey[KEYNUM] = {0,0,State0,NonePress,NoneEvent,0};

static void Key_Reset(KEY* Keyi)
{
	Keyi->KeyEvent = NoneEvent;
	Keyi->KeyMovement = NonePress;
	Keyi->KeyState = State0;
	Keyi->PressTime = 0;
	Keyi->ReleaseTime = 0;
	Keyi->ClickNum = 0;
}

void Key_Scanner()
{
	uint8_t i = 0;
	for(i = 0; i < KEYNUM; i++){
//		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) != KEY_IS_PRESSING){
//			myKey[i].ReleaseTime++;
//		}
		
		if(myKey[i].KeyEvent == NoneEvent)
		{
				switch(myKey[i].KeyState){
					case State0:
						myKey[i].KeyMovement = NonePress;
						myKey[i].ReleaseTime = 0;
						if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == KEY_IS_PRESSING){
							myKey[i].KeyState = State1;
							myKey[i].KeyMovement = PressDown;
						}
						else{					
							myKey[i].KeyState = State0;
							myKey[i].KeyMovement = NonePress;
							myKey[i].KeyEvent = NoneEvent;
						}
						break;
					case State1:
						myKey[i].PressTime++;
						if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == KEY_IS_PRESSING
							&& myKey[i].PressTime > LONGTICKS){
							myKey[i].KeyState = State4;
							myKey[i].KeyMovement = LongPressStart;
							myKey[i].PressTime = 0;
						}
						else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) != KEY_IS_PRESSING){
							myKey[i].KeyState = State2;
							myKey[i].KeyMovement = PressUp;
							myKey[i].ClickNum = 1;
							myKey[i].PressTime = 0;
						}							
//							&& myKey[i].ReleaseTime > SHORTTICKS){	
//							myKey[i].KeyState = State0;
//							myKey[i].KeyMovement = PressUp;
//							myKey[i].KeyEvent = SingleClick;
//							myKey[i].PressTime = 0;
//							myKey[i].ReleaseTime = 0;
//						}
//						else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) != KEY_IS_PRESSING){
//							Key_Reset(&myKey[i]);
//						}
						break;
					case State2:
						myKey[i].ReleaseTime++;
					if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) != KEY_IS_PRESSING 
						&& myKey[i].ReleaseTime > SHORTTICKS){
							myKey[i].KeyState = State0;
//							Key_Reset(&myKey[i]);
							myKey[i].KeyMovement = PressUp;
							if(myKey[i].ClickNum == 1){
								myKey[i].KeyEvent = SingleClick;							
							}
							else if(myKey[i].ClickNum == 2){
								myKey[i].KeyEvent = DoubleClick;	
							}
					}
					else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == KEY_IS_PRESSING){
						myKey[i].KeyState = State3;
						myKey[i].KeyMovement = PressDown;
						myKey[i].ReleaseTime = 0;
					}
						break;
					case State3:
						myKey[i].PressTime++;
						if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) != KEY_IS_PRESSING 
						&& myKey[i].PressTime > SHORTTICKS){
							myKey[i].KeyState = State0;
//							Key_Reset(&myKey[i]);
							myKey[i].KeyMovement = PressUp;
							myKey[i].PressTime = 0;
							myKey[i].ClickNum = 0;
						}
						else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) != KEY_IS_PRESSING 
						&& myKey[i].PressTime <= SHORTTICKS){
							myKey[i].KeyState = State2;
							myKey[i].KeyMovement = PressUp;
							myKey[i].ClickNum++;
							myKey[i].PressTime = 0;
						}
						break;
					case State4:
						if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == KEY_IS_PRESSING){
							myKey[i].KeyState = State4;
							myKey[i].KeyMovement = LongPressHold;
						}
						else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) != KEY_IS_PRESSING){
							myKey[i].KeyState = State0;
//							Key_Reset(&myKey[i]);
							myKey[i].KeyMovement = PressUp;
							myKey[i].KeyEvent = LongHold;
						}
						break;
			}
		}
	}
}

void Key_EventClean(KEY* Key)
{
	uint8_t i = 0;
	for(i = 0; i < KEYNUM; i++){
		if(Key[i].KeyEvent != NoneEvent){
			Key[i].KeyEvent = NoneEvent;
		}
	}
}
