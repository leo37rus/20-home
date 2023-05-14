#include "ChatClie.h"
using namespace std;
Client::~Client()
{close(socket_file_descriptor);}

bool Client::CreateSoc()
{socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_file_descriptor == -1) 
    {cout << "Failed to create socket!" << endl;
        return false;}
    ServDress.sin_addr.s_addr = inet_addr("127.0.0.1");
    ServDress.sin_port = htons(PORT);
    ServDress.sin_family = AF_INET;
    return true;}

void Client::ConnectServ()
{connection = connect(socket_file_descriptor, (struct sockaddr*)&ServDress, sizeof(ServDress));
    if (connection == -1) 
    {cout << "Connection to the server failed!" << endl;
        exit(1);}
    cout << "connection ok" << endl;
    communication();}

void Client::communication()
{ while (1) 
       {bzero(message, sizeof(message));
        read(socket_file_descriptor, message, sizeof(message));
        cout << "Server message: " << message << endl;
        bzero(message, sizeof(message));
        cout << "Message for client: ";
        std::cin.getline(message, MESSAGE_LENGTH);
        if ((strncmp(message, "end", 3)) == 0)
        { write(socket_file_descriptor, message, sizeof(message));
            cout << " Client logged out" << endl;
            cout << "Press any key to exit" << endl;
            cin.get();
            return;}
        ssize_t bytes = write(socket_file_descriptor, message, sizeof(message));
        if (bytes >= 0) {cout << "Data sent successfully!" << endl;}}
}
