/*
      |----------------UNIVERSIDADE FEDERAL DE ITAJUBÁ----------------|
      |--------------------------Regime - RTE-------------------------|
      |---------------Lista disciplina microcontroladores ------------|
      |--------------------------Atividade 4--------------------------|
      
      Autor: Rodrigo Fernandes Pinto 
      Registro Acadêmico: 30695										*/

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
//Frequência de Clock de 4MHz
#define _XTAL_FREQ 4000000

//Variáveis Globais
uint16_t timer1_value = 15535;
uint8_t flagTimer = 0;
//Identificador de botão
uint8_t aux = 0x00;
//Flag aperto Botão
uint8_t flagB1 = 0;
uint8_t cnt = 0;

//Unidade e dezena Segundos
uint8_t uni_Seg =0;
uint8_t dez_Seg = 0;
//Unidade e dezena Minutos
uint8_t uni_Min =0;
uint8_t dez_Min = 0;
//Unidade e dezena Horas
uint8_t uni_Hora =0;
uint8_t dez_Hora = 0;

void interrupt ISR(void) //Interrupt Service Routine - lida sempre que uma interrupção ocorre
	{
	       // Interrupção gerada pelo estouro do contador de TMR1 - Configurado em 200ms
		if(PIR1bits.TMR1IF == 1)
			{
				PIR1bits.TMR1IF = 0;					// limpa interrupt flag de TMR1
				TMR1H = (uint8_t) (timer1_value >> 8);		// reseta o valor dos MSbs do contador para valor configurado
				TMR1L = (uint8_t) (timer1_value);			// reseta o valor dos LSbs do contador para valor configurado
				flagTimer = 1;							// Dispara tic-tac
			}
	       // Interrupção gerada por aperto de tecla em PORTB
		if(INTCONbits.RBIF == 1)
			{
			      INTCONbits.RBIF = 0;					// limpa interrupt flag de TRISB 
			      aux = PORTB;							// Lê botão pressionado e desfaz o match permitindo nova interrupção index 3.4 datasheet.
			      flagB1 = 1;							//Dispara ajustes
			}
	}


int main(void)
{
	//setup
	TRISA = 0x00; //Define PORTA saídas
	PORTA = 0x00; //Inicializa saídas de teste = 0;
	TRISB = 0x0F;	//Define LSbs PORTB entrada
	IOCB=0x0F;	//Habilita LSbs PORTB para Interrupt-on-change
	PORTB = 0x00; //Inicializa PORTB = 0 para evitar embralhamento de dados
	ANSEL = 0x00;	//Entradas digitais
	ANSELH = 0X00;
	
	//Config Botões de ajuste 
	INTCONbits.PEIE = 1; //Habilita interrupção de periféricos
	INTCONbits.RBIE = 1; //Habilita interrupção por alteração em PORTB
	INTCONbits.RBIF = 0; //Inicializa flag = 0;
	
	OPTION_REG = 0b11000000;//Desabilita pull-up de PORTB, Define borda de subida
	
	//TMR1 = 15536 -> 0x3CAF  200ms
	TMR1H = (uint8_t) (timer1_value >> 8);
	TMR1L = (uint8_t) (timer1_value);

	//T1CON -> CLK INTERNO, prescaler 1:4, T1 ON
	T1CON = 0b00100001;
	PIR1bits.TMR1IF = 0; //Inicializa flag = 0;
	PIE1bits.TMR1IE = 1; //Habilita interrupção por estouro em TMR1
		
	//Habilita interrupção global
	INTCONbits.GIE = 1;

	//Loop
	while(1)
	{
		// Ajustes de HORA ou MINUTO
		if(flagB1)
		{
			   flagB1=0;
			   if(aux == 1) //Se o botão pressionado for RA0
			   {
			      aux=0x00;
			      uni_Min++; //Incrementa 1 em minutos
			      //PORTAbits.RA0 =  !PORTAbits.RA0 ;
			   }
			   else if(aux == 4)  //Se o botão pressionado for RA2
			   {
			      aux=0x00;
			      uni_Hora++; 	//Incrementa 1 em horas
			      //PORTAbits.RA1 =  !PORTAbits.RA1;
			   }
		}
			
		//COMEÇA RELÓGIO
			//Contador universal de 1 segundo.
			if(flagTimer)
			{
				 flagTimer = 0;
				 cnt++;  			// 1/5 segundos ou 200ms
			}
			if(cnt == 5)
			{
				 uni_Seg++;
				 cnt = 0;
			} //Fim Contador universal de 1 segundo
			
			//SEGUNDOS
			if(uni_Seg == 10)
			{	
				dez_Seg++;
				uni_Seg =0;
			}
			if(dez_Seg == 6)
			{
				uni_Min++;
				dez_Seg = 0;
			} //Fim segundos
			
			//MINUTOS
			if(uni_Min==10)
			{
				dez_Min++;
				uni_Min = 0;
			}
			if(dez_Min == 6)
			{
				uni_Hora++;
				dez_Min = 0;
			} //Fim minutos
			
			//HORAS
			if(uni_Hora==10)
			{
				 dez_Hora++;
				 uni_Hora=0;
			}
			if(dez_Hora == 2 && uni_Hora == 4)
			{
				uni_Hora = 0;
				dez_Hora = 0;
			} //Fim horas
			
		//TERMINA RELÓGIO
	}
}