# Server API REST dotnet Core

 ### Requisitos
 
 - Ubuntu 
 
 - [.Net Core 3.1](https://docs.microsoft.com/pt-br/dotnet/core/install/linux-package-manager-ubuntu-1804)
   

  ## Hardware necessário
```
- a) 1 Nodemcu   
- b) 1 Display LCD 16X2 
- c) 1 Potenciometro Linear 500k  
- d) 1 Protoboard
- e) 12-15 Cabos de conexão   
```
### a) Placa Nodemcu v1 
 Possui pinos de alimentação somente de 3.3v
 
<p><a target="_blank" rel="noopener noreferrer" href="https://user-images.githubusercontent.com/22710963/77499726-a0e47100-6e31-11ea-9768-2aabb681259e.png">
  <img src="https://user-images.githubusercontent.com/22710963/77499726-a0e47100-6e31-11ea-9768-2aabb681259e.png" alt="reset" style="max-width:100%;"></a></p> 

 ### b) Display LCD 16X2 
  
  Atenção os pinos devem estar soldados no display senão não funciona.
 
<p><a target="_blank" rel="noopener noreferrer" href="https://user-images.githubusercontent.com/22710963/77712613-0d3aae00-6fb3-11ea-892b-0d5e8753b394.png">
  <img src="https://user-images.githubusercontent.com/22710963/77712613-0d3aae00-6fb3-11ea-892b-0d5e8753b394.png" alt="reset" style="max-width:100%;"></a></p>

### c) Potenciometro Linear 500k
  <p><a target="_blank" rel="noopener noreferrer" href="https://user-images.githubusercontent.com/22710963/77713295-c1890400-6fb4-11ea-87e0-9f36d23c9042.png">
  <img src="https://user-images.githubusercontent.com/22710963/77713295-c1890400-6fb4-11ea-87e0-9f36d23c9042.png" alt="reset" style="max-width:100%;"></a></p> 
   
  ### d) Protoboard 
<p><a target="_blank" rel="noopener noreferrer" href="https://user-images.githubusercontent.com/22710963/77499362-a8574a80-6e30-11ea-9744-a15c3206fd50.png">
  <img src="https://user-images.githubusercontent.com/22710963/77499362-a8574a80-6e30-11ea-9744-a15c3206fd50.png" alt="reset" style="max-width:100%;"></a></p> 

  ### e) Cabos de conexão
<p><a target="_blank" rel="noopener noreferrer" href="https://user-images.githubusercontent.com/22710963/77499606-5662f480-6e31-11ea-96fd-9e268dceb50f.png">
  <img src="https://user-images.githubusercontent.com/22710963/77499606-5662f480-6e31-11ea-96fd-9e268dceb50f.png" alt="reset" style="max-width:100%;"></a></p> 


### Configuração:

- Alterar rede wifi e senha

```
// altere com o nome da sua rede wifi
const char *ssid = "Wii";
// altere com a senha da sua wifi
const char *password = "12345678";

```

- Alterar URL para consumir API e o intervalo em que é chamada

```
const String urlGet = "http://192.168.1.5:5001/WeatherForecast";
// Tempo para checar API
const long tempoMiliseg = 5000;
```

- Alterar os dados do payload exibidos no display

JSON Recebido

```
[
  {
    "date": "2020-03-30T11:11:17.8544144-03:00",
    "temperatureC": 18,
    "temperatureF": 64,
    "summary": "Mild"
  },
  {
    "date": "2020-03-31T11:11:17.8545598-03:00",
    "temperatureC": 48,
    "temperatureF": 118,
    "summary": "Sweltering"
  },
  {
    "date": "2020-04-01T11:11:17.8545632-03:00",
    "temperatureC": -18,
    "temperatureF": 0,
    "summary": "Hot"
  },
  {
    "date": "2020-04-02T11:11:17.8545635-03:00",
    "temperatureC": 12,
    "temperatureF": 53,
    "summary": "Chilly"
  },
  {
    "date": "2020-04-03T11:11:17.8545637-03:00",
    "temperatureC": 39,
    "temperatureF": 102,
    "summary": "Freezing"
  }
]
```
Exibindo chave summary e temperatureC

```

  //carregando os valores nas variaveis
  const char *summary = json[0]["summary"];
  const int temp = json[0]["temperatureC"];
 
}

```



