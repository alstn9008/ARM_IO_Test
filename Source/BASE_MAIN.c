#include "board.h"
#include <stdio.h>
#include <pio/pio.h>
#include <aic/aic.h>
#include <dbgu/dbgu.h>
#include <utility\trace.h>
#include <cs8900a/cs8900a.h>
#include <pwmc/pwmc.h>


//LED Brightness degree
/* 
#define PWM_FREQUENCY 20000 //Hz
#define MAX_DUTY_CYCLE 50
#define MIN_DUTY_CYCLE 0
#define MAX_DUTY_CYCLE_LED2 
#define MIN_DUTY_CYCLE_LED2 0
#define CHANNEL_PWM_LED1 1
#define CHANNEL_PWM_LED2 2

#define PIN_PWMC_LED1  {LED1, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_B, PIO_DEFAULT}
#define PIN_PWMC_LED2  {LED2, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_PERIPH_B, PIO_DEFAULT}

const Pin pins[] = 
{
	PINS_DBGU,
	PIN_PWMC_LED1,
	PIN_PWMC_LED2
};

int main()
{
	//PIO setup
	PIO_Configure(pins, PIO_LISTSIZE(pins));

	//Enable PWM
	AT91F_PWMC_CfgPMC();
	
	//Clock setting
	PWMC_ConfigureClocks(PWM_FREQUENCY*MAX_DUTY_CYCLE, 0, BOARD_MCK);

	//Channel
	PWMC_ConfigureChannel(CHANNEL_PWM_LED1, AT91C_PWMC_CPRE_MCKA, 0, 0);
	PWMC_ConfigureChannel(CHANNEL_PWM_LED2, AT91C_PWMC_CPRE_MCKA, 0, 0);
	
	//Period
	PWMC_SetPeriod(CHANNEL_PWM_LED1, MAX_DUTY_CYCLE);
	PWMC_SetPeriod(CHANNEL_PWM_LED2, MAX_DUTY_CYCLE);

	//Duty cycle
	PWMC_SetDutyCycle(CHANNEL_PWM_LED1, 0);
	PWMC_SetDutyCycle(CHANNEL_PWM_LED2, 40);

	//Enable channel
	PWMC_EnableChannel(CHANNEL_PWM_LED1);
	PWMC_EnableChannel(CHANNEL_PWM_LED2);

	while(true)
	{

	}
	return 0;
}*/


//dot matrix

//row 0 3 5 8 9 12 14 15

#define ROW1 PA12
#define ROW2 PA2
#define ROW3 PA3
#define ROW4 PA10
#define ROW5 PA5
#define ROW6 PA9
#define ROW7 PA14
#define ROW8 PA15

#define COL1 PA4
#define COL2 PA1
#define COL3 PA6
#define COL4 PA0
#define COL5 PA11
#define COL6 PA7
#define COL7 PA13
#define COL8 PA8

volatile unsigned int ten_us_count = 0;

void HW_delay_10us(unsigned int ten_us)
{
	// special case
	if(ten_us == 0) return;

	// start time
	ten_us_count = 0;

	// enable PIT interrupt
	AT91F_PITEnableInt(AT91C_BASE_PITC);

	// wait for us
	while(ten_us_count < ten_us);

	
	// disable PIT interrupt
	AT91F_PITDisableInt(AT91C_BASE_PITC);
}

void Port_Setup()
{

	AT91F_PMC_EnablePeriphClock(AT91C_BASE_PMC, 1 << AT91C_ID_PIOA);

	//LED
	AT91F_PIO_CfgOutput( AT91C_BASE_PIOA, PORTA ); //output
	AT91F_PIO_CfgPullup( AT91C_BASE_PIOA, PORTA ); //pull-up
}

int main()
{
	//Port set-up
	Port_Setup();


	//loop
	while(true)
	{
		// ROW1
		rPIO_CODR_A = PORTA;
		rPIO_SODR_A =  COL1 | COL4 | COL5 | COL8;
		rPIO_SODR_A = ROW1;
		Delay(10);

		// ROW2
		rPIO_CODR_A = PORTA;
		rPIO_SODR_A = COL2 | COL3 | COL6 | COL7 ;
		rPIO_SODR_A = ROW2;
		Delay(10);
		
		// ROW3
		rPIO_CODR_A = PORTA;
		rPIO_SODR_A = COL2 | COL3 | COL4 | COL5 | COL6 | COL7 ;
		rPIO_SODR_A = ROW3;
		Delay(10);
		
		// ROW4
		rPIO_CODR_A = PORTA;
		rPIO_SODR_A = COL2 | COL3 | COL4 | COL5 | COL6 | COL7 ;
		rPIO_SODR_A = ROW4;
		Delay(10);
		
		// ROW5
		rPIO_CODR_A = PORTA;
		rPIO_SODR_A =  COL2 | COL3 | COL4 | COL5 | COL6 | COL7 ;
		rPIO_SODR_A = ROW5;
		Delay(10);
		
		// ROW6
		rPIO_CODR_A = PORTA;
		rPIO_SODR_A =  COL1 | COL3 | COL4 | COL5 | COL6 | COL8;
		rPIO_SODR_A = ROW6;
		Delay(10);
		
		// ROW7
		rPIO_CODR_A = PORTA;
		rPIO_SODR_A =  COL1 | COL2 | COL4 | COL5 | COL7 | COL8;
		rPIO_SODR_A = ROW7;
		Delay(10);
		
		// ROW8
		rPIO_CODR_A = PORTA;
		rPIO_SODR_A =  COL1 | COL2 | COL3 | COL6 | COL7 | COL8;
		rPIO_SODR_A = ROW8;
		Delay(10);	
	}

	return 0;
}

