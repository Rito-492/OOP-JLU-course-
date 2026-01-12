#include <iostream>
#include <string.h>
#include <winsock.h>
#include <windows.h>
#include <unistd.h>
#include <thread>
using namespace std;

#define Port 6666
#define BackLog 1024
#define BufferMax 256

void listen_sever(SOCKET, bool*);
void listen_stdin(SOCKET, bool*);

int main() {

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) < 0) {//第一个参数表示winsock的版本，本例使用的是winsock2.2版本。
        cout << "WSAStarup failed" << endl;
        return 0;
    }

    SOCKET client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == SOCKET_ERROR) {
        cout << "Scoket Error" << endl;
        return 0;
    }

    struct sockaddr_in client_addr;
    memset(&client_addr, 0x0, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = inet_addr("202.198.144.186");
    client_addr.sin_port = htons(Port);

    if (connect(client_socket, (struct sockaddr *)&client_addr, sizeof(client_addr)) < 0) {
        cout << "Connect failed" << endl;
    }
    bool isExit = false;
    thread thrdrec(listen_sever, client_socket, &isExit);
    thread thrdsnd(listen_stdin, client_socket, &isExit);
    thrdrec.join();
    thrdsnd.join();
    
    closesocket(client_socket);
    WSACleanup();
    return 0;
}

void listen_sever(SOCKET clnt_socket, bool* isExit) {
    char clnt_buf[BufferMax];
    while (!(*isExit)) {
        cout << *isExit << endl;
        memset(clnt_buf, 0, BufferMax);
        int bytes_received = recv(clnt_socket, clnt_buf, BufferMax, 0);
        if (strcmp(clnt_buf, "exit") == 0)
            break;
        if (bytes_received > 0) {
            cout << "Server: " << clnt_buf << endl;
        } else {
            cout << "Receive failed with error: " << WSAGetLastError() << endl;
        }
    }
}

void listen_stdin(SOCKET clnt_socket, bool* isExit) {
    char svr_buf[BufferMax];
    while (cin >> svr_buf) {
        if (send(clnt_socket, svr_buf, strlen(svr_buf), 0) < 0) {
            cout << "Send failed" << endl;
        }
        else {
            cout << "User: " << svr_buf << endl;
        }
        if (strcmp(svr_buf, "exit") == 0) {
            *isExit = true;
            break;
        }
    }
}