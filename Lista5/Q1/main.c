/*
|-----------------UNIVERSIDADE FEDERAL DE ITAJUBA-----------------|
|---------------------------Regime RTE----------------------------|
|---------------Lista disciplina microcontroladores --------------|
|-----------------------Lista 5 - Questão 1-----------------------|
      
      Autor: Rodrigo Fernandes Pinto 
      Registro Academico: 30695					            	           */
      
#include<xc.h>
#include<stdio.h>

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

int main(void)
{
	//setup
	int k=0;
	TRISB = 0x00; // Saidas
	ANSEL = 0x00; // Digitais PORTA
	ANSELH = 0x00;// Digitais PORTB
		
	PORTB = 0xFF; // Acende leds inicio
	__delay_ms(1000);

	// Rotina de inicialização
	while(k<20)
	{
		k++;
		if(PORTB == 0xFF)
		{
				PORTB = 0x00;
				__delay_ms(200);
		}
		else if(PORTB == 0x00)
		{
				PORTB=0xFF;
				__delay_ms(200);
		}
	}
	PORTB = 0x55;
	//LOOP
	while(1)
	{
		PORTB = PORTB ^ 0xFF; // Alterna Leds
		__delay_ms(200);
	}
}
