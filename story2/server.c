/*注册登陆改用数据库实现的命令行版本191204*/
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
#include "Protocol.h"

#include <string.h>
#include <dlfcn.h>
#include <mysql.h>
#include <unistd.h>
#include <errno.h>
#include <termios.h>
#define STRING_SIZE 40
#define INSERT_SAMPLE "INSERT INTO UserInfo(accntfd,name,passwd) VALUES(?,?,?)"
#define SELECT_SAMPLE "SELECT * FROM UserInfo WHERE name = ?"

int             ret = 0;
MYSQL           *mysql;
MYSQL           *con;

#define COUNT 5//暂定只允许5个用户同时在线。数据库中存放所有用户的基本信息，account数组存放在线用户基本信息
#define SERVER_PORT 6666
//#define SERVER_ADDR "127.0.0.0"
#define SERVER_ADDR "0.0.0.0"//改成这个就不会bind error：Can't assign requested address了。

int socket_fd[COUNT]={-1,-1,-1,-1,-1};
int remain=COUNT;
int LoginSuccess = 0;
pthread_mutex_t remainmutex;


struct Account account[COUNT];
struct Packet pack_recv;
struct Packet pack_send;

void Register_Process(int fd);
void Login_Process(int fd);
void SendFile_Process(int fd);
void Chat_Process(int fd);


//每来一个客户就开一个线程
void* pthread_function(void* clientfd){
    
    InitPack(&pack_recv);
    InitPack(&pack_send);
    int i;
    int client_fd=*(int*)clientfd;
    
    
    pthread_mutex_lock(&remainmutex);
    if(remain>0)
        remain--;
    else pthread_exit(NULL);
    pthread_mutex_unlock(&remainmutex);
    
    
    
    if(recv(client_fd,&pack_recv, sizeof(pack_recv),0) == -1)
    {
        perror("recv error");
        pthread_exit(NULL);
    }
    switch(pack_recv.PacketType) {
        case REGISTER:
            Register_Process(client_fd);
            break;
        case LOGIN:
            Login_Process(client_fd);
            break;
        default:
            break;
    }
    
    
    
    //close socket and reset the fd -1
    close(client_fd);
    
    pthread_mutex_lock(&remainmutex);
    if(remain<COUNT)
        remain++;
    else pthread_exit(NULL);
    pthread_mutex_unlock(&remainmutex);
    for (i = 0; i < COUNT; ++i)
    {
        if(socket_fd[i]==client_fd)
            socket_fd[i]=-1;//reset the fd -1
        if(account[i].accntfd == client_fd)
            account[i].accntfd = -1;//reset the fd -1
    }
    pthread_exit(NULL);
    
    return ((void *)0);//
}


int main(){
    printf("listening...\n");
    int i;
    for(i = 0; i < COUNT; i++)
        account[i].accntfd = -1;//初始时所有用户都不在线
    pthread_mutex_init(&remainmutex,NULL);
    
    pthread_t tid;
    int sockfd,client_fd;
    socklen_t sin_size;
    struct sockaddr_in my_addr;
    struct sockaddr_in remote_addr;
    if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1){
        perror("socket");
        exit(1);
    }
    
    my_addr.sin_family=AF_INET;
    my_addr.sin_port=htons(SERVER_PORT);
    my_addr.sin_addr.s_addr=inet_addr(SERVER_ADDR);
    //    my_addr.sin_addr.s_addr=inet_addr(INADDR_ANY);
    bzero(&(my_addr.sin_zero), sizeof(my_addr.sin_addr));
    
    //解决在close之后会有一个WAIT_TIME，导致bind失败的问题
    int val = 1;
    int ret = setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,(void *)&val,sizeof(int));
    if(ret == -1){
        printf("setsockopt");
        exit(1);
    }
    
    if(bind(sockfd,(struct sockaddr*)&my_addr,sizeof(struct sockaddr))==-1){
        perror("bind");
        exit(1);
    }
    
    if(listen(sockfd,10)==-1){
        perror("listen");
        exit(1);
    }
    
    i=0;
    
    //主线程不断接受来自客户的连接
    while(1){
        sin_size=sizeof(struct sockaddr_in);
        if((client_fd=accept(sockfd,(struct sockaddr*)&remote_addr,&sin_size))==-1){
            perror("accept");
            exit(1);
        }
        if(remain>0){
            while(socket_fd[i]==-1)
                socket_fd[i]=client_fd;
            i=(i+1)%COUNT;
            pthread_create(&tid,NULL,pthread_function,(void*)&client_fd);//
        }
        else break;
    }
    
    pthread_mutex_destroy(&remainmutex);
    return 0;
}

void Register_Process(int fd){//注册
    struct Account account_tmp;
    recv(fd, &account_tmp, sizeof(account_tmp),0);
    
    account_tmp.accntfd = fd;//账户的socket
    account[COUNT - remain] = account_tmp;//新账户存入现有的账户数组中
    
    mysql = mysql_init(NULL);
    
    //连接到mysql server
    con = mysql_real_connect(mysql, "localhost", "root", "wxq987814762", "mysql", 0, NULL, 0 );
    if (con == NULL){
        printf("con error, %s\n", mysql_error(mysql));
//        return -1;
        exit(0);
    }
    
    ret = mysql_query(con, "SET NAMES utf8");       //设置字符集为UTF8
    if (ret != 0){
        printf("设置字符集错误, %s\n", mysql_error(mysql));
//        return ret;
        exit(0);
    }
    
    MYSQL_STMT    *stmt, *stmt2;
    MYSQL_BIND    bind[3];
    my_ulonglong  affected_rows;
    
    int           param_count;// total parameters in INSERT
    char          str_data1[STRING_SIZE];
    char          str_data2[STRING_SIZE];
    unsigned long str_length1;
    unsigned long str_length2;
    
    /* Prepare an SELECT query with 1 parameters */
    stmt = mysql_stmt_init(mysql); //初始化 预处理环境 生成一个预处理句柄
    if (!stmt){
        fprintf(stderr, " mysql_stmt_init(), out of memory\n");\
        exit(0);
    }
    
    if (mysql_stmt_prepare(stmt, SELECT_SAMPLE, strlen(SELECT_SAMPLE))) {//预处理环境中 准备sql
        fprintf(stderr, " mysql_stmt_prepare(), SELECT failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }
    
    /* Get the parameter count from the statement */
    param_count= (int)mysql_stmt_param_count(stmt);   //预处理环境中 求绑定变量的个数
    if (param_count != 1) /* validate parameter count */
    {
        fprintf(stderr, " invalid parameter count returned by MySQL\n");
        exit(0);
    }
    
    /* Bind the data for all the parameter */
    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type= MYSQL_TYPE_STRING;
    bind[0].buffer= (char *)str_data1;
    bind[0].buffer_length= STRING_SIZE;
    bind[0].is_null= 0;
    bind[0].length= &str_length1;
    
    /* Bind the buffers */
    if (mysql_stmt_bind_param(stmt, bind)) //把绑定变量设置到 预处理环境中
    {
        fprintf(stderr, " mysql_stmt_bind_param() failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }
    
    /* Specify the data values*/
    strncpy(str_data1, account_tmp.UserID, STRING_SIZE);
    str_length1= strlen(str_data1);
    
    /* Execute the INSERT statement - 1*/
    if (mysql_stmt_execute(stmt))
    {
        fprintf(stderr, " mysql_stmt_execute(), 1 failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }
    
    mysql_stmt_store_result(stmt);
    if(mysql_stmt_num_rows(stmt) != 0){
        char* tmp = "Sorry, this username has been taken! Please try another one.";
        setPack(&pack_send, REGISTER, strlen(tmp),"admin" ,tmp);
        send(fd, &pack_send, sizeof(pack_send), 0);
        return;
    }
    
    /* Close the statement */
    if (mysql_stmt_close(stmt))
    {
        fprintf(stderr, " failed while closing the statement\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }
    
    //插入新用户
    stmt2 = mysql_stmt_init(mysql); //初始化 预处理环境 生成一个预处理句柄
    if (!stmt2){
        fprintf(stderr, " mysql_stmt_init(), out of memory\n");\
        exit(0);
    }
    
    if (mysql_stmt_prepare(stmt2, INSERT_SAMPLE, strlen(INSERT_SAMPLE))) {//预处理环境中 准备sql
        fprintf(stderr, " mysql_stmt_prepare(), INSERT failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt2));
        exit(0);
    }
    
    /* Get the parameter count from the statement */
    param_count= (int)mysql_stmt_param_count(stmt2);   //预处理环境中 求绑定变量的个数
    if (param_count != 3) /* validate parameter count */
    {
        fprintf(stderr, " invalid parameter count returned by MySQL\n");
        exit(0);
    }
    
    /* Bind the data for all 3 parameters */
    int int_data = fd;//accntfd field
    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type= MYSQL_TYPE_LONG;  //为第一个绑定变量设置类型和 输入变量的内存首地址
    bind[0].buffer= (char *)&int_data;
    bind[0].is_null= 0;
    bind[0].length= 0;
    
    bind[1].buffer_type= MYSQL_TYPE_STRING;
    bind[1].buffer= (char *)str_data1;
    bind[1].buffer_length= STRING_SIZE;
    bind[1].is_null= 0;
    bind[1].length= &str_length1;
    
    bind[2].buffer_type= MYSQL_TYPE_STRING;
    bind[2].buffer= (char *)str_data2;
    bind[2].buffer_length= STRING_SIZE;
    bind[2].is_null= 0;
    bind[2].length= &str_length2;
    
    /* Bind the buffers */
    if (mysql_stmt_bind_param(stmt2, bind)) //把绑定变量设置到 预处理环境中
    {
        fprintf(stderr, " mysql_stmt_bind_param() failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt2));
        exit(0);
    }
    
//    int int_data = fd;//accntfd field
    strncpy(str_data1, account_tmp.UserID, STRING_SIZE);
    str_length1= strlen(str_data1);
    strncpy(str_data2, account_tmp.Passwd, STRING_SIZE);
    str_length2= strlen(str_data2);
    
    /* Execute the INSERT statement - 1*/
    if (mysql_stmt_execute(stmt2))
    {
        fprintf(stderr, " mysql_stmt_execute(), 1 failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt2));
        exit(0);
    }
    
    /* Get the total number of affected rows */
    affected_rows= mysql_stmt_affected_rows(stmt2);
    if (affected_rows != 1) /* validate affected rows */
    {
        fprintf(stderr, " invalid affected rows by MySQL\n");
        exit(0);
    }
    
    /* Close the statement */
    if (mysql_stmt_close(stmt2))
    {
        fprintf(stderr, " failed while closing the statement\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt2));
        exit(0);
    }
    mysql_close(con);      //断开与SQL server的连接
    
    
    //给用户发送注册成功提示
    char* tmp = "Registered!";
    setPack(&pack_send, REGISTER, strlen(tmp), "admin", tmp);
    //包类型为REGISTER（头文件里定义为1），长度是字符串tmp的长度，发送人是admin，消息是tmp
    send(fd, &pack_send, sizeof(pack_send), 0);//发送给新注册的用户
    LoginSuccess = 1;
    if(recv(fd,&pack_recv, sizeof(pack_recv),0) == -1){
        perror("recv error");
        exit(1);
    }
    sleep(1);
    switch(pack_recv.PacketType){
        case CHAT:
            Chat_Process(fd);
            break;
        case SENDFILE:
            SendFile_Process(fd);
            break;
        case EXIT:
            break;
        default:
            break;
    }
}

void Login_Process(int fd){//登陆
    struct Account account_tmp;
    char *tmp = NULL;
    recv(fd, &account_tmp, sizeof(account_tmp), 0);
    
    
    mysql = mysql_init(NULL);
    con = mysql_real_connect(mysql, "localhost", "root", "wxq987814762", "mysql", 0, NULL, 0 );
    if (con == NULL){
        printf("con error, %s\n", mysql_error(mysql));
        exit(0);
    }
    
    ret = mysql_query(con, "SET NAMES utf8");       //设置字符集为UTF8
    if (ret != 0){
        printf("设置字符集错误, %s\n", mysql_error(mysql));
        exit(0);
    }
    
    MYSQL_STMT    *stmt;
    MYSQL_BIND    bind[1];
    
//    int           param_count;
    char          str_data1[STRING_SIZE];
    unsigned long str_length1;
    
    /* Prepare an SELECT query with 1 parameters */
    stmt = mysql_stmt_init(mysql); //初始化 预处理环境 生成一个预处理句柄
    if (!stmt){
        fprintf(stderr, " mysql_stmt_init(), out of memory\n");\
        exit(0);
    }
    
    if (mysql_stmt_prepare(stmt, SELECT_SAMPLE, strlen(SELECT_SAMPLE))) {//预处理环境中 准备sql
        fprintf(stderr, " mysql_stmt_prepare(), SELECT failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }

    /* Get the parameter count from the statement */
//    param_count= (int)mysql_stmt_param_count(stmt);   //预处理环境中 求绑定变量的个数
//    if (param_count != 1) /* validate parameter count */
//    {
//        fprintf(stderr, " invalid parameter count returned by MySQL\n");
//        exit(0);
//    }
    
    /* Bind the data for all the parameter */
    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type= MYSQL_TYPE_STRING;
    bind[0].buffer= (char *)str_data1;
    bind[0].buffer_length= STRING_SIZE;
    bind[0].is_null= 0;
    bind[0].length= &str_length1;
    
    /* Bind the buffers */
    if (mysql_stmt_bind_param(stmt, bind)) //把绑定变量设置到 预处理环境中
    {
        fprintf(stderr, " mysql_stmt_bind_param() failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }
    
    /* Specify the data values*/
    strncpy(str_data1, account_tmp.UserID, STRING_SIZE);
    str_length1= strlen(str_data1);
    
    
    
    //绑定查询结果
    int rec_accntfd = 0;
    char rec_name[40] = {0};
    char rec_passwd[40] = {0};
    MYSQL_BIND result[3];
    memset(result, 0, sizeof(result));
    result[0].buffer_type = MYSQL_TYPE_LONG;
    result[0].buffer = &rec_accntfd;
    result[1].buffer_type = MYSQL_TYPE_STRING;
    result[1].buffer = rec_name;
    result[1].buffer_length = sizeof(rec_name);
    result[2].buffer_type = MYSQL_TYPE_STRING;
    result[2].buffer = rec_passwd;
    result[2].buffer_length = sizeof(rec_passwd);
    mysql_stmt_bind_result(stmt, result); //用于将结果集中的列与数据缓冲和长度缓冲关联（绑定）起来

    /* Execute the INSERT statement - 1*/
    if (mysql_stmt_execute(stmt))
    {
        fprintf(stderr, " mysql_stmt_execute(), 1 failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }
    
    mysql_stmt_store_result(stmt);
    if(mysql_stmt_num_rows(stmt) == 0){//数据库中没有此用户
        LoginSuccess = 0;
        tmp = "Login Failed! Username does not exist!";
    }else{
        mysql_stmt_fetch(stmt);
        if (strcmp(rec_passwd, account_tmp.Passwd) == 0) {//密码匹配
            int i;
            for (i = 0; i < COUNT; i++){//看是否在account数组中
                if (strcmp(account_tmp.UserID, account[i].UserID) == 0) {//若在
                    if(account[i].accntfd == -1) {//不在线
                        tmp = "Login Successfully!";
                        LoginSuccess = 1;
                        account[i].accntfd = fd;
                        break;
                    }else{//已经在线
                        tmp = "Someone has already logged in with your account before!";
                        LoginSuccess = 0;
                        break;
                    }
                }
            }
            if (i == COUNT) {//若不在account数组中，则加入account数组中
//                LoginSuccess = 0;
//                tmp = "Login Failed! Check your Username and Password!";
                tmp = "Login Successfully!";
                LoginSuccess = 1;
                account_tmp.accntfd = fd;
                account[COUNT - remain] = account_tmp;
            }
            
//            if (rec_accntfd == -1) {
//                tmp = "Login Successfully!";
//                LoginSuccess = 1;
//                //            account[i].accntfd = fd;
//            }else{
//                tmp = "Someone has already logged in with your account before!";
//                LoginSuccess = 0;
//            }
        }else{
            LoginSuccess = 0;
            tmp = "Login Failed! Check your password!";
        }
    }
    
    /* Close the statement */
    if (mysql_stmt_close(stmt))
    {
        fprintf(stderr, " failed while closing the statement\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(0);
    }
    mysql_close(con);
    
    //给用户发送登陆是否成功的消息
    setPack(&pack_send, LOGIN, strlen(tmp),"admin", tmp);//Thread 2: EXC_BAD_ACCESS
    send(fd, &pack_send, sizeof(pack_send), 0);
    
    if (LoginSuccess) {
        recv(fd, &pack_recv, sizeof(pack_recv), 0);
        switch(pack_recv.PacketType){
            case CHAT:
                Chat_Process(fd);
                break;
            case SENDFILE:
                SendFile_Process(fd);
                break;
            case EXIT:
                break;
            default:
                break;
        }
    }
}

void Chat_Process(int fd){
    long recvbytes;
    int i;
    int option;
    int choice;
    char userlist[140];
    char* plen = userlist;
    recv(fd, &option, sizeof(option), 0);
    if(option == 1) {
        for(i = 0; i < COUNT; i++){
            memcpy(plen, &account[i], 28);//把用户信息逐个复制到plen指向的内存中（每个account占28个字节）
            plen += 28;
        }
        if(send(fd, userlist, 140, 0) == -1){//发送用户列表
            perror("send");
        }
        recv(fd, &choice, sizeof(choice), 0);
    }
    while (1) {
        if ((recvbytes = recv(fd, &pack_recv, sizeof(pack_recv), 0)) == -1) {
            perror("recv");
            pthread_exit(NULL);
        }
        
        if (recvbytes == 0) {
            for(i = 0; i < COUNT; i++){
                if(account[i].accntfd == fd)
                    break;
            }
            printf("User %s has disconnected!\n",account[i].UserID);
            break;
        }
        if (pack_recv.PacketType == CHAT) {
            if (option == 1) {
                int tmpclient = account[choice-1].accntfd;
                if (tmpclient != -1) {
                    pack_send = pack_recv;
                    if (send(tmpclient, &pack_send, sizeof(pack_send), 0) == -1)
                        perror("send error");
                }
            }
            else if(option == 2){
                int tmpclient;
                for(i = 0; i < COUNT; i++) {
                    tmpclient = socket_fd[i];
                    if (tmpclient != -1) {
                        pack_send = pack_recv;
                        if (send(tmpclient, &pack_send, sizeof(pack_send), 0) == -1)
                            perror("send error");
                    }
                }
            }
        }
    }
}

void SendFile_Process(int fd){
    
}



