#include "common.h"

#ifdef _WIN32
    #include <windows.h>
    DWORD WINAPI receive_messages(LPVOID socket_desc);
#else
    #include <pthread.h>
    void* receive_messages(void* socket_desc);
#endif

int running = 1;

#ifdef _WIN32
DWORD WINAPI receive_messages(LPVOID socket_desc) {
    SOCKET sock = *(SOCKET*)socket_desc;
#else
void* receive_messages(void* socket_desc) {
    SOCKET sock = *(SOCKET*)socket_desc;
#endif
    char buffer[BUFFER_SIZE];
    
    while (running) {
        int bytes_received = recv(sock, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_received <= 0) {
            printf("\nDesconectado del servidor.\n");
            running = 0;
            break;
        }
        buffer[bytes_received] = '\0';
        printf("%s", buffer);
        fflush(stdout);
    }

    return 0;
}

int main(int argc, char *argv[]) {
    #ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Error en WSAStartup\n");
        return 1;
    }
    #endif

    char *server_ip = "127.0.0.1";
    if (argc > 1) {
        server_ip = argv[1];
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        perror("Error creando socket");
        return 1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, server_ip, &server_addr.sin_addr);

    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        perror("Error conectando al servidor");
        closesocket(sock);
        return 1;
    }

    char name[50];
    printf("Ingresa tu nombre de usuario: ");
    if (fgets(name, sizeof(name), stdin) != NULL) {
        name[strcspn(name, "\n")] = 0;
    } else {
        strcpy(name, "Anónimo");
    }

    printf("Conectado al chat. Escribe tus mensajes (Escribe 'SALIR' para salir):\n");

    // Hilo para recibir mensajes
#ifdef _WIN32
    DWORD thread_id;
    HANDLE thread = CreateThread(NULL, 0, receive_messages, &sock, 0, &thread_id);
    if (thread == NULL) {
        printf("Error creando hilo\n");
        closesocket(sock);
        return 1;
    }
#else
    pthread_t thread;
    if (pthread_create(&thread, NULL, receive_messages, &sock) != 0) {
        perror("Error creando hilo");
        closesocket(sock);
        return 1;
    }
#endif

    char input[BUFFER_SIZE - 150];
    char message[BUFFER_SIZE * 2];

    while (running) {
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "SALIR") == 0) {
            running = 0;
            break;
        }

        if (strlen(input) == 0) {
            continue;
        }

        snprintf(message, sizeof(message), "[%s]: %s\n", name, input);
        int send_res = send(sock, message, strlen(message), 0);
        if (send_res == SOCKET_ERROR) {
            printf("Error al enviar mensaje.\n");
            break;
        }
    }

    closesocket(sock);

#ifdef _WIN32
    WaitForSingleObject(thread, INFINITE);
    CloseHandle(thread);
    WSACleanup();
#else
    pthread_join(thread, NULL);
#endif

    return 0;
}
