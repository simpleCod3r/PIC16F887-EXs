include <p16f887.inc>
list p=16f887

__config _CONFIG1, 0x2FF4
__config _CONFIG2, 0x3FFF

;Variáveis Global

cblock 0x20
	cnt
endc

org 0x00
goto Setup

org 0x04
retfie

Setup: 
	bsf STATUS, RP0 ;Vai pro banco 1
	clrf TRISB		;Define PORTB saída
	
	bsf STATUS, RP1 ;Vai pro banco 3
	clrf ANSELH		;Define saída digital
	
	bcf STATUS, RP1
	bcf STATUS, RP0 ;Retorno ao banco 0

 	bsf PORTB
	call Delay_1s
	
Loop_20:
	movlw 0x14		;Move valor 20 p/ W
	subwf k, W		;Compara k com W
	btfsc STATUS, Z	;Testa resultado comparação
	goto Main_loop	;Vai pra main se k=20
	goto Loop_20	;Volta pro loop se k<20
Main_Loop:
	goto Main_Loop
Delay_1s:
	nop
	return
