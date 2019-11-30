#ifndef CONEXION_H
#define CONEXION_H

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <ctype.h>
#include <string.h>

#define MAX_CLIENTES 10
#define MAX_MENSAJE 100
#define esCliente(x) x == '0'

/**
 * Crea el socket para servidor
 * @param puerto vector de char con el puerto a utilizar
 * @return Socket configurado como servidor
 */
int CrearSocketServer(char * puerto);

/**
 * Crea el socket para cliente
 * @param puerto vector de char con el puerto a utilizar
 * @return Socket configurado como cliente
 */
int CrearSocketCliente(char * puerto);

/**
 * Hilo para conectar con otro servidor
 */
void ConectarServer();

#endif