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


## 2° Etapa - Instalando Nginx, criando serviço e configurando proxy reverso

#### Instalando Nginx 

```
user@user:~$ sudo apt update && sudo apt install nginx
```


