	include <p16f887.inc>
	list p=16f887

	__config _CONFIG1, 0x2FF4
	__config _CONFIG2, 0x3FFF

	org 0x00
	goto Setup
	
	org 0x04
	retfie

Setup:
	bsf STATUS, RP0		;Bank 1
	movlw 0x00
	movwf TRISB			;Output
	
	;config TMR0
	bcf OPTION_REG, T0CS
	bsf OPTION_REG, PSA
	
	bcf STATUS, RP0		;Bank 0
	bcf STATUS, RP1
	movlw 0x01
	movwf PORTB
Loop:
	movlw .166
	movwf TMR0
	bcf INTCON, T0IF
	btfss INTCON, T0IF
	goto $ - 1
	call Inverte
	goto Loop

Inverte:
	movf PORTB, W
	xorlw 0x01
	movwf PORTB
	return

END
