  
	include <p16f887.inc>
	list p=16f887

	__config _CONFIG1, 0x2FF4
	__config _CONFIG2, 0x3FFF

	#define SIZEOF .14

;Variáveis Global
	cblock 0x20
	vetor:SIZEOF
	vetor_index
	aux
	a
	c
	i
	endc
	
	org 0x00
	goto Setup
	
	org 0x04
	retfie

Setup:
	clrf aux
	clrf a
	movlw 0x01
	movwf c
	clrf i
	clrf vetor_index
	clrf vetor
	movlw 0x00
	movwf 0x20
	movlw 0x01
	movwf 0x21
	movlw 0x02
	movwf vetor_index

Loop:
	movf a, W
	addwf c, W
	movwf aux
	call Armazena
	movf c, W
	movwf a
	movf aux, W
	movwf c
	incf i
	movlw .12
	subwf i, w
	btfss STATUS, Z
	goto Loop
	nop

;-----Armazena--------
;Argumento: aux
Armazena: 
	bcf STATUS, IRP ;banco 0 ou 1
	movlw vetor
	movwf FSR
	movf vetor_index, W
	addwf FSR, F
	movf aux, W
	movwf INDF
	incf vetor_index, F
	return

END
