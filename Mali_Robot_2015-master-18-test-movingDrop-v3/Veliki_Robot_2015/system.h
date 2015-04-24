#ifndef SYSTEM_H_
#define SYSTEM_H_

#define MAX_INPUTS	    10
#define USE_TIMER_HOOK  1

#define GPIOA_BASE 0x22
#define GPIOB_BASE 0x25
#define GPIOC_BASE 0x28
#define GPIOD_BASE 0x2B
#define GPIOE_BASE 0x2E
#define GPIOG_BASE 0x34
#define GPIOF_BASE 0x31

unsigned char GPIO_PinRegister(volatile unsigned char *baseAddress, unsigned char pin);
unsigned char GPIO_PinRead(unsigned char pinHandler);
unsigned char GPIO_ReadFromRegister(unsigned char pinHandler);
void fillDebaunsingData(void);

void Timer_Init(unsigned int freq);

unsigned char forwardLeftSensor, backwardLeftSensor, forwardRightSensor, backwardRightSensor,jumper;
unsigned char carpetsReleased, changeSides, jumper, checkSensor;
unsigned char matchIsStarted(void);

void systemInit(void);
int jumperCheck(void);
unsigned long getSystemTime(void);

void servo_init(unsigned int f_pwm);
void servo_position(unsigned char dutyCycle);

#endif
