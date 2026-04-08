#include <iostream>
#include <cstring>

#ifdef _WIN32
    #include <winsock2.h>
    #pragma comment(lib, "ws2_32.lib")
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>
#endif

int main()
{
    #ifdef _WIN32
        WSADATA wsa;
        WSAStartup(MAKEWORD(2,2), &wsa);
    #endif

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8083);

#ifdef _WIN32
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
#else
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
#endif

    connect(sock, (sockaddr*)&serv_addr, sizeof(serv_addr));

    const char* msg = "Hello from client!";
    send(sock, msg, strlen(msg), 0);

    char buffer[1024] = {0};
    recv(sock, buffer, sizeof(buffer), 0);
    std::cout << "Server says: " << buffer << std::endl;

    #ifdef _WIN32
        closesocket(sock);
        WSACleanup();
    #else
        close(sock);
    #endif
}