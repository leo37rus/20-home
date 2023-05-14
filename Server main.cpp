#include "ChatServ.h"

int main() {
    Chat_ServerTCP Serv;
    if (Serv.ÑreateSoc()){
        Serv.connect();}
    return 0;}

