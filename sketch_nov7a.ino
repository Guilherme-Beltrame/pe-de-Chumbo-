/*
 * CÓDIGO FINAL - ROBÔ CONTROLADO POR BLUETOOTH
 * * Este código ouve os comandos enviados por um aplicativo
 * de controle via Bluetooth (como o "Bluetooth RC Controller")
 * e controla os motores de acordo.
 * * Conexões:
 * --- L298N ---
 * Arduino D4 -> L298N IN1
 * Arduino D5 -> L298N IN2
 * Arduino D6 -> L298N IN3
 * Arduino D7 -> L298N IN4
 * L298N EEP  -> Arduino 5V (MUITO IMPORTANTE!)
 * * --- Bluetooth HC-05/HC-06 ---
 * Bluetooth VCC -> Arduino 5V
 * Bluetooth GND -> Arduino GND
 * Bluetooth TX  -> Arduino D2 (RX do SoftwareSerial)
 * Bluetooth RX  -> Divisor de Tensão vindo do Arduino D3 (TX do SoftwareSerial)
 */

#include <SoftwareSerial.h>

// --- Define os pinos dos motores ---
// Motor A (Direito)
#define MA_IN1 4
#define MA_IN2 5
// Motor B (Esquerdo)
#define MB_IN3 6
#define MB_IN4 7

// --- Define os pinos para a comunicação Bluetooth ---
#define BT_RX_PIN 2 // Pino RX do Arduino (recebe do TX do Bluetooth)
#define BT_TX_PIN 3 // Pino TX do Arduino (transmite para o RX do Bluetooth)

// Cria uma "porta serial virtual" para o Bluetooth
SoftwareSerial btSerial(BT_RX_PIN, BT_TX_PIN);

// Variável para armazenar o comando recebido
char comando;

void setup() {
  // Inicia a comunicação com o computador (para debug)
  Serial.begin(9600);
  // Inicia a comunicação com o módulo Bluetooth
  btSerial.begin(9600);
  
  Serial.println("Robo pronto para receber comandos via Bluetooth!");

  // Configura todos os pinos de controle dos motores como SAÍDA
  pinMode(MA_IN1, OUTPUT);
  pinMode(MA_IN2, OUTPUT);
  pinMode(MB_IN3, OUTPUT);
  pinMode(MB_IN4, OUTPUT);

  // Garante que o robô comece parado
  parar();
}

void loop() {
  // Verifica se há algum dado vindo do Bluetooth
  if (btSerial.available()) {
    // Lê o caractere (comando) recebido
    comando = btSerial.read();
    Serial.print("Comando recebido: ");
    Serial.println(comando); // Mostra o comando no Serial Monitor

    // Executa a ação baseada no comando
    switch (comando) {
      case 'F': // Frente
        frente();
        break;
      case 'B': // Trás
        tras();
        break;
      case 'L': // Esquerda
        esquerda();
        break;
      case 'R': // Direita
        direita();
        break;
      case 'S': // Parar (Stop)
        parar();
        break;
      default: // Se receber qualquer outra coisa, para por segurança
        parar();
        break;
    }
  }
}

// --- Funções de Movimento (as mesmas do código de teste) ---

void frente() {
  digitalWrite(MA_IN1, HIGH); digitalWrite(MA_IN2, LOW);
  digitalWrite(MB_IN3, HIGH); digitalWrite(MB_IN4, LOW);
}

void tras() {
  digitalWrite(MA_IN1, LOW); digitalWrite(MA_IN2, HIGH);
  digitalWrite(MB_IN3, LOW); digitalWrite(MB_IN4, HIGH);
}

void direita() {
  digitalWrite(MA_IN1, LOW); digitalWrite(MA_IN2, HIGH);
  digitalWrite(MB_IN3, HIGH); digitalWrite(MB_IN4, LOW);
}

void esquerda() {
  digitalWrite(MA_IN1, HIGH); digitalWrite(MA_IN2, LOW);
  digitalWrite(MB_IN3, LOW); digitalWrite(MB_IN4, HIGH);
}

void parar() {
  digitalWrite(MA_IN1, LOW); digitalWrite(MA_IN2, LOW);
  digitalWrite(MB_IN3, LOW); digitalWrite(MB_IN4, LOW);
}