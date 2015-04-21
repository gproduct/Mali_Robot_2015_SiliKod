#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "system.h"
#include "odometry.h"
#include "can.h"
#include "sides.h"
#include "usart.h"

/*char driveByGreen(unsigned long startTime)
{
	if(carpetsReleased == 0)
	{
		if(getSystemTime() - startTime >= 4000)
		{
			servo_position(190);
		}
	}
	return 0;
}*/
char driveByYellow(void)
{
	if(carpetsReleased == 0)
	{
		_delay_ms(3000);
		servo_position(190);
		_delay_ms(1000);
		servo_position(0);//iskljucen
		carpetsReleased = 1;	
	}
}
char detectEnemyYellow(unsigned long startTime)
{
	if(GPIO_PinRead(forwardLeftSensor) == 0 || GPIO_PinRead(forwardRightSensor) == 0)
	{
		stop(SOFT_STOP);
		_delay_ms(1000);
	}
	return 0;
}






/*************************************************************************************************************************************************************************************
																POZICIJE,BRZINE,SMEROVI I DETEKCIJE ZA ZUTU STRANU
*************************************************************************************************************************************************************************************/
const moveOnDirectionFields yellowSideTacticOnePositions[TACTIC_ONE_POSITION_COUNT] =
{
	{-227,90,detectEnemyYellow},//ide do pola stola							//1//provereno dobro (gostojic kaze ;) ) //original 217
	{-730,40,driveByYellow}//popne se										//2	proveriti jer je 30 vise nego yellow side
};
/*************************************************************************************************************************************************************************************
																				ZUTA STRANA
*************************************************************************************************************************************************************************************/
void yellowSide(void)
{
	position startingPosition;
	unsigned char currentPosition = 0, nextPosition = 0, odometryStatus;
	unsigned char activeState = TACTIC_ONE;
	
	startingPosition.x = 0;
	startingPosition.y = 0;
	startingPosition.angle = 0;
	setPosition(startingPosition);
	
	while (1)
	{
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
					_delay_ms(1000);
					rotate(76,50,NULL);//rotira se za stepenice
					_delay_ms(1000);
				}
				else if(currentPosition == 1)
				{
					_delay_ms(500);
					servo_position(250);
					while(1);
				}
			}//end for
			break;
		}
	}//end while(1)
	
}