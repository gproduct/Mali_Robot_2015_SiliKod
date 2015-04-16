#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "system.h"
#include "odometry.h"
#include "can.h"
#include "sides.h"
#include "usart.h"

char stepDetectionGreen(void)
{
	if(GPIO_PinRead(forwardLeftSensor) == 1)
	{
		PORTG = 0xff;
		PORTG = 0x01;
		PORTG = 0xff;
		stop(SOFT_STOP);
		_delay_ms(3000);
		moveOnDirection(100,40,NULL);
		/*	moveOnDirection(-200,40,NULL);
		_delay_ms(100);
		servo_position(180);
		_delay_ms(100);
		servo_position(250);
		_delay_ms(100);
		moveOnDirection(-300,40,NULL);	*/
		while(1);
	}
	else
	{
		
	}
	return 0;
}


/*************************************************************************************************************************************************************************************
											 					POZICIJE,BRZINE,SMEROVI I DETEKCIJE ZA ZELENU STRANU
*************************************************************************************************************************************************************************************/
const moveOnDirectionFields greenSideTacticOnePositions[TACTIC_ONE_POSITION_COUNT] =
{
	//SERVO STAVITI NA MAX
	{-200, 90, NULL},
	{-200, 40, stepDetectionGreen}
						
};




/*************************************************************************************************************************************************************************************
																				ZELENA STRANA
*************************************************************************************************************************************************************************************/
void greenSide(void)
{
	position startingPosition;
	unsigned char currentPosition = 0, nextPosition = 0, odometryStatus;
	unsigned char activeState = TACTIC_ONE;
	
	startingPosition.x = 520;
	startingPosition.y = 990;
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
				odometryStatus = moveOnDirection(greenSideTacticOnePositions[currentPosition].distance, greenSideTacticOnePositions[currentPosition].speed, greenSideTacticOnePositions[currentPosition].detectionCallback);
				
				if(odometryStatus == ODOMETRY_FAIL)
				{

				}
				else if(odometryStatus == ODOMETRY_STUCK)
				{
					
				}
				if(currentPosition == 0)
				{
					_delay_ms(1000);
					rotate(-85 ,40, NULL);
					_delay_ms(1000);	
				}
				else if(currentPosition == 1)
				{
					
				}
				else if(currentPosition == 2)
				{
					/*PORTG = 0xff;
					servo_position(180);
					_delay_ms(500);
					servo_position(250);
					_delay_ms(500);
					//TREBA SERVO DO MAX!!!!!*/
					
				}
				
			}//end for
			break;
		}
	}//end while(1)
	
	
}