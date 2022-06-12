<h1 align="center">PROPOSTA DE TRABALHO DE CONCLUSÃO DE CURSO (TCC)</h1>

<h2 align="center">PITCH</h2>
Ola meu nome é augusto, sendo a segurança e privacidade do usuario na internet um topico cada vez mais importante nos dias atuais.

justamente pelo grande aumento do uso de computadores com internet e muitos serviços sendo disponibilizados online,
como exemplo os comunicadores instantaneos: whatsapp, telegram, messenger...

juntamente com o aumento do uso de internet tbm tem aumento o numero de computadores infectados por malwares, tendo um estudo da Kingsoft de 2016 mostrando que em média 2-5 milhões de computadores são infectados por dia

atualmente sabemos que esses comunicadores instantaneos utilizam criptografia entre um dispositivo e outro, porem não podem garantir que o dispositivo que recebeu ou enviou a mensagem já não esteja infectado por um malware...

podendo esse malware saber a mensagem que o usuario vai enviar antes mesmo dele precionar ENTER com a utilização de um keylogger ou ate mesmo gravando a tela do usuario e enviando para o hacker.

Minha proposta busca uma solução para isso.
Podemos com a utilização de um arduino conectado ao computador criar um middleware entre um teclado externo e o computador
para realizar a criptografia de mensagems que precisam realmente ser seguras e privadas...

O arduino receberia a entrada de dados do usuario atraves do teclado e realizaria uma criptografia na mensagem antes mesmo que ela seja realmente digitada no computador, podendo ele visualizar e alterar a mensagem original atraves de um display também conectado ao arduino

e a outra ponta que receberia essa mensagem também teria que ter um mesmo dispositivo, 
porem no caso de quem recebe a mensagem existiria um programa em que você cola a mensagem recebida e envia para o arduino para que o mesmo realize a descriptografia da mensagem e mostre a mensagem original também atraves do display.

<h2 align="center">ANOTACÕES</h2>

Yubico

https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries

https://forum.arduino.cc/t/liquidcrystal_i2c-arduino-due/519260

http://www.armlearning.com/code/arduino-due/arduino-due-i2c-lcd-example.php#google_vignette

### keyMap abnt2 

https://www.hackeduca.com.br/ligando-um-teclado-ps2-ao-arduino/