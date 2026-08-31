#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// ==============================================================
// 1. CREDENCIAIS WI-FI E ADAFRUIT IO
// ==============================================================
const char* ssid          = "ITANET-ILMAR";
const char* password      = "senha";

#define IO_SERVER         "io.adafruit.com"
#define IO_SERVERPORT     1883
#define IO_USERNAME       "Saymon231"
#define IO_KEY            "aio_NPNH35wnH4Kn2gneNdNCsKpLlel3"

const char* topic_distancia = "Saymon231/feeds/estacionamento-distancia";
const char* topic_status    = "Saymon231/feeds/estacionamento-status";

// ==============================================================
// 2. PINAGEM EXATA E VARIÁVEIS
// ==============================================================
const int trigPin     = 14;  // D5 -> GPIO 14
const int echoPin     = 12;  // D6 -> GPIO 12
const int ledVerde    = 5;   // D1 -> GPIO 5
const int ledVermelho = 16;  // D0 -> GPIO 16

long duracao;
float distancia;

WiFiClient espClient;
PubSubClient mqttClient(espClient);

unsigned long ultimoEnvio = 0;
const long intervaloEnvio = 6000; // Atualização de segurança a cada 6 segundos (Anti-Throttle)

String statusAnterior = "";
unsigned long ultimaMudancaEstado = 0;

// ==============================================================
// 3. FUNÇÕES DE CONECTIVIDADE
// ==============================================================
void conectarWiFi() {
  Serial.print("Conectando ao Wi-Fi: ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWi-Fi Conectado!");
  Serial.print("IP da ESP: ");
  Serial.println(WiFi.localIP());
}

void reconectarMQTT() {
  while (!mqttClient.connected()) {
    Serial.print("Tentando conexao MQTT...");
    String clientId = "ESP8266-Vaga-" + String(random(0xffff), HEX);

    if (mqttClient.connect(clientId.c_str(), IO_USERNAME, IO_KEY)) {
      Serial.println(" Conectado ao Adafruit IO!");
    } else {
      Serial.print(" Falha no MQTT, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" Tentando em 3s...");
      delay(3000);
    }
  }
}

void publicarDados(float dist, String st) {
  char payloadDist[8];
  dtostrf(dist, 4, 1, payloadDist);

  // Publica o status e a distância
  mqttClient.publish(topic_status, st.c_str());
  mqttClient.publish(topic_distancia, payloadDist);

  Serial.print(">> [NUVEM] Status: ");
  Serial.print(st);
  Serial.print(" | Distancia: ");
  Serial.print(payloadDist);
  Serial.println(" cm");
}

// ==============================================================
// 4. SETUP
// ==============================================================
void setup() {
  Serial.begin(115200);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);

  // Teste visual de 1s
  digitalWrite(ledVerde, HIGH);
  digitalWrite(ledVermelho, HIGH);
  delay(1000);
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledVermelho, LOW);

  Serial.println("--- Sistema Estabilizado ---");

  conectarWiFi();
  mqttClient.setServer(IO_SERVER, IO_SERVERPORT);
  mqttClient.setKeepAlive(30);
}

// ==============================================================
// 5. LOOP PRINCIPAL
// ==============================================================
void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    conectarWiFi();
  }
  if (!mqttClient.connected()) {
    reconectarMQTT();
  }
  mqttClient.loop();

  // --- LEITURA ULTRASSÔNICA ---
  digitalWrite(trigPin, LOW);
  delayMicroseconds(4);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duracao = pulseIn(echoPin, HIGH, 30000);
  distancia = (duracao * 0.0343) / 2.0;

  String statusAtual = "LIVRE";

  // Resposta visual imediata na bancada (LEDs sem delay)
  if (duracao > 100 && distancia >= 2.0 && distancia <= 20.0) {
    digitalWrite(ledVermelho, HIGH);
    digitalWrite(ledVerde, LOW);
    statusAtual = "OCUPADA";
  } else {
    digitalWrite(ledVermelho, LOW);
    digitalWrite(ledVerde, HIGH);
    statusAtual = "LIVRE";
  }

  unsigned long agora = millis();

  // ENVIO 1: Mudança de Estado com trava de 1.5s (Debounce)
  if (statusAtual != statusAnterior && (agora - ultimaMudancaEstado > 1500)) {
    statusAnterior = statusAtual;
    ultimaMudancaEstado = agora;
    ultimoEnvio = agora; // Reinicia a contagem periódica
    
    publicarDados(distancia, statusAtual);
  }
  // ENVIO 2: Heartbeat a cada 6 segundos (mantém o gráfico ativo sem estourar a cota)
  else if (agora - ultimoEnvio >= intervaloEnvio) {
    ultimoEnvio = agora;
    if (duracao > 100 && distancia >= 2.0) {
      publicarDados(distancia, statusAtual);
    }
  }

  delay(50);
}