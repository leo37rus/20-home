#include "ChatServ.h"
#include <arpa/inet.h>

using namespace std;

Chat_ServerTCP::~Chat_ServerTCP()
{close(socket_file_descriptor);}

bool Chat_ServerTCP::СreateSoc()
{ socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_file_descriptor == -1) {
        cout << "Failed to create socket!" << endl;
        return false; }
    serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddress.sin_port = htons(PORT);
    serveraddress.sin_family = AF_INET;
    bind_status = bind(socket_file_descriptor, (struct sockaddr*)&serveraddress,
        sizeof(serveraddress));
    if (bind_status == -1) {
        cout << "Socket bind error!" << endl;
        return false;;}
    return true;}

void Chat_ServerTCP::connect()
{ connection_status = listen(socket_file_descriptor, 5);
    if (connection_status == -1) 
    {cout << "The socket cannot accept new connections!" << endl; exit(1);}
    else {cout << "The server is waiting" << endl; }

    length = sizeof(client);
    connection = accept(socket_file_descriptor, (struct sockaddr*)&client, &length);
    if (connection == -1) {//smile makes the world better. :* 
        cout << "The server cannot accept data from the client!" << endl;exit(1);}
    cout << "Server- received a connection from" << inet_ntoa(client.sin_addr) << " port " << ntohs(client.sin_port) << endl;
    communication();}

void Chat_ServerTCP::communication()
{while (1) 
    { bzero(message, MESSAGE_LENGTH);
      cout << "Server message: ";
      cin.getline(message, MESSAGE_LENGTH);
      
      ssize_t bytes = write(connection, message, sizeof(message));
      if (bytes >= 0) { cout << "Data successfully sent to the client!" << endl; }
      bzero(message, MESSAGE_LENGTH);
      read(connection, message, sizeof(message));
      if (strncmp("end", message, 3) == 0) 
      { cout << "no client" << endl;
        cout << "Press any key to exit..." << endl;cin.get();
            return;}//did you smile?))
       cout << "Message for client: " << message << endl;}

}
