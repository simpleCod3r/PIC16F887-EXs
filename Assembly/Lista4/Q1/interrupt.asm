	include <p16f887.inc>
	list p=16f887

	__config _CONFIG1, 0x2FF4
	__config _CONFIG2, 0x3FFF

	cblock
	w_temp
	status_temp
	endc

	org 0x00
	goto Setup
	
	org 0x04
	;Salva registradores
	movwf w_temp
	movf STATUS, W
	movwf status_temp
	;Processa
	btfss INTCON, T0IF
	goto IntExit
	bcf INTCON, T0IF
	movlw .156
	movwf TMR0
	movf PORTB, W
	xorlw 0x01
	movwf PORTB
IntExit:
	;restaurar resgistradores
	movf status_temp, W
	movwf STATUS
	swapf w_temp, F
	swapf w_temp, W
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
	
	;Config tmr0 interrupt
	movlw .156
	movwf TMR0
	bcf INTCON, T0IF
	bsf INTCON, T0IE
	bsf INTCON, GIE

	movlw 0x01
	movwf PORTB

Loop:
	goto Loop

END
