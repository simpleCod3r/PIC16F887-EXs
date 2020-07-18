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
	movwf w_temp
	movf STATUS, W
	movwf status_temp
	;Processa
	btfss INTCON, T0IF
	goto IntExit
	bcf INTCON, T0IF
	movlw .99			;valor original 69 (255 - t/(Tinst*PS)
	movwf TMR0
IntExit:
	;restaurar resgistradores
	movf status_temp, W
	movwf STATUS
	swapf w_temp, F
	swapf w_temp, W
	retfie

Setup:
	bsf STATUS, RP0		;Bank 1
	bcf OPTION_REG, T0CS
	bcf OPTION_REG, PSA
	bsf OPTION_REG, PS2
	bsf OPTION_REG, PS1
	bsf OPTION_REG, PS0	;PS = 1:256

	bcf STATUS, RP0		;Bank 0
	bcf STATUS, RP1
	;Config tmr0 interrupt
	movlw .99
	movwf TMR0
	bcf INTCON, T0IF
	bsf INTCON, T0IE
	bsf INTCON, GIE
Loop:
	goto Loop

END
