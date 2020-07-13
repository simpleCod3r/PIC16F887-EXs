# Circuito

![Q1L3](https://user-images.githubusercontent.com/67662041/87201486-0ec78200-c2d5-11ea-9fd6-baa32a44ce8a.png)


Considerando o circuito, o firmware a ser desenvolvido, deve seguir as etapas: 

# ETAPAS

- [x] Assim que o microcontrolador for ligado, todos os LEDs devem ser ativados por um segundo.

- [x] Após um segundo, o programa entra em um loop e permanece nesse loop enquanto a variável k é menor que 20.

- [x] Dentro do loop, o estado de PORTB é monitorado. Se PORTB=0xFF, seu estado é invertido para 0x00 e vice versa. O LEDs devem permanecer 200ms em cada estado.

- [x] Quando o programa sair do loop, o estado de PORTB deve ser alterado para b’01010101’

- [x] E então o programa entra em um loop infinito. Os bits de PORTB devem ser invertidos a cada 200ms. 

---
The firmware to be developed, must:

* Once the microcontroller is turned on, all LEDs must be activated for one second.
* After one second, the program enters a loop and remains in that loop as long as the variable k is less than 20.
* Within the loop, the status of PORTB is monitored. If PORTB = 0xFF, its status is inverted to 0x00 and vice versa. The LEDs must remain 200ms in each state.
* When the program exits the loop, the state of PORTB must be changed to b’01010101’
* And then the program enters an infinite loop. The PORTB bits must be inverted every 200ms.
---

# Fluxograma de execução

![BPMN 2 0](https://user-images.githubusercontent.com/67662041/87200602-47665c00-c2d3-11ea-85e3-693d2079ac89.png)

[Fluxograma.pdf](https://github.com/simpleCod3r/PIC16F887-EXs/files/4905232/Fluxograma.pdf)
