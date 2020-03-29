# Server API REST .NET Core

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
<p>
 <a target="_blank" rel="noopener noreferrer" href="https://user-images.githubusercontent.com/22710963/77859558-89660900-71e0-11ea-8bd6-8c848676f1b7.png" >
  <img src="https://user-images.githubusercontent.com/22710963/77859558-89660900-71e0-11ea-8bd6-8c848676f1b7.png" alt="reset" style="max-width:100%;"></a>
</p> 


Etapa 3 concluída.
