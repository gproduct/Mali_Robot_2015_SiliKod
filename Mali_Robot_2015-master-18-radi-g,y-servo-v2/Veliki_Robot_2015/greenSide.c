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
	if(GPIO_PinRead(forwardLeftSensor) == 0 || GPIO_PinRead(forwardRightSensor) == 0)//ovaj drugi moramo da probamo
	{
		/*stop(SOFT_STOP);																
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
		moveOnDirection(-10,40,NULL);//malo cimne	*/
		_delay_ms(5000);					
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
	{-220,90,NULL},//ide do pola stola							//1
	{-605,40,NULL},												//2
	{-145,40,NULL}												//3
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
					rotate(-79,50,NULL);//rotira se za stepenice
					_delay_ms(1000);
				}
				else if(currentPosition == 1)
				{
					_delay_ms(100);
					servo_position(190);
					_delay_ms(100);
				}
				else if(currentPosition == 2)
				{
					_delay_ms(1000);
					rotate(-90,40,NULL);//gojkovic reko da stavim :D (samo da bolje izgleda)
					while(1);
				}
				
			}//end for
			break;
		}
	}//end while(1)
	
	
}