#include "common.h"
#include <signal.h>

#define MAX_CLIENTS 10

SOCKET server_socket = INVALID_SOCKET;
int running = 1;

void handle_sigint(int sig) {
    (void)sig;
    printf("\nCerrando servidor...\n");
    running = 0;
    if (server_socket != INVALID_SOCKET) {
        closesocket(server_socket);
    }
    #ifdef _WIN32
    WSACleanup();
    #endif
    exit(0);
}

int main() {
    #ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Error en WSAStartup\n");
        return 1;
    }
    #endif

    signal(SIGINT, handle_sigint);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        perror("Error creando socket");
        return 1;
    }

    int opt = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        perror("Error en bind");
        closesocket(server_socket);
        return 1;
    }

    if (listen(server_socket, 5) == SOCKET_ERROR) {
        perror("Error en listen");
        closesocket(server_socket);
        return 1;
    }

    printf("Servidor de chat iniciado en el puerto %d...\n", PORT);

    SOCKET client_sockets[MAX_CLIENTS];
    for (int i = 0; i < MAX_CLIENTS; i++) {
        client_sockets[i] = INVALID_SOCKET;
    }

    while (running) {
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(server_socket, &readfds);

        SOCKET max_fd = server_socket;

        for (int i = 0; i < MAX_CLIENTS; i++) {
            SOCKET sd = client_sockets[i];
            if (sd != INVALID_SOCKET) {
                FD_SET(sd, &readfds);
                if (sd > max_fd) {
                    max_fd = sd;
                }
            }
        }

        int activity = select((int)(max_fd + 1), &readfds, NULL, NULL, NULL);

        if ((activity < 0) && (errno != EINTR)) {
            perror("Error en select");
            break;
        }

        // Nueva conexión entrante
        if (FD_ISSET(server_socket, &readfds)) {
            struct sockaddr_in client_addr;
            socklen_t addr_len = sizeof(client_addr);
            SOCKET new_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_len);
            
            if (new_socket == INVALID_SOCKET) {
                perror("Error en accept");
            } else {
                char client_ip[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, &(client_addr.sin_addr), client_ip, INET_ADDRSTRLEN);
                printf("Nueva conexion desde %s:%d (socket %d)\n", client_ip, ntohs(client_addr.sin_port), (int)new_socket);

                // Agregar a la lista de clientes
                int added = 0;
                for (int i = 0; i < MAX_CLIENTS; i++) {
                    if (client_sockets[i] == INVALID_SOCKET) {
                        client_sockets[i] = new_socket;
                        added = 1;
                        break;
                    }
                }

                if (!added) {
                    printf("Servidor lleno. Conexion rechazada.\n");
                    char *msg = "Servidor lleno. Desconectando...\n";
                    send(new_socket, msg, strlen(msg), 0);
                    closesocket(new_socket);
                }
            }
        }

        // Datos de clientes existentes
        for (int i = 0; i < MAX_CLIENTS; i++) {
            SOCKET sd = client_sockets[i];

            if (sd != INVALID_SOCKET && FD_ISSET(sd, &readfds)) {
                char buffer[BUFFER_SIZE];
                int valread = recv(sd, buffer, BUFFER_SIZE - 1, 0);

                if (valread <= 0) {
                    // Cliente desconectado
                    struct sockaddr_in addr;
                    socklen_t addr_len = sizeof(addr);
                    getpeername(sd, (struct sockaddr*)&addr, &addr_len);
                    printf("Cliente desconectado (socket %d)\n", (int)sd);

                    closesocket(sd);
                    client_sockets[i] = INVALID_SOCKET;
                } else {
                    buffer[valread] = '\0';
                    // Reenviar mensaje a todos los demás clientes
                    printf("Mensaje recibido de socket %d: %s", (int)sd, buffer);
                    
                    for (int j = 0; j < MAX_CLIENTS; j++) {
                        SOCKET dest_sd = client_sockets[j];
                        if (dest_sd != INVALID_SOCKET && dest_sd != sd) {
                            send(dest_sd, buffer, valread, 0);
                        }
                    }
                }
            }
        }
    }

    #ifdef _WIN32
    WSACleanup();
    #endif

    return 0;
}
