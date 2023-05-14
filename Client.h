#include<iostream>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define MESSAGE_LENGTH 1024 
#define PORT 7777 

struct Client
{   ~Client();
	bool CreateSoc();
	void ConnectServ();
	void communication();
private:
	struct sockaddr ServDress, client;
	int socket_file_descriptor, connection;
	char message[MESSAGE_LENGTH];};
