//Professor, saliento que este código foi feito com o auxílio do chat.
//Mesmo depois de uma semana tentando ainda não sei se o botão de reset atende o esperado.


#include <Arduino.h>
#include <Bounce2.h>

const byte ledPins[] = {14, 15, 16, 17};
const byte buttonPins[] = {4, 5, 12, 13};
const byte buzzerPin = 18;         // Pino do Buzzer
const byte resetButtonPin = 2;     // Pino do Botão de Reset

#define MAX_GAME_LENGTH 100
byte gameSequence[MAX_GAME_LENGTH] = {0};
byte gameIndex = 0;

Bounce resetButtonDebouncer = Bounce();

void setup() {
  Serial.begin(9600);

  // Configuração dos pinos
  for (byte i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  pinMode(buzzerPin, OUTPUT);         // Configura o pino do Buzzer como saída
  pinMode(resetButtonPin, INPUT_PULLUP);  // Configura o pino do botão de reset como entrada pull-up
  resetButtonDebouncer.attach(resetButtonPin);
  resetButtonDebouncer.interval(10);  // Ajuste este valor conforme necessário
  randomSeed(analogRead(A0));
}

void lightLedAndPlayTone(byte ledIndex, int frequency) {
  // Acende o LED e ativa o Buzzer
  digitalWrite(ledPins[ledIndex], HIGH);
  tone(buzzerPin, frequency);
  delay(300);
  // Desliga o LED e desativa o Buzzer
  digitalWrite(ledPins[ledIndex], LOW);
  noTone(buzzerPin);
}

void playSequence() {
  // Reproduz a sequência atual do jogo
  for (int i = 0; i < gameIndex; i++) {
    byte currentLed = gameSequence[i];
    int frequency = 1000 + i * 200;  // Frequência diferente para cada LED
    lightLedAndPlayTone(currentLed, frequency);
    delay(50);
  }
}

byte readButtons() {
  // Lê os botões e retorna o índice do botão pressionado
  while (true) {
    for (byte i = 0; i < 4; i++) {
      byte buttonPin = buttonPins[i];
      if (digitalRead(buttonPin) == LOW) {
        return i;
      }
    }
    delay(1);
  }
}

void restartGame() {
  // Reinicia o jogo
  Serial.println("Game restarted!");
  gameIndex = 0;
  // Desliga todos os LEDs
  for (byte i = 0; i < 4; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}

void loop() {
  // Atualiza o debouncer do botão de reset
  resetButtonDebouncer.update();

  // Verifica se o botão de reset foi pressionado
  if (resetButtonDebouncer.fell()) {
    // Adiciona um atraso para debounce e evita falso acionamento
    delay(500);
    // Chama a função de game over e reinicia o jogo
    gameOver();
    restartGame();
  }

  // Gera um novo evento na sequência do jogo
  gameSequence[gameIndex] = random(0, 4);
  gameIndex++;

  // Limita o comprimento máximo da sequência
  if (gameIndex >= MAX_GAME_LENGTH) {
    gameIndex = MAX_GAME_LENGTH - 1;
  }

  // Reproduz a sequência atual
  playSequence();

  // Verifica se a sequência do jogador está correta
  if (!checkUserSequence()) {
    // Se incorreta, chama a função de game over e reinicia o jogo
    gameOver();
    restartGame();
  }

  // Aguarda antes de iniciar o próximo evento
  delay(300);
}

bool checkUserSequence() {
  // Verifica se a sequência do jogador coincide com a sequência do jogo
  for (int i = 0; i < gameIndex; i++) {
    byte expectedButton = gameSequence[i];
    byte actualButton = readButtons();
    int frequency = 1000 + i * 200;  // Frequência diferente para cada botão
    lightLedAndPlayTone(actualButton, frequency);
    if (expectedButton != actualButton) {
      return false;
    }
  }
  return true;
}

void gameOver() {
  // Exibe a mensagem de game over e reinicia o jogo
  for (byte i = 0; i < 4; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
  Serial.print("Game over! Your score: ");
  Serial.println(gameIndex - 1);
  restartGame();
  delay(1000);  // Aguarda um pouco antes de iniciar um novo jogo
}
