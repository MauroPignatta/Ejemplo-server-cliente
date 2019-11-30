#include "conexion.h"

int CrearSocketServer(char * puerto)
{
    int Puerto = atoi(puerto);
    
    //crea el socket
    int server = socket(AF_INET, SOCK_STREAM, 0);
    
    //libera el socket al cerrar la aplicacion
    int activado = 1;
    setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &activado, sizeof(activado));
    
    //Estructura que contiene datos del servidor 
    struct sockaddr_in dirServer;
    dirServer.sin_family = AF_INET;
    dirServer.sin_addr.s_addr = inet_addr("127.0.0.1");
    dirServer.sin_port = htons(Puerto);
    
    //comprobar error
    if ( bind(server, (struct sockaddr*) &dirServer,sizeof (dirServer)) != 0)
    {
        perror("Error de conexion");
        exit(2);
    }
    
    listen(server, MAX_CLIENTES + 1);
    printf("Socket server creado correctamente.\n");
    return server;
}

int CrearSocketCliente(char * puerto)
{
    int Puerto = atoi(puerto);
    
    /* Creamos el socket*/
    int cliente = socket(AF_INET, SOCK_STREAM, 0);
    
    /* En esta struct se guardan los datos del servidor*/
    struct sockaddr_in dirServer;
    dirServer.sin_family = AF_INET;
    dirServer.sin_addr.s_addr = inet_addr("127.0.0.1");
    dirServer.sin_port = htons(Puerto);
    
    /* Conectamos al servidor*/
    if (connect(cliente, (void *)&dirServer, sizeof(dirServer)) != 0)
    {
        perror("No se pudo conectar con el servidor");
        exit(2);
    }

    printf("Socket cliente creado correctamente.\n");
    return cliente;
}

void ConectarServer()
{
	sleep(1);
	int opt;
    char * puerto = malloc(6);
    char mensaje[MAX_MENSAJE] = "1";
    int cliente;

	printf("Queres conectarte a otro servidor? 1. Si 2.No\n");
	scanf("%d", &opt);
    
	if (opt == 1)
	{	
        printf("Ingrese el puerto del servidor a conectarse: ");
        scanf("%s", puerto);
		cliente = CrearSocketCliente(puerto);
		send(cliente, mensaje, MAX_MENSAJE, 0);

		while(1)
		{
			gets(mensaje);
			send(cliente, mensaje, MAX_MENSAJE, 0);
		}
	}
}