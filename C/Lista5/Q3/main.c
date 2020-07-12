/*
|-----------------UNIVERSIDADE FEDERAL DE ITAJUBA-----------------|
|----------------------------Regime RTE---------------------------|
|--------------Lista disciplina microcontroladores ---------------|
|----------------------Lista 5 - Questão 3------------------------|
      
      Autor: Rodrigo Fernandes Pinto 
      Registro Academico: 30695					            	             */

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

#include <xc.h>
#include <stdint.h>
uint16_t a = 0, b = 1, aux;
void main(void)
 {
     for(int i = 0; i < 14; i++)
  {
    aux = a + b;
    a = b;
    b = aux;
  }
 }
