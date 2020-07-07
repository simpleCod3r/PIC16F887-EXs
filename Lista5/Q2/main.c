/*
|-----------------UNIVERSIDADE FEDERAL DE ITAJUBA-----------------|
|-------------------------Regime RTE--------------------------|
|-------------------Lista disciplina microcontroladores --------------------|
|------------------------Lista 5 - Questão 2------------------------|
      
      Autor: Rodrigo Fernandes Pinto 
      Registro Academico: 30695					            	                  	                       */
#include<xc.h>
#include<stdint.h>
#include<stdbool.h> 

//Configuration bits: CONFIG1 = 0x3FF4
#pragma config CONFIG1 = 0x3FF4

//Configuration bits: CONFIG2 = 0x3FFF
#pragma config BOR4V=BOR40V
#pragma config WRT=OFF

#define _XTAL_FREQ 4000000

//VARIAVEIS GLOBAL
uint8_t  cnt=0x00;
//Identificador de botão
uint8_t aux = 0x00;
//Flag aperto Botão
uint8_t flagB1 = 0;

int b1=0,b2=0;
void interrupt ISR(void) //Interrupt Service Routine - lida sempre que uma interrupção ocorre
	{
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
	
	//Habilita interrupção global
	INTCONbits.GIE = 1;
	

	//Loop principal
	while(1)
	{
		
			if(flagB1)
		{
			flagB1=0;
			while(cnt<0xFF)
{
			   
			   if(aux == 1) //Se o botao pressionado for RA0
			   {
			      aux=0x00;
				  cnt++;
			   }
}	
				PORTAbits.RA0 = 1;
			   if(aux == 2)  //Se o botao pressionado for RA1
			   {
			      aux=0x00;
			      cnt = 0x00;
				  PORTAbits.RA0 = 0;
			   }

		}

	}
	
}
