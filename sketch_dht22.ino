//Biblioteca para uso do WiFi do ESP8266
#include <ESP8266WiFi.h>
//Biblioteca para uso do ESP8266 no Blynk
#include <BlynkSimpleEsp8266.h>
//Biblioteca do DHT22
#include <DHT.h> 

//Auth token
#define BLYNK_AUTH_TOKEN "mmRsl1i8SKbZec8zHUYWyrpH5yE8Tarq"

//Armazena o AuthToken
char auth[] = BLYNK_AUTH_TOKEN;
//Rede WiFi
char ssid[] = "IoT";
//Senha da rede WiFi
char pass[] = "nodemcu8266"; 

#define DHTPIN D2          // Define o pino digital que o DHT22 está conectado
#define DHTTYPE DHT22     // DHT 22
DHT dht(DHTPIN, DHTTYPE); //Inicializando o objeto dht do tipo DHT passando como parâmetro o pino (DHTPIN) e o tipo do sensor (DHTTYPE)
BlynkTimer timer; //Inicializando o objeto timer do tipo BlynkTimer

//Função de leitura do sensor
void sendSensor(){
  float h = dht.readHumidity(); //Realiza a leitura da umidade e armazena na variável h
  float t = dht.readTemperature(); //Realiza a leitura da temperatura e armazena na variável t

  if (isnan(h) || isnan(t)) { //Verifica se houve falha na leitura do sensor
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V5, h); //Escreve no pino virtual V5 o valor de h (umidade)
  Blynk.virtualWrite(V6, t); //Escreve no pino virtual v6 o valor de t (temperatura)
}

void setup(){
  Serial.begin(9600); //Inicialização da comunicação serial

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80); //Inicializa o blynk passando como parâmetro o auth token, o nome da rede Wi-Fi e a senha
  dht.begin(); //Inicializa o sensor

  timer.setInterval(1000L, sendSensor); //Função sendSensor sendo chamada a cada segundo
}

void loop(){
  Blynk.run(); //Chama a função Blynk.run()
  timer.run(); //Chama a função timer.run()
}
