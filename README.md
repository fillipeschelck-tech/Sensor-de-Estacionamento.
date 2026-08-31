🚗 Sistema Inteligente de Gerenciamento de Vagas

Sistema desenvolvido para detectar automaticamente a presença de veículos em vagas de estacionamento, indicando visualmente se cada vaga está livre ou ocupada e enviando a quantidade de vagas disponíveis para uma plataforma em nuvem.

👥 Integrantes

- Débora Pereira
- Luis Fillipe
- Rayssa
- Saymon

---

📌 Sobre o Projeto

O projeto tem como objetivo solucionar um problema comum em estacionamentos: a dificuldade de identificar rapidamente quais vagas estão disponíveis.

Sensores são utilizados para detectar a presença de veículos. As informações coletadas são processadas por uma ESP8266, que utiliza uma conexão Wi-Fi para enviar os dados para o Adafruit IO.

A situação da vaga também é indicada por LEDs:

- 🟢 LED verde: vaga livre
- 🔴 LED vermelho: vaga ocupada

Além da indicação visual, o sistema informa a quantidade de vagas disponíveis por meio do servidor da nuvem.

---

⚙️ Funcionamento

O funcionamento do sistema segue o seguinte fluxo:

1. O sensor ultrassônico detecta a presença de um veículo.
2. A ESP8266 recebe as informações do sensor.
3. O sistema processa os dados recebidos.
4. A vaga é identificada como livre ou ocupada.
5. O LED correspondente é acionado.
6. A quantidade de vagas disponíveis é atualizada.
7. Os dados são enviados pela rede Wi-Fi para o Adafruit IO.

---

🏗️ Arquitetura do Sistema

A arquitetura é composta por três etapas principais:

Detecção → Processamento → Comunicação/Visualização


       ┌─────────────┐
       │  LED Verde  │ → Vaga livre
       └─────────────┘

       ┌─────────────┐
       │  LED Vermelho│ → Vaga ocupada
       └─────────────┘

O sensor realiza a detecção, a ESP8266 processa os dados e a conexão Wi-Fi permite transmitir as informações para uma plataforma IoT.

---

🔩 Componentes

Para reproduzir o projeto, são necessários:

 Componente
- ESP8266 — 1.
- Sensor ultrassônico — 1.
- LED verde — 1
- LED vermelho — 1
- Protoboard — 1
- Cabos Jumper — ( Conforme necessário )
- Resistores — ( Conforme necessário ).
- Adafruit IO — Plataforma em nuvem.

---

🔌 Mapeamento dos Pinos
Componentes :

- Sensor ultrassônico – TRIG ; GPIO 14
- Sensor ultrassônico – ECHO ; GPIO 12

- LED verde : GPIO 5
- LED vermelho : GPIO 16

---

🛠️ Instruções de Replicação

1. Monte o circuito

Monte os componentes em uma protoboard, conectando o sensor ultrassônico e os LEDs à ESP8266 conforme o mapeamento de pinos apresentado anteriormente.

- Sensor Ultrassônico | 
- ├── TRIG ── → GPIO 14 │ 
- └── ECHO ── → GPIO 12

LEDs

LED Verde ───── → GPIO 5
LED Vermelho ── → GPIO 16

Utilize os resistores no circuito dos LEDs.

---

2. Prepare a ESP8266

Conecte a ESP8266 ao computador e prepare o ambiente utilizado para carregar o programa do projeto.

O código deve ser configurado para utilizar:

- O sensor ultrassônico;
- O LED verde;
- O LED vermelho;
- A conexão Wi-Fi;
- A comunicação com o Adafruit IO.

---

3. Configure a rede Wi-Fi

No código da ESP8266, informe as credenciais da rede Wi-Fi que será utilizada pelo projeto.

Importante: não publique senhas ou outras credenciais reais no GitHub. Utilize variáveis ou um arquivo de configuração que não seja enviado ao repositório.

---

4. Configure o Adafruit IO

Crie/configure o ambiente do projeto no Adafruit IO para receber os dados enviados pela ESP8266.

A ESP8266 deverá utilizar a conexão Wi-Fi para transmitir as informações referentes às vagas para a plataforma.

---

5. Carregue o código

Depois de montar o circuito e configurar a conexão:

1. Conecte a ESP8266 ao computador.
2. Abra o código do projeto.
3. Configure os dados necessários da rede Wi-Fi e do Adafruit IO.
4. Verifique o código.
5. Faça o upload para a ESP8266.
6. Aguarde a inicialização do dispositivo.

---

6. Teste o sistema

Após iniciar a ESP8266:

🟢 Vaga livre

Quando não houver veículo diante do sensor, o sistema deverá identificar a vaga como livre e utilizar o LED verde para indicar seu estado.

🔴 Vaga ocupada

Quando um veículo for detectado, a vaga deverá ser identificada como ocupada e o LED vermelho deverá indicar essa condição.

A quantidade de vagas disponíveis também deverá ser atualizada no servidor da nuvem.

---

📊 Resultado Esperado

Ao final da replicação, o sistema deverá ser capaz de:

- Detectar a presença de veículos;
- Identificar se a vaga está livre ou ocupada;
- Indicar o estado da vaga através dos LEDs;
- Processar as informações utilizando a ESP8266;
- Utilizar Wi-Fi para comunicação;
- Enviar as informações para o Adafruit IO;
- Informar a quantidade de vagas disponíveis.

---

🎯 Objetivo

O projeto busca tornar o gerenciamento de vagas mais eficiente, reduzindo a necessidade de verificação manual e facilitando a identificação das vagas disponíveis.

A combinação de sensor ultrassônico + ESP8266 + LEDs + Wi-Fi + Adafruit IO permite criar uma solução de monitoramento de vagas com indicação local e visualização dos dados na nuvem.

---

📄 Relatório

O projeto foi desenvolvido como uma solução para o problema da dificuldade de encontrar vagas disponíveis rapidamente em estacionamentos.

A utilização dos sensores permite automatizar a identificação das vagas, enquanto a ESP8266 realiza o processamento das informações. Os LEDs fornecem uma indicação visual imediata e a comunicação Wi-Fi permite transmitir os dados para uma plataforma IoT.


Dessa forma, o sistema integra sensoriamento, processamento, comunicação e visualização de dados, criando uma solução inteligente para o gerenciamento de vagas de estacionamento.

---

📜 Licença

Este projeto foi desenvolvido para fins acadêmicos e educacionais.
