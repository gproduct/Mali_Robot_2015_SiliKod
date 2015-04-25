#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "system.h"
#include "odometry.h"
#include "can.h"z
#include "sides.h"
#include "usart.h"


//NO TAC CODE HOCE PERA KILL



char driveByGreen(void)
{
	if(carpetsReleased == 0)
	{
		_delay_ms(3650);
		servo_position(190);
		_delay_ms(1000);
		servo_position(0);//iskljucen
		
		carpetsReleased = 1;	
	}
}
char detectEnemyGreen(unsigned long startTime)
{
	if(GPIO_PinRead(forwardLeftSensor) == 1 || GPIO_PinRead(forwardRightSensor) == 1)
	{
		if(checkSensor == 0)
		{
			stop(SOFT_STOP);
			//URADI DA KAD DETEKTUJE DA SAMO STOJI DOK NE DETEKTUJE NISTA
			
		}
		
		return 1;
	}
	return 0;
}





/*************************************************************************************************************************************************************************************
											 					POZICIJE,BRZINE,SMEROVI I DETEKCIJE ZA ZELENU STRANU
*************************************************************************************************************************************************************************************/
const moveOnDirectionFields greenSideTacticOnePositions[TACTIC_ONE_POSITION_COUNT] =
{
	{-750,60,detectEnemyGreen}
};
/*************************************************************************************************************************************************************************************
																				ZELENA STRANA
*************************************************************************************************************************************************************************************/
void greenSide(void)
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
			case COLLISION:
				while(detectEnemyGreen(0) == 1)
					_delay_ms(100);
					
				activeState = TACTIC_ONE;
				nextPosition = currentPosition;
				break;
			case TACTIC_ONE:
			for (currentPosition = nextPosition; currentPosition < TACTIC_ONE_POSITION_COUNT; currentPosition++)
			{
				// mozda ubaciti if-else sa akcijama tipa regularno- kretanje, i alternativno- sta god
				odometryStatus = moveOnDirection(greenSideTacticOnePositions[currentPosition].distance, greenSideTacticOnePositions[currentPosition].speed, greenSideTacticOnePositions[currentPosition].detectionCallback);
				
				if(odometryStatus == ODOMETRY_FAIL)
				{
					activeState = COLLISION;
					nextPosition = currentPosition;
					break;
				}
				else if(odometryStatus == ODOMETRY_STUCK)
				{
					
				}
				if(currentPosition == 0)
				{
					
				}
				else if(currentPosition == 1)
				{
					while(1);
				}			
			}//end for				
			break;
		}
	}//end while(1)
	
	
}