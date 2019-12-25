// chatroom_client_c20191218
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/un.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <Protocol.h>
//#include <signal.h>//
#define STRING_SIZE 40

#define SERVER_ADDR "127.0.0.1"//本机测试, fuctions well//try local db
//#define SERVER_ADDR "47.101.152.44"//服务器公网ip, 连接成功， register回车后报错退出Message from debugger: Terminated due to signal 13
//#define SERVER_ADDR "172.17.31.160"//服务器内网ip, connect error，所以就用公网ip吧
#define SERVER_PORT 6666

struct Packet pack_send;
struct Packet pack_recv;
struct Account account;
struct Account accntlist[5];
pthread_t tid;
int LoginSuccess = 0;

void* pthread_function(void* sock_fd);  //线程主函数

void Register_request(int fd);  //注册
void Login_request(int fd);     //登录
void SendFile_request(int fd);  //发送文件
void Chat_request(int fd);      //聊天
void Chat_p2p(int fd);      //私聊
void CheckHistory_request(int fd);//查看消息记录

/* Catch Signal Handler functio */
//void signal_callback_handler(int signum){
//    printf("Caught signal SIGPIPE %d\n",signum);
//}

int main(){
    /* Catch Signal Handler SIGPIPE */
    //    signal(SIGPIPE, signal_callback_handler);//
    //    signal(SIGPIPE, SIG_IGN);//
    
    
    printf("connecting...\n");
    int sockfd;
    struct sockaddr_in server_addr;
    
    
    if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1){
        printf("socket error");
        exit(1);
    }
    
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(SERVER_PORT);
    server_addr.sin_addr.s_addr=inet_addr(SERVER_ADDR);
    
    if(connect(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr))==-1){
        printf("connect error");
        exit(1);
    }
    
    printf("Welcome to this chatroom! Select an option to continue:\n");
    printf("1.Register\n2.Login\n");
    int option;
    scanf("%d", &option);
    fflush(stdin);
    switch(option){
        case REGISTER:
            Register_request(sockfd);
            break;
        case LOGIN:
            Login_request(sockfd);
            break;
        default:
            break;
    }
    
    if(LoginSuccess) {
//        while(1){//加上循环从而使得client可以执行多次请求直到选择EXIT.
            printf("Select an option to continue:\n3. Chat\n4. File Transfer\n5. Check Message History\n6. Exit\n");
            scanf("%d", &option);
            fflush(stdin);
            switch(option){
                case CHAT:
                    Chat_request(sockfd);
                    break;
                case SENDFILE:
                    SendFile_request(sockfd);
                    break;
                case HISTORY:
                    CheckHistory_request(sockfd);
                    break;//
                case EXIT:
                    close(sockfd);
                    exit(1);
                default:
                    break;
            }
//        }
    }
    else {
        close(sockfd);
        exit(1);
    }
    
    close(sockfd);
    pthread_cancel(tid);
    return 0;
}

void Register_request(int fd){
    setPack(&pack_send, REGISTER, 0, "", "");
    if(send(fd,&pack_send,sizeof(pack_send),0) == -1){
        perror("send error");
        exit(1);
    }
    //sleep(1);
    char passwd2[STRING_SIZE];
    printf("Username: ");
    scanf("%s", account.UserID);
    printf("Password: ");
    scanf("%s", account.Passwd);
    printf("Confirm Password: ");
    scanf("%s", passwd2);
    if (strcmp(passwd2, account.Passwd) != 0) {
        printf("Password and Re-entered Password do not match\n");
        exit(0);
    }
    
    account.accntfd = fd;//
    if(send(fd,&account, sizeof(account),0) == -1){
        perror("send error");
        exit(1);
    }
    //sleep(1);
    if(recv(fd, &pack_recv, sizeof(pack_recv), 0) == -1){
        perror("recv error");
        exit(1);
    }
    
    if(strcmp(pack_recv.Msg,"Registered!") == 0){
        printf("Successfully registered!\n");
        LoginSuccess = 1;
    }else{
        printf("%s\n", pack_recv.Msg);
    }
}

void Login_request(int fd){
    printf("Username: ");
    scanf("%s",account.UserID);
    printf("Password: ");
    scanf("%s", account.Passwd);
    setPack(&pack_send, 2, 0, account.UserID, "");
    if(send(fd,&pack_send, sizeof(pack_send), 0) == -1){
        perror("send error");
        exit(1);
    }
    //sleep(1);
    if(send(fd,&account,sizeof(account),0) == -1){
        perror("send error");
        exit(1);
    }
    //sleep(1);
    if(recv(fd, &pack_recv, sizeof(pack_recv),0) == -1){
        perror("recv error");
        exit(1);
    }
    printf("%s\n", pack_recv.Msg);
    if(strcmp(pack_recv.Msg,"Login Successfully!") == 0)
        LoginSuccess = 1;
    else{
        LoginSuccess = 0;
    }
}

void Chat_request(int fd){
    int option;
    //sleep(1);
    setPack(&pack_send, CHAT, 0, "", "");
    if(send(fd, &pack_send, sizeof(pack_send), 0) == -1){
        perror("send error");
        exit(1);
    }
    //sleep(1);
    printf("In which way do you like to chat?\n1. Chat with an online user.\n2. Chat in the group.\n");
    scanf("%d", &option);
    send(fd, &option, sizeof(option), 0);
    switch (option){
        case 1:
            Chat_p2p(fd);
            break;
        case 2:
            //chat in the group
            break;
        default:
            printf("Wrong Option!\n");
            exit(1);
    }
    
    //    if (pthread_create(&tid, NULL, (void *) pthread_function, (void *) &fd) != 0)
    if(pthread_create(&tid,NULL,pthread_function,(void*)&fd)!=0)//
        printf("create thread error\n");
    //不断发送聊天内容
    while(1){
        InitPack(&pack_send);
        char tmp[1500];
        fflush(stdout);
        fflush(stdin);
        fgets(tmp, 1500, stdin);
        tmp[1499] = '\0';
        if(tmp[0] == '\n')
            continue;
        setPack(&pack_send, CHAT, strlen(tmp),account.UserID,tmp);
        if(send(fd,&pack_send, sizeof(pack_send),0)==-1){
            printf("send error");
            exit(1);
        }
        //sleep(1);
    }
    
}

void SendFile_request(int fd){
    
}

void Chat_p2p(int fd){
    int i = 0;
    int choice;
    char userlist[140];
    char* plen = userlist;
    recv(fd, userlist, 140, 0);//receive online userlist
    for(i = 0; i < 5; i++){
        memcpy(&accntlist[i], plen, 28);
        plen += 28;
    }
    printf("Choose one online user below to chat with:\n");
    for(i = 0; i < 5; i++){
        if(accntlist[i].accntfd != -1)
            printf("%d. %s\n", i+1, accntlist[i].UserID);
    }
    scanf("%d",&choice);
    send(fd, &choice, sizeof(choice), 0);
}

//不断接收聊天内容
void* pthread_function(void* sock_fd){
    int sockfd=*(int*)sock_fd;
    while(1) {
        if(recv(sockfd, &pack_recv, sizeof(pack_recv), 0)==-1){
            printf("recv error");
            exit(1);
        }
        if(pack_recv.PacketType == CHAT){
            if(strcmp(pack_recv.UserName,account.UserID) != 0)
                printf("%s: %s", pack_recv.UserName, pack_recv.Msg);
        }
    }
    return ((void*)0);
}

void CheckHistory_request(int fd){
    //send request
    setPack(&pack_send, HISTORY, 0, "", "");
    if(send(fd,&pack_send,sizeof(pack_send),0) == -1){
        perror("send error");
        exit(1);
    }
    
    //receive result
    char filename[60] = {0};
    sprintf(filename, "%shistory.txt", account.UserID);
    FILE *fp;
    if((fp = fopen(filename, "w")) == NULL){
        printf("file open error\n");
        exit(1);
    }
    
    char lastmessage[1800] = {0};
    while(1) {//暂时注释掉循环才发现每次收到的都是空的。问题1:为什么是空的。问题2:如何终止循环//all due to the "strcpy", now solved.
        //一轮循环处理收到的一条消息记录。
        if(recv(fd, &pack_recv, sizeof(pack_recv), 0)==-1){
            printf("recv error");
            exit(1);
        }
        
        if(pack_recv.PacketType == HISTORY){
            //            printf("in HISTORY\n");
            if (strcmp(pack_recv.Msg, lastmessage) == 0) {//omg, mistook strcpy for strcmp, which result in my keeping wondering why the Msg is empty.
                //                printf("break because no new package\n");//
                break;
            }
            //            printf("pack_recv.UserName:'%s'\n", pack_recv.UserName);//
            //            printf("pack_recv.PacketLen:'%d'\n", (int)pack_recv.PacketLen);//
            //            printf("pack_recv.PacketType:'%d'\n", (int)pack_recv.PacketType);//
            printf("%s", pack_recv.Msg);//直接打印出本条消息记录
            fprintf(fp, "%s", pack_recv.Msg);//也写进了文件
            strcpy(lastmessage, pack_recv.Msg);
        }else{
            //            printf("break for receiving wrong type packet of type %d\n", pack_recv.PacketType);//
            break;
        }
    }
}
