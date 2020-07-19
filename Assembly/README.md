# Descrição



* Considere um sistema de semáforos em uma travessia de uma avenida contendo
um semáforo de veículos e um semáforo de pedestres.

* Além dos indicadores luminosos, o semáforo de pedestres possui um botão para
solicitação de abertura do semáforo.
# Ex:

![Farol_desligado](https://user-images.githubusercontent.com/67662041/87883430-b92e5c00-c9dd-11ea-9c54-4ba12b217516.png)

* O semáforo para os veículos possui os indicadores verde, amarelo e vermelho. 

* O semáforo para os pedestres possui semente os indicadores verde e vermelho.

# Operação

- [ ] O semáforo de veículos opera ficando verde por 30 segundos, amarelo por 5
segundos, vermelho por 10 segundos e então o ciclo se repete.
- [ ] Quando o botão no semáforo de pedestres é pressionado, o sinal amarelo do 
semáforo de veículos é ativado e permanece ativo por 5 segundos. 
- [ ] Em seguida o sinal vermelho do semáforo de veículos é ativado e mantido 
ativo por 10 segundos. 
- [ ] O semáforo de pedestres deve ter o sinal verde ativo somente enquanto o sinal vermelho do
semáforo de veículos estiver ativo, devendo permanecer em vermelho em todas as outras situações.

![Operação](https://user-images.githubusercontent.com/67662041/87883491-1aeec600-c9de-11ea-8c28-c768a6d11869.png)

# Circuito necessário usando o PIC16F887.

![Semaforo](https://user-images.githubusercontent.com/67662041/87883979-7c646400-c9e1-11ea-8c64-24cc08968760.png)

[Semaforo.PDF](https://github.com/simpleCod3r/PIC16F887-EXs/files/4944520/Semaforo.PDF)



# Escreva o firmware em assembly, considerando o circuito do item anterior.
