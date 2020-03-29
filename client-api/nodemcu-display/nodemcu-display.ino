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

// altere com o nome da sua rede wifi
const char *ssid = "Wii";
// altere com a senha da sua wifi
const char *password = "12345678";

// Tempo para checar API
const long tempoMiliseg = 5000;

uint32_t timer = 0;

void setup()
{

  Serial.begin(9600);

  setandoPinos();
  //Verifica se o esp está conectado na rede, caso contrário realiza a tentaiva a cada 2 seg.
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(2000);
    Serial.println(WiFi.status());
  }

  lcd.setCursor(1, 1);
  lcd.print("OK Conectado...");
  delay(5000);
}

void loop()
{

  if (millis() - timer >= tempoMiliseg)
  {
    chamandoAPI();
    timer = millis();
  }
}

void chamandoAPI()
{

  lcd.clear();

  // Verifica se o esp está conectado
  if (WiFi.status() == WL_CONNECTED)
  {

    //cria a requisição http passando o URL da api node
    HTTPClient http;
    http.begin("http://192.168.1.5:5001/WeatherForecast");
    int httpCode = http.GET();

    if (httpCode > 0)
    {
      const String input = http.getString();

      DynamicJsonDocument doc(1024);

      deserializeJson(doc, input);

      exibirDadosDisplay(doc);
    }
    else
    {
      lcd.setCursor(1, 1);
      lcd.print("Error API: ");
      lcd.print(httpCode);
    }

    //fechando a conexão
    http.end();
  }
}

void exibirDadosDisplay(DynamicJsonDocument json)
{

  //carregando os valores nas variaveis
  const char *summary = json[0]["summary"];
  const int temp = json[0]["temperatureC"];

  lcd.setCursor(0, 0);
  lcd.print("S: ");
  lcd.print(summary);

  lcd.setCursor(0, 2);
  lcd.print("T: ");
  lcd.print(temp);
  lcd.write(B11011111); // Imprime o símbolo de grau
  lcd.print("C");
}

void setandoPinos()
{
  WiFi.begin(ssid, password);

  Wire.begin(D2, D1);

  lcd.begin(16, 2);
  lcd.clear();

  lcd.setCursor(1, 0);
  lcd.print("Conectando...");
}
