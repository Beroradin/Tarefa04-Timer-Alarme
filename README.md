# ✨ Tarefa04-Timers-Alarme
<p align="center"> Repositório dedicado a Tarefa 04 do processo de capacitação do EmbarcaTech que envolve temporizadores e alarmes na placa Raspberry Pi Pico W por meio da Placa BitDogLab.</p>

## :clipboard: Apresentação da tarefa

Para consolidar a compreensão dos conceitos relacionados ao uso de temporizadores no microcontrolador RP2040 e explorar as funcionalidades da placa de desenvolvimento BitDogLab, esta atividade propõe a implementação de um projeto prático envolvendo o controle de LEDs por meio de alarmes *one-shot*.

## :dart: Objetivos

- Compreender o funcionamento e a aplicação de temporizadores em microcontroladores;

- Utilizar alarmes *one-shot*;

- Manipular e controlar LEDs comuns (no caso da placa, LED RGB);

- Um botão aciona o funcionamento dos LEDs, em qual todos devem iniciar em nível lógico alto;

- Após o pressionar do botão, é chamado um alarme *one-shot* a cada 3 segundos para desligar um LED por vez, até que todos estejam em nível lógico baixo;

- Durante a sequência dos LEDs e seus alarmes, a sequência não pode ser inicializada novamente, deve-se aguardar acabar a sequência atual terminar para que seja chamada novamente.

## :books: Descrição do Projeto

Utiizou-se a placa BitDogLab (que possui o microcontrolador RP2040) para o controle de LEDs, esses por sua vez são acionados por meio de um botão, que aciona um alarme que em sequência aciona uma função (callback) que aciona outro alarme, até que todos os LEDs estejam desligados, cada alarme possui 3 segundos de espera para serem chamadas.
O funcionamento dos alarmes ocorrem por meio da API de Hardware *add_alarm_in_ms()* que opera de forma externa ao processamento central, não afetando o funcionamento do loop principal. O botão possui *debounce* por meio de *software*, melhorando sua utilização por parte do usuário. O programa é posteriomente testado na placa BitDogLab.

## :walking: Integrantes do Projeto

- Matheus Pereira Alves

## :bookmark_tabs: Funcionamento do Projeto

- Os LEDs são acionados por meio do botão, que também ativa um alarme. Este, por sua vez, acionará uma função auxiliar (callback);
- A função auxiliar chamará um alarme em sequência, isso ocorre até que todos os LEDs estejam desligados;
- O tempo de cada chamada de alarme é de 3 segundos (3000 milisegundos);
- O botão possui um *debounce* que funciona por meio de *pooling*, melhorando a usabilidade do programa.

## 🧮 Simulação do projeto

- É necessário ter o VScode instalado;
- É necessário ter o C/C++ e CMAKE instalados como extensão VScode;
- É necessário ter o Wokwi Simulator instalado como extensão do VScode e uma chave ativa;
- É necessário compilar o arquivo.c por meio da extensão oficial do Raspberry Pi Pico;
- Utilize o arquivo diagram.json para rodar a simulação.

## :camera: GIF mostrando o funcionamento do programa na placa BitDogLab
<p align="center">
  <img src=".github/alarme.gif" alt="GIF" width="411px" />
</p>

Na placa BitDogLab, é difícil visualizar a mudança dos estados dos LEDs devido ao uso do LED RGB e à compressão do GIF. No entanto, o funcionamento ocorre de forma semelhante à simulação: inicialmente, todos os LEDs estão em nível alto (resultando na cor branca). Após 3 segundos, o LED vermelho é desligado, enquanto os LEDs azul e verde permanecem em nível alto (resultando na cor ciano). Depois de mais 3 segundos, apenas o LED verde permanece em nível alto. Por fim, após mais 3 segundos, todos os LEDs estarão em nível baixo. Ressaltando que essas mudanças se devem ao uso de timers e alarmes.
