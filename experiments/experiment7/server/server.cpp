#include <iostream>
#include <winsock.h>
#include <windows.h>
#include <unistd.h>
#include <thread>
using namespace std;

#define Port 6666
#define BackLog 1024
#define BufferMax 256

void listen_client(int);
void listen_stdin(int);

int main() {

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) < 0) {//第一个参数表示winsock的版本，本例使用的是winsock2.2版本。
        cout << "WSAStarup failed" << endl;
        return 0;
    }
    
    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        cout << "Socket Error" << endl;
        return 0;
    }

    struct sockaddr_in socket_addr;
    memset(&socket_addr, 0x0, sizeof(socket_addr)); //清零
    socket_addr.sin_family = AF_INET;
    socket_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    socket_addr.sin_port = htons(Port);
    //将地址与套接字进行关联、绑定

    if (bind(server_socket, (struct sockaddr *)&socket_addr, sizeof(socket_addr)) < 0) {
        cout << "Bind failed" << endl;
    }

    if (listen(server_socket, BackLog) < 0) {
        cout << "Listen Failed" << endl;
    }

    SOCKET client_socket;
    struct sockaddr_in client_addr;
    int len = sizeof (client_addr);
    if ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &len)) < 0) {
        cout << "Accept failed" << endl;
    }

    
    char svr_buf[BufferMax] = "";
    if (send(client_socket, svr_buf, strlen(svr_buf), 0) < 0) {
        cout << "Send failed" << endl;
    }
    else {
        cout << "Server: I'm the server.You can send messages now." << endl;
    }

    thread thrdrec(listen_client, client_socket);
    thread thrdsnd(listen_stdin, client_socket);
    thrdrec.join();
    thrdsnd.join();

    closesocket(server_socket);
    closesocket(client_socket);
    WSACleanup();
    return 0;
}

void listen_client(int clnt_socket) {
    char clnt_buf[BufferMax];
    while (true) {
        memset(clnt_buf, 0, BufferMax);
        int bytes_received = recv(clnt_socket, clnt_buf, BufferMax, 0);
        if (strcmp(clnt_buf, "exit") == 0)
            break;
        if (bytes_received > 0) {
            cout << "User: " << clnt_buf << endl;
        } else {
            cout << "Receive failed with error: " << WSAGetLastError() << endl;
        }
    }
}

void listen_stdin(int clnt_socket) {
    char svr_buf[BufferMax];
    while (cin >> svr_buf) {
        if (send(clnt_socket, svr_buf, strlen(svr_buf), 0) < 0) {
            cout << "Send failed" << endl;
        }
        else {
            cout << "Server: " << svr_buf << endl;
        }
        if (strcmp(svr_buf, "exit") == 0)
            break;
    }
}