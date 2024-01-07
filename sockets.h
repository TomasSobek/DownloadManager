#ifndef SEMESTRALNAPRACAUDSP_SOCKETS_H
#define SEMESTRALNAPRACAUDSP_SOCKETS_H

int create_server_socket(unsigned int port);
int create_client_socket(const char *server_ip, unsigned int port);

#endif //SEMESTRALNAPRACAUDSP_SOCKETS_H
