#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "system.h"
#include "odometry.h"
#include "can.h"z
#include "sides.h"
#include "usart.h"


//NO TAC CODE HOCE PERA KILL

char detectAfterGreen(unsigned long startTime)
{
	if(GPIO_PinRead(forwardLeftSensor) == 1 || GPIO_PinRead(forwardRightSensor) == 1)
	{
		//URADI DA SAMO DA STANE DA CEKA
		while(1);
	}
	return 0;
}

char driveByGreen(void)
{
	if(carpetsReleased == 0)
	{
		_delay_ms(3650);
		servo_position(180);
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
		{//slow | samo detekcija da izadje veliki | samo da baci
			
			if(getSystemTime() - startTime >= 1000 && getSystemTime() - startTime <= 1100)
			{
				stop(SOFT_STOP);
				_delay_ms(2000);
				moveOnDirection(-155,90,detectAfterGreen);
			}
			else if(getSystemTime() - startTime >= 1100 && getSystemTime() - startTime <= 1200)
			{
				stop(SOFT_STOP);
				_delay_ms(2000);
				moveOnDirection(-142,90,detectAfterGreen);
			}
			else if(getSystemTime() - startTime >= 1200 && getSystemTime() - startTime <= 1300)
			{
				stop(SOFT_STOP);
				_delay_ms(2000);
				moveOnDirection(-125,90,detectAfterGreen);
			}
			else if(getSystemTime() - startTime >= 1300 && getSystemTime() - startTime <= 1400)
			{
				stop(SOFT_STOP);
				_delay_ms(2000);
				moveOnDirection(-90,90,detectAfterGreen);
			}
			else if(getSystemTime() - startTime >= 1350)
			{
				stop(SOFT_STOP);
				_delay_ms(2000);
				moveOnDirection(-80,90,detectAfterGreen);
			}
			//dotle brate mili
			
			
		}
	}
	return 0;
}





/*************************************************************************************************************************************************************************************
											 					POZICIJE,BRZINE,SMEROVI I DETEKCIJE ZA ZELENU STRANU
*************************************************************************************************************************************************************************************/
const moveOnDirectionFields greenSideTacticOnePositions[TACTIC_ONE_POSITION_COUNT] =
{
	{-218,80,detectEnemyGreen},//ide do pola stola							//1//provereno dobro (gostojic kaze ;) ) 
	{-725,50,driveByGreen}//popne se										//2	proveriti jer je 30 vise nego yellow side	//90
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
					_delay_ms(500);
					rotate(-83,50,NULL);//rotira se za stepenice
					_delay_ms(500);
				}
				else if(currentPosition == 1)
				{
					//rotacija
					/*rotate(90,40,NULL);
					_delay_ms(500);*/
					servo_position(250);
					while(1);
				}			
			}//end for				
			break;
		}
	}//end while(1)
	
	
}