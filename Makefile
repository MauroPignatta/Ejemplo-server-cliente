all: server cliente

server: server.c conexion.c conexion.h
	gcc server.c conexion.c -o server

cliente: cliente.c conexion.c conexion.h
	gcc cliente.c conexion.c -o cliente