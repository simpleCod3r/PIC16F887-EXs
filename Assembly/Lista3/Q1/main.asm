	include <p16f887.inc>
	list p=16f887

	__config _CONFIG1, 0x2FF4
	__config _CONFIG2, 0x3FFF

;Variáveis Global

	cblock 0x20
		k
	endc

	org 0x00
	goto Setup

	org 0x04
	retfie

Setup: 
	movlw 0x00
	movwf k
	bsf STATUS, RP0 ;Vai pro banco 1
	movlw 0x00
	movwf TRISB		;Define PORTB saída
	
	bsf STATUS, RP1 ;Vai pro banco 3
	movlw 0x00
	movwf ANSELH		;Define saída digital
	
	bcf STATUS, RP1
	bcf STATUS, RP0 ;Retorno ao banco 0

 	movlw 0xFF
	movwf PORTB
	call Delay_1s

Loop_20:
	incf k
	movlw 0xFF		
	subwf PORTB, W	;Compara aceso
	btfsc STATUS, Z	;Se aceso
	call Inverte		;Apaga
	movlw 0x00	
	subwf PORTB, W	;Compara apagado
	btfsc STATUS, Z	;Se apagado
	call Inverte		;Acende
	movlw 0x14		;Move valor 20 p/ W
	subwf k, W		;Compara k com W
	btfss STATUS, Z	;Testa resultado comparação
	goto Loop_20	;Volta pro loop se k<20
	movlw 0x55
	movwf PORTB
	goto Main_Loop	;Vai pra main se k=20
	
	
Main_Loop:
	call Inverte
	goto Main_Loop

Delay_1s:
	nop
	return
Delay_200ms:
	nop
	return
Inverte: 
	movlw 0xFF
	xorwf PORTB
	call Delay_200ms
	return

end
