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
	bsf STATUS, RP0 ;vai pro banco 1
	movlw 0xFF
	movwf TRISB		;Define PORTB entrada
	movlw 0x00
	movwf TRISA		;Define PORTA saída
	bsf STATUS, RP1	;vai pro banco 3
	movlw 0x00
	movwf ANSELH	;Define entrada digital
	movlw 0x00
	movwf ANSEL

	bcf STATUS, RP1
	bcf STATUS, RP0

	movlw 0x00
	movwf cnt		;inicializa

Loop:
	call B1			;incrementa com aperto
	movlw 0xFF
	subwf cnt, W
	btfsc STATUS, Z
	call Acende
	goto Loop

B1:
	btfss PORTB, RB0
	goto B1
	incf cnt, F
	return	

Acende:
	movlw 0x01
	movwf PORTA
	call B2
	return	 

B2:
	btfss PORTB, RB1
	goto B2
	movlw 0x00
	movwf PORTA
	movlw 0x00
	movwf cnt
	return
END
