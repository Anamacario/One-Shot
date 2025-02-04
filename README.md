# Controle de LEDs com Botão e Temporizador One-Shot no Raspberry Pi Pico

## 📌 Descrição
Este projeto implementa um **controle de LEDs** utilizando um **Raspberry Pi Pico** e um **botão push-button** para acionar um temporizador **one-shot**. O sistema foi desenvolvido em **linguagem C**, simulado no **Wokwi**, e configurado para rodar no **VS Code** com todas as dependências e SDK instalados. Além disso, há suporte para execução em hardware real, utilizando a placa de desenvolvimento **BitDogLab**.

## 🎯 Funcionalidade
- Quando o **botão** é pressionado, **todos os LEDs acendem**.
- Após **3 segundos**, o LED **verde se apaga**.
- Após **mais 3 segundos**, o LED **azul se apaga**.
- Após **mais 3 segundos**, o LED **vermelho se apaga**.
- O botão **só pode ser pressionado novamente quando todos os LEDs forem desligados**.

## 🛠 Requisitos

**Microcontrolador**: Raspberry Pi Pico ou Raspberry Pi Pico W (opcional)
- **Placa de Desenvolvimento:** BitDogLab (opcional).
- **Conta Criada no Wokwi Simulator**: [Wokwi](https://wokwi.com/).
- **Editor de Código**: Visual Studio Code (VS Code).
- **SDK do Raspberry Pi Pico** configurado no sistema.
- Ferramentas de build: **CMake** e **Ninja**.

## 🖥 Configuração dos Pinos

| Componente | GPIO |
|------------|------|
| LED Vermelho | GPIO 13 |
| LED Azul | GPIO 11 |
| LED Verde | GPIO 12 |
| Botão | GPIO 5 |
---

## 🚀 Como Executar

### **1️⃣ Clonar o Repositório**
```bash
git clone https://github.com/Anamacario/One-Shot.git
cd One-Shot
```

### **2️⃣ Compilar e Carregar no Raspberry Pi Pico**
- Conecte a placa ao computador em modo **BOOTSEL**.
- Compile o código e copie o arquivo `.uf2` para a unidade do Pico ou pressione "Run" no terminal.

### **3️⃣ Testar no Wokwi integrado no Vs Code**
- Abra o arquivo `diagram.json`  e clique em "Run Simulation".
- Aperte o botão para inciar o sistema.

---

## ⚙ Implementação Técnica

- **Uso de Temporizador One-Shot**: O botão ativa um temporizador **`add_alarm_in_ms()`** para desligar os LEDs um por um.
- **Debouncing via Software**: Implementado para evitar leituras erradas do botão.
- **Controle do Estado do Botão**: O botão **não pode ser pressionado novamente** até que todos os LEDs estejam apagados.

---

## 🔍 Testes Realizados
✅ Teste do acionamento correto do botão.  
✅ Teste do debounce para evitar múltiplas leituras erradas.  
✅ Teste de execução no **simulador Wokwi** , **Wokwi no Vs Code** e na **BitDogLab**.  

---

## Autoria
- Ana Carla Macário
