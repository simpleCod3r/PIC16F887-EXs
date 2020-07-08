/* 

O código a ser desenvolvido deve: 

* ~~Gerar um sinal PWM de frequência 2kHz~~; 
* Duty-cycle proporcional a tensão do potenciômetro conectado no pino RA1;
* O valor do duty-cycle será exibido nos dois displays de 7 segmentos do tipo catodo-comum conectados à porta D;
* Os displays são multiplexados, sendo um display para exibir dezenas e o outro as unidades;
* Os displays devem ser atualizados periodicamente com uma frequência de 60Hz;
* A cada período (aproximadamente 16,7ms), o display ativo deve ser selecionado a partir dos sinais de seleção conectados aos pinos RB0 e RB1.
 */

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
#include "display.h"
#include "adc_init.h"
#include "configs.h"


//VARIAVEIS GLOBAL
uint8_t  dez = 0, uni =0;
uint16_t duty = 0x00;
uint16_t timer1_value = 48535;
uint8_t flag = 0x00;
uint8_t cnt = 0x00;


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

	//TMR1 = 48536
	TMR1H = (uint8_t) (timer1_value >> 8);
	TMR1L = (uint8_t) (timer1_value); 

		//T1CON -> CLK INTERNO, prescaler 1:1, T1 ON
		T1CON = 0b00000001;
		PIR1bits.TMR1IF = 0; // Inicializa flag de interrupção em TMR1 em 0
		PIE1bits.TMR1IE = 1; // Habilita interrupção por estouro em TMR1


		//Config conversor A/D
		//ADC -> ch1, fosc/4 
		ADCON0 = 0b01000001;
		ADCON1bits.ADFM = 0;	// Alinhado a esquerda
		ADCON1bits.VCFG1 = 0;	// Ref- = VSS
		ADCON1bits.VCFG0 = 0;	// Ref+ = VCC
		__delay_ms(10);

		INTCONbits.PEIE = 1; // Habilita interrupçao de periféricos
		INTCONbits.GIE = 1;	// Habilita interrupção global
		

		// PWM
		CCP1CON = 0b00001100; 		// PWM: Single output, P1C active HIGH
		CCPR1L = 0X03;			// MSbs do duty cycle.

    
		// TIMER2 
    PR2 = 124;	// Valor de comparação com TMR2 para 2000Hz de frequência no PWM
		T2CON = 0b00000101;  			// TMR2ON, PS 1:4\
	
   // Write your code here
   while (1)
		{
					
								if(flag == 1)
						{	
								flag = 0;
								PORTB ^= 0x03;
								ADCON0bits.GO = 1; 		// Inicia a conversão
								while(ADCON0bits.GO == 1); 	// Epera o final da conversão
								//adc = (ADRESH<<2)+(ADRESL>>6);	// Armazena resultado da conversão em um int 16 bits pois o resultado é de 10 bits
								//CCPR1L  = ADRESH;
								duty = (uint16_t) ((ADRESH)*49e-2);		// Converte para 0 a 5V  			
								dez = duty/10;
								uni = duty%10;
								if(duty<100)
								{
										if(PORTB == 0x01)
											{
														PORTD = display[dez];
											}
											if(PORTB == 0x02)
											{
														PORTD = display[uni];
											}
								}
						}
				}      
 }
