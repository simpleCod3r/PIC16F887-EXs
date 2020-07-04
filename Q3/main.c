#include <xc.h>
#include<stdint.h>
//Configuration bits: CONFIG1 = 0x3FF4

#pragma config FOSC = INTRC_NOCLKOUT
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config MCLRE = ON
#pragma config CP = OFF
#pragma config CPD = OFF
#pragma config BOREN = ON
#pragma config IESO = ON
#pragma config FCMEN = ON
#pragma config LVP = OFF
#pragma config DEBUG = OFF

//Configuration bits: CONFIG2 = 0x3FFF
#pragma config BOR4V=BOR40V
#pragma config WRT=OFF

#define _XTAL_FREQ 4000000

uint8_t flag = 0;

uint8_t duty_10p = 16;

void interrupt ISR(void)
	{
		if(INTCONbits.INTF == 1)
			{			
			   INTCONbits.INTF = 0;
			   flag = 1;
			}
	}

void main(void)
 {
	//setup
	TRISA = 0x00; //Define PORTA saídas
	TRISB = 0b00000001; //Define RB0 entrada 
	TRISC =0x00;
	ANSEL = 0x00;	//Entradas digitais
	ANSELH = 0x00;
	INTCONbits.INTE = 1; //Habilita interrupção externa
	INTCONbits.PEIE = 1; //Habilita interrupção de periféricos
	OPTION_REG = 0b11000000;//Desabilita pull-up de PORTB, Define borda de subida
	
	//PWM
	CCP1CON = 0b00001100; //PWM: Single output, P1C active HIGH
	CCPR1L = 0b00000000;//MSbs do duty cycle.
	
	//TIMER2 PRESCALER
    PR2 = 166;
	T2CON = 0b00000101;  //TMR2ON, PS 1:4
	
	//Habilita interrupção global
	INTCONbits.GIE = 1;
	
	//Loop
	while(1)
	{
			if(flag == 1)
		{
			flag = 0;
			PORTA ^= 0x01;
			CCPR1L += duty_10p;
		}
	}
 }