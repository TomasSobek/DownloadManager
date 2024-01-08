#ifndef SEMESTRALNAPRACAUDSP_SOCKETS_H
#define SEMESTRALNAPRACAUDSP_SOCKETS_H

void create_server_socket(unsigned int port);
int create_client_socket(const char *server_ip, unsigned int port);

void send_file_tcp(const char *ip, int port, const char *file_path);
void receive_file_tcp(int port, const char *file_path);

#endif //SEMESTRALNAPRACAUDSP_SOCKETS_H
