#include "system.h"
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define _MMIO_BYTE(mem_addr) (*(volatile uint8_t *)(mem_addr))

struct gpio
{
	volatile unsigned char *baseAddress;
	volatile unsigned char pinPosition;
	volatile unsigned char buffer[3];
};

typedef struct gpio GPIOData;

static volatile GPIOData *gpios[MAX_INPUTS];
static volatile unsigned char inputsNumber = 0;
static volatile long systemTime;

unsigned char GPIO_PinRegister(volatile unsigned char *baseAddress, unsigned char pin)
{
	if(inputsNumber >= MAX_INPUTS)
		return 0;

	unsigned char i;

	gpios[inputsNumber] = (GPIOData *)malloc(sizeof(GPIOData));
	if(gpios[inputsNumber] == NULL)
		return -1;

	gpios[inputsNumber]->baseAddress = baseAddress;
	gpios[inputsNumber]->pinPosition = pin;
	for(i = 0; i < 3; i++)
		gpios[inputsNumber]->buffer[i] = 0;

	//_MMIO_BYTE(baseAddress - 1) &= ~(1 << pin);
	_MMIO_BYTE(baseAddress - 1) &= (0 << pin);
	//_MMIO_BYTE(baseAddress) |= (1 << pin);
	_MMIO_BYTE(baseAddress) &= (0 << pin);

	i = inputsNumber;
	inputsNumber++;

	return i;
}

unsigned char GPIO_PinRead(unsigned char pinHandler)
{
	return ( (gpios[pinHandler]->buffer[0]) & (gpios[pinHandler]->buffer[1]) & (gpios[pinHandler]->buffer[2]) );
}

unsigned char GPIO_ReadFromRegister(unsigned char pinHandler)
{
	unsigned char state = 0;

	state = ((_MMIO_BYTE(gpios[pinHandler]->baseAddress - 2)) >> (gpios[pinHandler]->pinPosition)) & 0x01;

	return state;
}

void fillDebaunsingData(void)
{
	unsigned char i;
	static char j = 0;

	if(++j >= 3)
		j = 0;

	for(i = 0; i < inputsNumber; ++i)
		gpios[i]->buffer[j] = GPIO_ReadFromRegister(i);
}

void Timer_Init(unsigned int freq)
{
    TCCR1A = 0;
	TCCR1B = (1 << WGM12) | (1 << CS10);
	OCR1A = (double)F_CPU / freq + 0.5;
	TIMSK1 = 1 << OCIE1A;

	SREG |= 0x80;
}

ISR(TIMER1_COMPA_vect)
{
	fillDebaunsingData();
    #if USE_TIMER_HOOK == 1
    Timer_Hook();
    #endif // USE_TIMER_HOOK
	systemTime++;
}

void systemInit(void)
{
	Timer_Init(1000);
	servo_init(100);
	DDRG = 0xFF;
	CAN_Init(4);
	
	forwardLeftSensor = GPIO_PinRegister(GPIOA_BASE, 2); // PREDNJI LEVI SENZOR ZA STEPENICE
	forwardRightSensor = GPIO_PinRegister(GPIOA_BASE, 0); // PREDNJI DESNI SENZOR //promenjen za 0
	backwardLeftSensor = GPIO_PinRegister(GPIOA_BASE, 3); // ZADNJI LEVI SENZOR	
	backwardRightSensor = GPIO_PinRegister(GPIOA_BASE, 1);	//ZADNJI DESNI SENZOR
	changeSides = GPIO_PinRegister(GPIOB_BASE, 0);	//CHANGE SIDES
	jumper = GPIO_PinRegister(GPIOB_BASE, 7);
	systemTime = 0;
	
	carpetsReleased = 0;
}

unsigned long getSystemTime(void)
{
	return systemTime;
}
int jumperCheck(void)
{
	if (GPIO_PinRead(jumper) == 1)
	{
		return 0;
	}
	
	return 1;
}//END OF jumperCheck
void servo_init(unsigned int f_pwm)
{
	DDRE |= (1 << PINE3) | (1 << PINE4) | (1 << PINE5);
	
	TCNT3 = 0;
	OCR3A = 0;
	OCR3B = 0;
	OCR3C = 0;
	
	TCCR3A = (1 << COM3A1) | (1 << COM3A0) | (1 << COM3B1) | (1 << COM3B0) | (1 << COM3C1) | (1 << COM3C0) | (1 << WGM31);
	TCCR3B = (1 << WGM32) | (1 << WGM33) | (1 << CS30); // PRESKALER = 1
	ICR3 = F_CPU / f_pwm - 0.5; // FREKVENCIJA PWMA JE ~19kHz
}

//Zatvoren drzac za klapne je na 250
//Otvoren drzac za klapne je na 180
//ali stavimo 190 za sigurno
void servo_position(unsigned char dutyCycle)
{
	if (dutyCycle > 250 || dutyCycle < 165)
	{
		dutyCycle = 200;
	}
	
	OCR3A = ((double)ICR3 / 255) * dutyCycle + 0.5;
}
