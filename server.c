#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "conexion.h"

int main(int argc, char ** argv)
{
	system("clear");

	if(argc != 2)
	{
		printf("Para ejecutar el server: ./server <PUERTO>\n");
		printf("Ej: ./server 8080\n");
		printf("En caso de usar mas de un server, no usar el mismo puerto.\n");
		exit(1);
	}

	char * puerto = argv[1];
	int server = CrearSocketServer(puerto);

	int maxfd = MAX_CLIENTES + 1;
    fd_set master;
    FD_ZERO(&master);
    FD_SET(server, &master);
    
    int client[MAX_CLIENTES];
    char mensaje[MAX_MENSAJE];
    int i = 0;

    pthread_t hilo;
    pthread_create(&hilo, NULL,(void*) ConectarServer , NULL);

    printf("Esperando conexiones entrantes...\n");
    while (1)
    {
        fd_set copy = master;
        select(maxfd, &copy, NULL, NULL, NULL); 

        // si es un cliente nuevo
        if ( FD_ISSET(server, &copy))
        {
        	/* acepta al nuevo cliente */
            client[i] = accept(server, 0, 0);
            recv(client[i], mensaje, MAX_MENSAJE, 0);

            if ( esCliente(mensaje[0]))
            {
            	printf("Se conecto un nuevo cliente.\n");
            }
            else
            {
            	printf("Se conecto un nuevo servidor.\n");
            }

        	/* lo agrega al fd */
            FD_SET(client[i] ,&master);
            i++;
        }
        else // si ya lo conoce
        {
        	int encontrado = 0;
        	for(int j = 0; j < MAX_CLIENTES && !encontrado; j++)
        	{
        		if (FD_ISSET(client[j], &copy))
                {
                	encontrado = 1;
                	if (recv(client[j], mensaje, MAX_MENSAJE, 0) > 0) 
                	{
                		printf("Mensaje nuevo: %s\n", mensaje);
                	}
                	else
                	{
                		printf("Se han desconectado\n");
                		FD_CLR(client[j], &master);
                	}
                }
        	}
        }
    }

	return 0;
}