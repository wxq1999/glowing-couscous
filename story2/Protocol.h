#ifndef CHATROOM_CLIENT_PACKET_H
#define CHATROOM_CLIENT_PACKET_H

#define REGISTER 1
#define LOGIN 2
#define CHAT 3
#define SENDFILE 4
#define EXIT 5

struct Packet{
    int PacketType;
    size_t PacketLen;
    char UserName[40];
    char Msg[1500];
};

struct Account{
    int accntfd;
    char UserID[40];
    // int Passwd;
    char Passwd[40];
};

void InitPack(struct Packet* packet){
    packet->PacketType = 0;
    packet->PacketLen = 0;
    strcpy(packet->UserName,"");
    strcpy(packet->Msg,"");
}

void setPack(struct Packet* packet,int type, size_t len, char* name, char* msg){
    packet->PacketType = type;
    packet->PacketLen = len;
    strcpy(packet->UserName,name);
    strcpy(packet->Msg,msg);
}

#endif //CHATROOM_CLIENT_PACKET_H
