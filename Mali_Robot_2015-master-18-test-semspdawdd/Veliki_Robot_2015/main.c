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
	_delay_ms(100);
	
	while(1)
		{
			if(GPIO_PinRead(changeSides) == 0)
			{	
				greenSide();
			}
			else if(GPIO_PinRead(changeSides) == 1)
			{
				yellowSide();
			}
		}
		
}
