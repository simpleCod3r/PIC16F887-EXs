#include<xc.h>
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

int adc = 0;
uint16_t timer1_value = 15535;
uint8_t flag = 0;
void interrupt ISR(void)
	{
		if(PIR1bits.TMR1IF == 1)
			{
				PIR1bits.TMR1IF = 0;
				TMR1H = (uint8_t) (timer1_value >> 8);
				TMR1L = (uint8_t) (timer1_value);	
				flag = 1;
			}
	}

int main(void)
{
	//setup
	TRISC = 0;
	TRISD = 0;
	TRISA = 0b00000001;
	ANSEL = 0x00000001;
	ANSELH = 0X00;
	
	//TMR1 = 55536 -> 0xD8F0
	TMR1H = (uint8_t) (timer1_value >> 8);
	TMR1L = (uint8_t) (timer1_value);
	//T1CON -> CLK INTERNO, prescaler 1:1, T1 ON
	T1CON = 0b00010001;
	PIR1bits.TMR1IF = 0;
	PIE1bits.TMR1IE = 1;
	INTCONbits.PEIE = 1;
	//ADC -> ch0, fosc/4 
	ADCON0 = 0b01000001;
	ADCON1bits.ADFM = 1;	//alinhado a direita
	ADCON1bits.VCFG1 = 0;	//Ref- = VSS
	ADCON1bits.VCFG0 = 0;	//Ref+ = VCC
	__delay_ms(10);

	INTCONbits.GIE = 1;

	//Loop
	while(1)
	{
		if(flag == 1)
		{
			flag = 0;
			//PORTA ^= 0x01;
			ADCON0bits.GO = 1; //start
			while(ADCON0bits.GO == 1);
			adc = ADRESH<<8 + ADRESL;
			adc = adc*0.004887585;		//Converte para 0a5V
			PORTC = ADRESL;
			PORTD = ADRESH;
			
		}		

	}

}