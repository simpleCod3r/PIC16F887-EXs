/*
      |----------------UNIVERSIDADE FEDERAL DE ITAJUBÁ----------------|
      |--------------------------Regime - RTE-------------------------|
      |---------------Lista disciplina microcontroladores ------------|
      |--------------------------Prova 2--------------------------|
      
      Autor: Rodrigo Fernandes Pinto 
      Registro Acadêmico: 30695										*/

#include<xc.h>
#include<stdint.h>
#include<math.h>
#include<float.h>

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

//Frequência de Clock de 4MHz
#define _XTAL_FREQ 4000000
//INTERFACE 7SEG
uint8_t display[ ] = {		0x3F,
								0x06,
								0x5B,
								0x4F,
								0x66,
								0x6D,
								0x7D,
								0x07,
								0x7F,
								0x6F};


//VARIAVEIS GLOBAL
uint8_t  dez = 0x00, uni =0x00;
uint16_t duty = 0x00, timer1_value = 48535;
uint8_t flag = 0x00;

void interrupt ISR(void) // Interrupt Service Routine
{
		//Interrupção periódica com tempo calibrado para 17ms
		if(PIR1bits.TMR1IF == 1)
			{
				PIR1bits.TMR1IF = 0;
				TMR1H = (uint8_t) (timer1_value >> 8);
				TMR1L = (uint8_t) (timer1_value);	
				flag = 1;	// Dispara 
			}
	}

void main(void)
 {
		//setup  ENTRADA ADC
		TRISA = 0xFF; 	//PORTA definido como entrada
		ANSEL = 0xFF;	// Analógica
		PORTA = 0x00;// Inicializa para evitar embaralhamento

		//SELECAO DE DISPLAY 0x01 -> dezena 0x03 ->unidade
		TRISB = 0x00;						// saídas
		ANSELH = 0x00;
		PORTB = 0x01; 	// Inicializa display
		
		//setup SAIDA PWM
		TRISD = 0x00;							// Define PORTD como saída
		TRISC = 0x00;
		PORTC = 0x00;
		 PORTD=0x00;

	//TMR1 = 48536
	TMR1H = (uint8_t) (timer1_value >> 8);
	TMR1L = (uint8_t) (timer1_value); 

		//T1CON -> CLK INTERNO, prescaler 1:1, T1 ON
		T1CON = 0b00000001;
		PIR1bits.TMR1IF = 0; // Inicializa flag de interrupção em TMR1 em 0
		PIE1bits.TMR1IE = 1; // Habilita interrupção por estouro em TMR1


		//Config conversor A/D
		//ADC -> ch1, fosc/8 
		ADCON0 = 0b01000101; 							//está checkado e correto 22:15
		ADCON1bits.ADFM = 0;	// Alinhado a esquerda
		ADCON1bits.VCFG1 = 0;	// Ref- = VSS
		ADCON1bits.VCFG0 = 0;	// Ref+ = VCC
		__delay_ms(10);

		INTCONbits.PEIE = 1; // Habilita interrupçao de periféricos
		INTCONbits.GIE = 1;	// Habilita interrupção global
		

		// PWM
		CCP1CON = 0b00001100; 		// PWM: Single output, P1C active HIGH
		CCPR1L = 0b00000001;			// MSbs do duty cycle.

    
		// TIMER2 
    PR2 = 124;	// Valor de comparação com TMR2 para 2000Hz de frequência no PWM
		T2CON = 0b00000101;  			// TMR2ON, PS 1:4
	
   // Write your code here
   while (1)
		{
					
								if(flag == 1)
						{	
								flag = 0;
								PORTB ^= 0x03;
								ADCON0bits.GO = 1; 		// Inicia a conversão
								while(ADCON0bits.GO == 1); 	// Epera o final da conversão
								CCPR1L  = ADRESH*0.5;
								duty = (((ADRESH<<2)+(ADRESL>>6))*0.097751) - 1;		// Converte para 0 a 99%		
								dez = duty/10;
								uni = duty%10;
								if(duty<100)
								{
										if(PORTB == 0x01)
											{
														PORTD = display[dez];
											}
											else if(PORTB == 0x02)
											{
														PORTD = display[uni];
											}
								}
						}
				}      
 }
