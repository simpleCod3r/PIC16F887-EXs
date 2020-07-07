Para esse circuito, desenvolva um firmware em C que opera da seguinte forma:

* Assim que o microcontrolador for ligado, todos os LEDs devem ser ativados por um segundo.
* Após um segundo, o programa entra em um loop e permanece nesse loop enquanto a variável k é menor que 20.
* A variável é incrementada a cada iteração. Dentro do loop, o estado de PORTB é monitorado.
* Se PORTB=0xFF, seu estado é invertido para 0x00 e vice versa. O LEDs devem permanecer 200ms em cada estado.
* Quando o programa sair do loop, o estado de PORTB deve ser alterado para b’01010101’ e então o programa entra 
  em um loop infinito. Os bits de PORTB devem ser invertidos a cada 200ms.
