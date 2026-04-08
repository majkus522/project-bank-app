#include <iostream>
#include <cstring>

#ifdef _WIN32
    #include <winsock2.h>
    #pragma comment(lib, "ws2_32.lib")
    typedef int socklen_t;
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>
#endif

#ifdef _WIN32
    #define GET_ERROR() WSAGetLastError()
#else
    #include <errno.h>
    #define GET_ERROR() errno
#endif

#ifdef _WIN32
    #include <winsock2.h>
    #pragma comment(lib, "ws2_32.lib")
#else
    #include <arpa/inet.h>
    #include <sys/socket.h>
    #include <unistd.h>
    #include <ifaddrs.h>
    #include <arpa/inet.h>
    #include <netinet/in.h>
#endif

#include <iostream>
#include <string>
#include <cstring>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#endif

std::string getPrimaryIP() {
#ifdef _WIN32
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);
#endif

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) return "Socket error";

    sockaddr_in serv{};
    serv.sin_family = AF_INET;
    serv.sin_port = htons(80);

    inet_pton(AF_INET, "8.8.8.8", &serv.sin_addr);

    connect(sock, (sockaddr*)&serv, sizeof(serv));

    sockaddr_in name{};
#ifdef _WIN32
    int len = sizeof(name);
#else
    socklen_t len = sizeof(name);
#endif

    getsockname(sock, (sockaddr*)&name, &len);

    char buf[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &name.sin_addr, buf, sizeof(buf));

#ifdef _WIN32
    closesocket(sock);
    WSACleanup();
#else
    close(sock);
#endif

    return std::string(buf);
}

int main()
{
    std::cout << "Primary IP: " << getPrimaryIP() << "\n";

#ifdef _WIN32
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        std::cout << "WSAStartup failed\n";
        return 1;
    }
#endif

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        std::cout << "Socket creation failed\n";
        return 1;
    }

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8083);

    // 🔥 This is CRITICAL on Windows (prevents "address already in use")
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

    if (bind(server_fd, (sockaddr*)&address, sizeof(address)) < 0) {
        std::cout << "Bind failed! Error: " << GET_ERROR() << "\n";
        return 1;
    }

    if (listen(server_fd, 3) < 0) {
        std::cout << "Listen failed\n";
        return 1;
    }

    std::cout << "Waiting for connection on port 8083...\n";

    socklen_t addrlen = sizeof(address);
    int client_socket = accept(server_fd, (sockaddr*)&address, &addrlen);

    if (client_socket < 0) {
        std::cout << "Accept failed! Error: " << GET_ERROR() << "\n";
        return 1;
    }

    std::cout << "Client connected!\n";

    char buffer[1024] = {0};
    recv(client_socket, buffer, sizeof(buffer), 0);
    std::cout << "Client says: " << buffer << std::endl;

    const char* reply = "Hello from server!";
    send(client_socket, reply, strlen(reply), 0);

#ifdef _WIN32
    closesocket(client_socket);
    WSACleanup();
#else
    close(client_socket);
#endif
}