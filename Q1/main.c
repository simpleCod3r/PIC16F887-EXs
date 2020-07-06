/*
      |----------------UNIVERSIDADE FEDERAL DE ITAJUBÁ----------------|
      |--------------------------Regime - RTE-------------------------|
      |---------------Lista disciplina microcontroladores ------------|
      |--------------------------Atividade 1--------------------------|
      
      Autor: Rodrigo Fernandes Pinto 
      Registro Acadêmico: 30695							*/
      
#include<xc.h>
#include<stdint.h>
#include<math.h>

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

#define _XTAL_FREQ 4000000  // Clock de 4MHz

//VARIAVEIS GLOBAL
uint16_t adc = 0;
float tensao=0.0;
uint16_t timer1_value = 15535;
uint8_t flag = 0x00;

void interrupt ISR(void) // Interrupt Service Routine
	{
		//Interrupção periódica com tempo calibrado para 100ms
		if(PIR1bits.TMR1IF == 1)
			{
				PIR1bits.TMR1IF = 0;
				TMR1H = (uint8_t) (timer1_value >> 8);
				TMR1L = (uint8_t) (timer1_value);	
				flag = 1;	// Dispara leitura
			}
	}

int main(void)
{
	//setup
	TRISC = 0x00;		//PORTC como saídas para validação
	TRISD = 0x00;		//PORTD como saídas para validação
	TRISA = 0b00000001; //PORTAbits.RA0 definido como entrada
	ANSEL = 0b00000001;	//Entrada em PORTAbits.RA0 tipo analógica
	
	//TMR1 = 15536 -> 0x3CAF
	TMR1H = (uint8_t) (timer1_value >> 8);
	TMR1L = (uint8_t) (timer1_value);
	
	//T1CON -> CLK INTERNO, prescaler 1:2, T1 ON
	T1CON = 0b00010001;
	PIR1bits.TMR1IF = 0; // Inicializa flag de interrupção em TMR1 em 0
	PIE1bits.TMR1IE = 1; // Habilita interrupção por estouro em TMR1
	INTCONbits.PEIE = 1; //Habilita interrupçao de periféricos
	
	//ADC -> ch0, fosc/4 
	ADCON0 = 0b01000001;
	ADCON1bits.ADFM = 0;	//alinhado a esquerda
	ADCON1bits.VCFG1 = 0;	//Ref- = VSS
	ADCON1bits.VCFG0 = 0;	//Ref+ = VCC
	__delay_ms(10);

	INTCONbits.GIE = 1;	// Habilita interrupção global

	//Loop
	while(1)
	{
		if(flag == 1)
		{
			flag = 0;
			//PORTA ^= 0x01;
			ADCON0bits.GO = 1; // Inicia a conversão
			while(ADCON0bits.GO == 1); // Epera o final da conversão
			adc = (ADRESH<<2)+(ADRESL>>6); //Armazena resultado da conversão em um int 
			tensao = adc*0.00488;	// Converte para 0 a 5V  			
			PORTC = ADRESH<<2;	// Interface de teste MSbs do resultado da conversão A/D
			PORTD = ADRESL>>6;	// Interface de teste LSbs do resultado da conversão A/D
			
		}		

	}

}
