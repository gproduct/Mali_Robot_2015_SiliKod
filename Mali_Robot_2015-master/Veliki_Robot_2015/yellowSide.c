#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "system.h"
#include "odometry.h"
#include "can.h"
#include "sides.h"
#include "usart.h"

char stepDetection(void)
{
	if(GPIO_PinRead(forwardLeftSensor) == 0)
	{//OVO JE SVE ISPRAVNO
		stop(SOFT_STOP);																
		_delay_ms(2000);																
		rotate(-50,40,NULL);//rotira se zato sto se on sam | nemam pojma zasto	
		_delay_ms(1000);																
		moveOnDirection(10,40,NULL);//malo ide napred
		_delay_ms(100);											
		moveOnDirection(-230,50,NULL);//popne se do pola								
		_delay_ms(100);																	
		servo_position(170);//podigni servo / pusti tepih								
		_delay_ms(100);																	
		moveOnDirection(-190,50,NULL);//popne se do kralja									
		moveOnDirection(-10,40,NULL);//malo cimne										
		while(1);																		
	}
	else
	{
		
	}
	return 0;
}



/*************************************************************************************************************************************************************************************
																POZICIJE,BRZINE,SMEROVI I DETEKCIJE ZA ZUTU STRANU
*************************************************************************************************************************************************************************************/
const moveOnDirectionFields yellowSideTacticOnePositions[TACTIC_ONE_POSITION_COUNT] =
{
	//SERVO STAVITI NA MAX
	{-200, 90, NULL},//ide do centra							//1
	{-300, 40, stepDetection}//popne se, ali ceka detekciju		//2	
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
				
				if(currentPosition == 0)//rotira se za 86 za stepenice
				{
					_delay_ms(1000);
 					rotate(86 ,50, NULL);
					_delay_ms(1000);	
				}
				else if(currentPosition == 1)
				{
					
				}
				else if(currentPosition == 2)
				{

				}
				
			}//end for
			break;
		}
	}//end while(1)
	
}