/*
      |----------------UNIVERSIDADE FEDERAL DE ITAJUBÁ----------------|
      |--------------------------Regime - RTE-------------------------|
      |---------------Lista disciplina microcontroladores ------------|
      |--------------------------Atividade 3--------------------------|
      
      Autor: Rodrigo Fernandes Pinto 
      Registro Acadêmico: 30695							*/


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

//VARIAVEIS GLOBAL
uint8_t flag = 0x00;
uint8_t cnt = 0x00;

void interrupt ISR(void)				//Interrupt Service Routine
	{
		if(INTCONbits.INTF == 1)		// Interrupção externa por pressionamento de botão INT/RB0
			{			
			   INTCONbits.INTF = 0;
			   flag = 1;			// Dispara incremento
			}
	}
	
void incPWM()					//Função de incremento
	{
		uint8_t duty_10p = 16;	 	// Aproximadamente 10% do preríodo
		CCPR1L += duty_10p;
		cnt++;
		if(cnt == 10)			// Se Duty chega a 100% 
			{
			   CCPR1L = 0b00000001;		// Reinicializa os MSbs 
			   cnt=0;
			}
	}

void main(void)
 {
	 //setup
	TRISA = 0x00; 		// Define PORTA saídas
	TRISB = 0b00000001; 	// Define RB0 entrada 
	PORTB = 0x00;
	TRISC =0x00;
	
	ANSELH = 0x00;		// Entradas digitais
    
	// Configura interação com botão
	INTCONbits.INTE = 1; 		// Habilita interrupção externa
	INTCONbits.PEIE = 1; 		// Habilita interrupção de periféricos
	OPTION_REG = 0b11000000;	// Desabilita pull-up de PORTB, Define borda de subida
    
	// PWM
	 CCP1CON = 0b00001100; 		// PWM: Single output, P1C active HIGH
	 CCPR1L = 0b00000001;		// MSbs do duty cycle.
    
	 // TIMER2 PRESCALER
         PR2 = 166;			// Valor de comparação com TMR2 para 1500Hz de frequência no PWM
	 T2CON = 0b00000101;  		// TMR2ON, PS 1:4
	 
	INTCONbits.GIE = 1;		// Habilita interrupção global
	
	while(1)
	{
		      if(flag == 1)
		{
			flag = 0;
			incPWM();			// Incrementa 10% de Duty Cycle
		}
	}
 }
