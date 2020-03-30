# nodemcu-display-api-dotnetcore

Consumindo API REST .NET Core que retorna a temperatura de algumas localidades com um cliente rodando dentro de uma placa Nodemcu e exibindo num display de lcd.

### Consumindo API e exibindo no display o payload (vídeo)
<p>
 <a target="_blank" rel="noopener noreferrer" href="https://youtu.be/5IAuFDBAtKw" >
  <img src="https://user-images.githubusercontent.com/22710963/77842518-a0b5df80-7169-11ea-96f1-57ad53e3c168.png" alt="reset" style="max-width:100%;"></a>
</p> 
  

 ### [Server API dotnet Core](https://github.com/sganzerla/nodemcu-display-api-dotnetcore/tree/master/server-api) 
 
<details><summary> Como criar, configurar nginx e publicar no Linux.
</summary>
<p>

 ### Tecnologias utilizadas
 
 - [Ubuntu 19.10](https://ubuntu.com/download/desktop/thank-you?version=19.10&architecture=amd64) - Sistema Operacional 
 
 - [.Net Core 3.1](https://docs.microsoft.com/pt-br/dotnet/core/install/linux-package-manager-ubuntu-1910) - SDK .NET Core 3.1
   
- [Nginx](https://www.nginx.com/) - Hospedar aplicações web e rodar serviços


## 1° Etapa - Criando projeto e gerando artefato para publicar no servidor 

Execute os seguintes comandos dentro do terminal:

#### Verifica se há versão .NET Core SDK instalada na máquina, resposta 
```
user@user:~$ sudo dotnet --list-sdks
```

#### Criando projeto API e acessando diretório do projeto
```
user@user:~$ sudo dotnet new api -n wheater-api && cd wheater-api
```

#### Rodando a aplicação para verificar se foi criada corretamente

Importante que as portas 5000 e 5001 estejam disponíveis
```
user@user:~/wheater-api$ sudo dotnet run
```

Acesse a seguinte URL https://localhost:5001/WeatherForecast

<p>
 <a target="_blank" rel="noopener noreferrer" href="https://user-images.githubusercontent.com/22710963/77859558-89660900-71e0-11ea-8bd6-8c848676f1b7.png" >
  <img src="https://user-images.githubusercontent.com/22710963/77859558-89660900-71e0-11ea-8bd6-8c848676f1b7.png" alt="reset" style="max-width:100%;"></a>
</p> 

Pare de rodar a aplicação para liberar as portas novamente digitando Ctrl + C dentro do terminal

#### Gerando artefato para publicação no servidor

```
user@user:~/wheater-api$ sudo dotnet publish
```

#### Movendo o artefato gerado para diretório de publicação

```
user@user:~/wheater-api$ sudo cp -r bin/Debug/netcoreapp3.1/publish /var/www/html/wheater-api
```

Etapa 1 concluída.


## 2° Etapa - Instalando Nginx, criando serviço 

#### Instalando Nginx 

```
user@user:~$ sudo apt update && sudo apt install nginx
```

#### Criando serviço para rodar aplicação .NET

```
user@user:~$ sudo gedit /etc/systemd/system/wheater-api.service
```

Dentro do arquivo colar as seguintes configurações 

```
[Unit]
Description=Wheater-api running on Ubuntu
[Service]
WorkingDirectory=/var/www/html/wheater-api
ExecStart=/usr/bin/dotnet /var/www/html/wheater-api/wheater-api.dll
Restart=always
# Restart service after 10 seconds if the dotnet service crashes:
RestartSec=10
KillSignal=SIGINT
SyslogIdentifier=wheater-api
User=www-data
Environment=ASPNETCORE_ENVIRONMENT=Production
Environment=DOTNET_PRINT_TELEMETRY_MESSAGE=false
[Install]
WantedBy=multi-user.target
```

#### Habilitando serviço para iniciar junto com sistema operacional
```
user@user:~$ sudo systemctl enable wheater-api.service
```

#### Iniciar serviço

```
user@user:~$ sudo systemctl start wheater-api.service
```

#### Conferir status do serviço

```
user@user:~$ sudo systemctl status wheater-api.service
```
Etapa 2 concluída

## 3° Etapa - Configurando proxy reverso

#### Criando arquivo de configuração

```
user@user:~$ sudo gedit /etc/nginx/sites-available/wheater-api
```

Colar dentro do arquivo as configurações abaixo

```
server {
         listen [::]:5001;
         listen 5001;

        root /var/www/html/wheater-api;
        server_name wheater-api *.wheater-api;

        location / {
                     proxy_pass      http://localhost:5000/;
                     proxy_http_version 1.1;
                     proxy_set_header   Upgrade $http_upgrade;                    
                     proxy_set_header   Connection $http_connection; 
                     proxy_set_header   Host $host;
                     proxy_cache_bypass $http_upgrade;
                     proxy_set_header   X-Forwarded-For $proxy_add_x_forwarded_for;
                     proxy_set_header   X-Forwarded-Proto $scheme;
                     proxy_set_header 'Access-Control-Allow-Headers' '*';
                     proxy_set_header 'Access-Control-Allow-Methods' 'GET,POST,OPTIONS,PUT,DELETE';
        } 
}
```
#### Criando link simbólico para habilitar o site


```
user@user:~$ sudo ln -s /etc/nginx/sites-available/wheater-api /etc/nginx/sites-enabled/
```

#### Consultar sintaxe do arquivo de configuração

```
user@user:~$ sudo nginx -t
```

#### Restartando Nginx para pegar configurações

```
user@user:~ sudo systemctl restart nginx
```

#### Acessar no navegador 
Com localhost http://localhost:5001/WeatherForecast e com seu próprio ip 


Etapa 3 concluída.

## 4° Etapa - Liberando portas do firewall e realizando redirecionamento de portas dentro do roteador 

Liberando portas no firewall da máquina
```
$ sudo apt-get install ufw
$ sudo ufw allow 5000/tcp
$ sudo ufw allow 5001/tcp
$ sudo ufw enable
$ sudo ufw status verbose
```
No roteador precisa ser criado regra para redirecionar solicitações para a porta 5000/5001 para o IP da máquina do servidor

https://www.youtube.com/watch?v=9havP7L2Smk



</p>
</details>
 
 
## [Cliente Nodemcu](https://github.com/sganzerla/nodemcu-display-api-dotnetcore/tree/master/client-api/nodemcu-display) 
 

<details><summary> Criando cliente e montando circuito com display lcd.</summary>
<p>

  ### Circuito 
 
 <p>
 <a target="_blank" rel="https://user-images.githubusercontent.com/22710963/77842571-33ef1500-716a-11ea-9ab7-eddb25cc5211.png" >
  <img src="https://user-images.githubusercontent.com/22710963/77842571-33ef1500-716a-11ea-9ab7-eddb25cc5211.png" alt="reset" style="max-width:100%"></a>
</p> 

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


</p>
</details>


### Links úteis

 
- [IDE Arduino](https://www.arduino.cc/en/Main/Software)
 
- [Documentação sintaxe C++](https://www.arduino.cc/reference/en/)

- [Fritzing](https://fritzing.org/home/) - Licença comercial

- [Fritzing](https://softfamous.com/fritzing/download/) - Versão gratuita (antiga mas permite que seja atualizada)

- [TinkerCad](https://www.tinkercad.com) - Ambiente Virtual p/ prototipagem
 
- [Circuit Digest](https://circuitdigest.com/microcontroller-projects/interfacing-lcd-with-nodemcu) Pinagem Display LCD sem conector I2C no Nodemcu

- [Arduino Json](https://arduinojson.org/v6/api/json/deserializejson/) Biblioteca para trabalhar com JSON

- [Doc Dotnet](https://docs.microsoft.com/pt-br/dotnet/core/tools/dotnet-build) Fazer build de aplicação dotnet para deploy

- [Configurando Servidor Nginx](https://github.com/sganzerla/run-dotnetcore-nginx-server) Criando serviço e configurando o proxy

- [Filipe Flop](https://www.filipeflop.com/blog/como-utilizar-uma-api-no-esp8266-nodemcu-boas-praticas-para-integracoes/) Client Api Rest no Nodemcu
 

 ###  Aplicações
 
 - Dispositivos que precisam consultar dados e interagir com API.


