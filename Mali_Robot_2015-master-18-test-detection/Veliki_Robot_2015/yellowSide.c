#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "system.h"
#include "odometry.h"
#include "can.h"
#include "sides.h"
#include "usart.h"

/*char detectNiggasGreen(unsigned long startTime)
{
	if(sensorCheck == 0)
	{
		if(getSystemTime() - startTime >= 1000)
		{
			stop(SOFT_STOP);
			sensorCheck = 1;
		}
	}
	return 0;
}*/
char driveByYellow(void)
{
	if(carpetsReleased == 0)
	{
		_delay_ms(3100);//3050
		servo_position(190);
		_delay_ms(1000);
		servo_position(0);//iskljucen
		carpetsReleased = 1;	
	}
}
char detectEnemyYellow(unsigned long startTime)
{
	if(GPIO_PinRead(forwardLeftSensor) == 1 || GPIO_PinRead(forwardRightSensor) == 1)
	{
		/*if(getSystemTime() - startTime >= 1000)
		{
			
			stop(SOFT_STOP);
			PORTG = 0xff;
			_delay_ms(4000);
			moveOnDirection(-150,80,NULL);
		}
		else if(getSystemTime() - startTime >= 2000)
		{
			
			stop(SOFT_STOP);
			PORTG = 0xff;
			_delay_ms(4000);
			
		}
		
			stop(SOFT_STOP);
			PORTG = 0xff;
			_delay_ms(4000);
			int tempTime = (int) getSystemTime() - startTime;
			moveOnDirection(-(tempTime/10),80,NULL);
		}
		else if(getSystemTime() - startTime >= 1500)
		{
			stop(SOFT_STOP);
			sensorCheck = 1;
		}
		else if(getSystemTime() - startTime >= 2000)
		{
			stop(SOFT_STOP);
			sensorCheck = 1;
		}*/
	}
	return 0;
}






/*************************************************************************************************************************************************************************************
																POZICIJE,BRZINE,SMEROVI I DETEKCIJE ZA ZUTU STRANU
*************************************************************************************************************************************************************************************/
const moveOnDirectionFields yellowSideTacticOnePositions[TACTIC_ONE_POSITION_COUNT] =
{
	{-208,90,detectEnemyYellow},//ide do pola stola							//1//provereno dobro (gostojic kaze ;) ) //original 212
	{-705,40,driveByYellow}//popne se										//2	proveriti jer je 30 vise nego yellow side
};
/*************************************************************************************************************************************************************************************
																				ZUTA STRANA
*************************************************************************************************************************************************************************************/
void yellowSide(void)
{
	position startingPosition;
	unsigned char currentPosition = 0, nextPosition = 0, odometryStatus;
	unsigned char activeState = TACTIC_ONE;
	unsigned long startTime = getSystemTime();
	
	startingPosition.x = 0;
	startingPosition.y = 0;
	startingPosition.angle = 0;
	setPosition(startingPosition);
	
	while (1)
	{
		/*GASENJE POSLE 90 SEKUNDI
		if(getSystemTime() - startTime >= 5000)
		{
			while(1);
		}
		*/
		switch(activeState)
		{
			case TACTIC_ONE:
			for (currentPosition = nextPosition; currentPosition < TACTIC_ONE_POSITION_COUNT; currentPosition++)
			{
				// mozda ubaciti if-else sa akcijama tipa regularno- kretanje, i alternativno- sta god
				
				odometryStatus = moveOnDirection(yellowSideTacticOnePositions[currentPosition].distance, yellowSideTacticOnePositions[currentPosition].speed, yellowSideTacticOnePositions[currentPosition].detectionCallback);
				
				if(odometryStatus == ODOMETRY_FAIL)
				{

				}
				else if(odometryStatus == ODOMETRY_STUCK)
				{
					
				}
				
				if(currentPosition == 0)
				{
					char *tempTimeString;
					int tempTime = (int) getSystemTime() - startTime;
					sprintf(tempTimeString, "%d", tempTime);
					UART0_Init(9600, 1);
					//UART0_Write(*tempTimeString);
						UART0_Write('a');
					if(UART0_Read())
					{
						while(1)
						{
							PORTG = 0xFF;
							_delay_ms(500);
							PORTG = 0x00;
							_delay_ms(500);
						};
					}
					while(1);
					/*
					_delay_ms(1000);
					rotate(72,50,NULL);//rotira se za stepenice 76
					_delay_ms(1000);
					*/
				}
				else if(currentPosition == 1)
				{
					//rotacija
					/*
					servo_position(250);
					while(1);
					*/
				}
			}//end for
			break;
		}
	}//end while(1)
	
}