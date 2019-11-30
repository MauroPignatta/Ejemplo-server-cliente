#include <stdio.h>
#include <stdlib.h>
#include "conexion.h"

int main(int argc, char ** argv)
{
	system("clear");

	if(argc != 2)
	{
		printf("Para ejecutar el cliente: ./client <PUERTO DEL SERVIDOR>\n");
		printf("Ej: ./cliente 8080\n");
		exit(1);
	}

	char mensaje[MAX_MENSAJE] = "0"; 
	char * puerto = argv[1];
	int cliente = CrearSocketCliente(puerto);
	send(cliente, mensaje, MAX_MENSAJE, 0); // envio el 0 para que sepa que es un cliente

	while(1)
	{
		gets(mensaje);
		send(cliente, mensaje, MAX_MENSAJE, 0);
	}
	return 0;
}