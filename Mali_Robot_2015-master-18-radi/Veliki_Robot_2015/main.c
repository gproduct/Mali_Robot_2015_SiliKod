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
			yellowSide();
		}
		
}
