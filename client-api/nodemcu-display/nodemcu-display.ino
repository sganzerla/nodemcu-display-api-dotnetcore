#include <LiquidCrystal.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <Wire.h>

// dispĺay LCD
#define RS D2
#define EN D3
#define d4 D5
#define d5 D6
#define d6 D7
#define d7 D8

LiquidCrystal lcd(RS, EN, d4, d5, d6, d7);

const char *ssid = "SEU_SSID";
const char *password = "SENHA_DA_REDE";

byte grau[8] = {
    B00001100,
    B00010010,
    B00010010,
    B00001100,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
};

void setup()
{

  Serial.begin(115200);

  WiFi.begin(ssid, password);

  Wire.begin(D2, D1);

  lcd.begin(16, 2);
  // lcd.backlight();
  lcd.home();

  //Cria o caractere customizado com o simbolo do grau
  lcd.createChar(0, grau);

  //limpa o tela e escreve os textos iniciais
  lcd.clear();
  lcd.setCursor(1, 1);
  lcd.print("SSID: ");

  lcd.setCursor(7, 1);
  lcd.print(ssid);

  lcd.setCursor(1, 2);
  lcd.print("Conectando...");

  //Verifica se o esp está conectado na rede, caso contrário realiza a tentaiva a cada 2 seg.
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(2000);
    Serial.println(WiFi.status());
  }
}

void loop()
{
  // Verifica se o esp está conectado
  if (WiFi.status() == WL_CONNECTED)
  {

    //cria a requisição http passando o URL da api node
    HTTPClient http;
    http.begin("https://localhost:5001/WeatherForecast");
    int httpCode = http.GET();
    if (httpCode > 0)
    {

      //definindo o tamanho do buffer para o objeto json
      const size_t bufferSize = JSON_OBJECT_SIZE(5);

      //realizando o parse do json para um JsonObject
      //DynamicJsonBuffer jsonBuffer(bufferSize);
      DynamicJsonDocument jsonBuffer(bufferSize);
      
      //JsonObject &root = jsonBuffer.parseObject(http.getString());

      deserializeJson(jsonBuffer, http.getString());
      //carregando os valores nas variaveis
      const char *_data = jsonBuffer["date"];
      const char *_temper = jsonBuffer["temperatureC"];
      const char *summary = jsonBuffer["summary"];

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Data: ");
      lcd.print(_data);

      lcd.setCursor(0, 2);
      lcd.print("Temperatura: ");
      lcd.print(_temper);
      //Mostra o simbolo do grau formado pelo array
      lcd.write((byte)0);
    }
    //fechando a conexão
    http.end();
  }
  delay(60000);
}
