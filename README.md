<h1 align="center">PROPOSTA DE TRABALHO DE CONCLUSÃO DE CURSO (TCC)</h1>

<h2 align="center">Assista ao vídeo Demonstração</h2>

[![Watch the video](https://user-images.githubusercontent.com/32443720/201154283-ecf50440-0964-4207-ac31-1d5e1d04e25c.png)](https://youtu.be/Wa5P3EffBTg)

<h2 align="center">PITCH</h2>
Olá meu nome é augusto, sendo a segurança e privacidade do usuario na internet um topico cada vez mais importante nos dias atuais.

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

keyscrambler

https://www.techtudo.com.br/noticias/2011/06/novo-teclado-sem-fio-da-microsoft-com-sistema-de-criptografia.ghtml

https://forum.adrenaline.com.br/threads/review-teclado-mecanico-wireless-matias-secure-pro.527253/

### keyMap abnt2 

https://www.hackeduca.com.br/ligando-um-teclado-ps2-ao-arduino/

### teclas pyautogui
https://pyautogui.readthedocs.io/en/latest/keyboard.html#keyboard-keys

### display lcd ic2
https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library

### icon
https://icon-icons.com/pt/icone/para-os-olhos-oculto-invis%C3%ADvel/111380

### to do :
- [x] Renomear repo
- [x] Tornar publico
- [x] Refatorar programa python
- [x] criar banner repo git
- [x] permitir scrollar no visor (permitir voltar)
- [x] selecionar criptografia (rot47)
- [x] criptografar mensagem no modo encrypt
- [x] descriptografar mensagem no modo decrypt
- [ ] colocar todos os comentarios e variaveis em inglês
- [ ] fazer comandos compinados funcionar (ctrl + a)

### bugs a serem resolvidos
- [x] troca de modo do programa
- [x] decrypt not working
- [x] Quando clica varias vezes rapidamente esta escrevendo o texto invés de realizar a ação

<h2 align="center">Versão 1 funcional</h2>

![WhatsApp Image 2022-10-17 at 19 39 39](https://user-images.githubusercontent.com/32443720/196297172-9dbef4b7-01c0-4d2c-a54f-4283fcf06066.jpeg)

<h2 align="center">Versão 2 sendo construida</h2>

![20221006_002124](https://user-images.githubusercontent.com/32443720/196296975-0958eafe-7150-4eb9-bbb1-8e1962529ded.jpg)

![20221002_005254](https://user-images.githubusercontent.com/32443720/196297288-4ea1ee3e-e428-42bd-89d1-8bbc81499b90.jpg)
