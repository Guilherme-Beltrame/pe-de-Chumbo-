# 🤖 Pé de Chumbo - Robô de Combate Controlado via Bluetooth

Este repositório contém o código-fonte e a documentação de hardware para o projeto **Pé de Chumbo**, um robô móvel desenvolvido com Arduino Uno, controlado remotamente via smartphone através de conexão Bluetooth.

O projeto utiliza uma ponte H L298N para controle de tração diferencial e velocidade variável (PWM), alimentado por baterias de Li-Ion de alta descarga.

## 📋 Tabela de Conteúdos
- [Funcionalidades](#-funcionalidades)
- [Lista de Materiais (Hardware)](#-lista-de-materiais-hardware)
- [Esquema de Ligações](#-esquema-de-ligações)
- [Configuração do Ambiente](#-configuração-do-ambiente)
- [Como Usar](#-como-usar)
- [Protocolo de Comunicação](#-protocolo-de-comunicação)

---

## ✨ Funcionalidades
* **Controle Remoto:** Movimentação em tempo real via App Android.
* **Direção Diferencial:** Capacidade de girar no próprio eixo (tipo tanque).
* **Controle de Velocidade:** Uso de pinos PWM para ajustar a potência dos motores.
* **Sistema de Proteção:** Divisor de tensão para proteção do módulo Bluetooth.

---

## 🛠 Lista de Materiais (Hardware)

| Componente | Modelo/Especificação | Quantidade |
| :--- | :--- | :--- |
| **Microcontrolador** | Arduino Uno R3 | 1 |
| **Driver de Motor** | Ponte H L298N (Módulo Vermelho) | 1 |
| **Motores** | Motor DC N20 (3-12V) com caixa de redução | 2 |
| **Comunicação** | Módulo Bluetooth HC-05 ou HC-06 | 1 |
| **Alimentação** | Baterias Li-Ion 18650 (em série ~7.4V) | 2 |
| **Segurança** | Chave Liga/Desliga (Gangorra) | 1 |
| **Resistores** | 1kΩ e 2kΩ (Para divisor de tensão do Bluetooth) | 1 de cada |

---

## 🔌 Esquema de Ligações

A montagem deve seguir rigorosamente a tabela abaixo para corresponder ao código fornecido.

### 1. Motores e Driver (L298N)
**Importante:** Remova o jumper de 5V do L298N se estiver alimentando com mais de 12V. Para 7.4V, o jumper pode ser mantido ou usado para alimentar o Arduino (opcional).

| Arduino Pin | L298N Pin | Função |
| :--- | :--- | :--- |
| **D3** (PWM) | **ENA** | Controle de Velocidade Motor A |
| **D9** (PWM) | **ENB** | Controle de Velocidade Motor B |
| D4 | IN1 | Direção Motor A |
| D5 | IN2 | Direção Motor A |
| D6 | IN3 | Direção Motor B |
| D7 | IN4 | Direção Motor B |

### 2. Módulo Bluetooth (HC-05/06)
**Atenção:** O pino RX do módulo Bluetooth trabalha com lógica 3.3V. Recomenda-se o uso de um divisor de tensão.

| Arduino Pin | Bluetooth Pin | Observação |
| :--- | :--- | :--- |
| **D10** | **TX** | Arduino recebe dados (RX Software) |
| **D11** | **RX** | Arduino envia dados (TX Software) via Divisor* |
| 5V | VCC | Alimentação |
| GND | GND | Terra Comum |

*\*Divisor de Tensão: Conectar D11 a um resistor de 1kΩ e então ao RX do Bluetooth. Conectar o RX do Bluetooth a um resistor de 2kΩ e então ao GND.*

### 3. Alimentação
* **Baterias em Série (~7.4V a 8.4V):**
    * Positivo (+) -> Chave Liga/Desliga -> **Arduino VIN** e **L298N 12V**.
    * Negativo (-) -> **GND** comum (Arduino, L298N e Baterias).

---

## 💻 Configuração do Ambiente

1.  Baixe e instale a [Arduino IDE](https://www.arduino.cc/en/software).
2.  Clone este repositório ou baixe o arquivo `.zip`.
3.  Abra o arquivo principal `.ino` na Arduino IDE.
4.  Conecte o Arduino ao PC via cabo USB.
5.  Selecione a placa: `Ferramentas > Placa > Arduino AVR Boards > Arduino Uno`.
6.  Selecione a porta correta em `Ferramentas > Porta`.
7.  Carregue o código (Upload).

> **Nota:** Não é necessário desconectar o Bluetooth para carregar o código, pois estamos usando a biblioteca `SoftwareSerial` nos pinos D10 e D11.

---

## 📱 Como Usar

1.  Ligue o robô através da chave geral.
2.  No seu smartphone Android, ative o Bluetooth e pareie com o dispositivo `HC-05` ou `HC-06` (Senha padrão: `1234` ou `0000`).
3.  Baixe um aplicativo controlador, recomenda-se o **"Bluetooth RC Controller"** (desenvolvedor: Mihai Pruna).
4.  No App, conecte-se ao módulo pareado.
5.  Configure os botões (se necessário) ou use o padrão para enviar os caracteres abaixo.

---

## 📡 Protocolo de Comunicação

O robô espera receber caracteres simples (Char) via Serial para executar os movimentos.

| Caractere | Ação | Descrição |
| :---: | :--- | :--- |
| **'F'** | Frente | Move ambos os motores para frente. |
| **'B'** | Trás | Move ambos os motores para trás. |
| **'L'** | Esquerda | Gira no próprio eixo (Motor Esq Trás / Motor Dir Frente). |
| **'R'** | Direita | Gira no próprio eixo (Motor Esq Frente / Motor Dir Trás). |
| **'S'** | Parar | Corta a alimentação dos motores (Velocidade 0). |

---

## ⚠️ Avisos de Segurança
* **Baterias:** Baterias 18650 requerem cuidado. Nunca deixe os fios positivo e negativo se tocarem (curto-circuito).
* **Calor:** Verifique se o dissipador do L298N não está superaquecendo durante uso intenso.

---
