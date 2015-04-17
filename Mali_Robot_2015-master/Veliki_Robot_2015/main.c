#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "system.h"
#include "odometry.h"
#include "can.h"
#include "usart.h"
#include "sides.h"

/*void servoRealese()
{
	servo_position(180);
	_delay_ms(1000);
	servo_position(250);
	_delay_ms(1000);
}*/

int main(void)
{
	systemInit();
	while(1)
		{
			//yellowSide();
			/* BEZ BIKONA */
			/*moveOnDirection(-200,90,NULL);
			_delay_ms(1000);
			rotate(90,50,NULL);
			_delay_ms(1000);
			moveOnDirection(-800,40,NULL);
			while(1);*/
			/*
			servo_position(170);
			_delay_ms(500);
			servo_position(250);
			_delay_ms(500);*/
			moveOnDirection(-225, 90, NULL);
			_delay_ms(500);
			rotate(78,60,NULL);
			_delay_ms(1000);
			moveOnDirection(-700, 50, NULL);
			_delay_ms(100);
			rotate(-90,40,NULL);
			moveOnDirection(-10, 50, NULL);
			_delay_ms(5000);
			while(1);
		}
		
}
