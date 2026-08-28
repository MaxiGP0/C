#include "common.h"
#include <raylib.h>

#ifdef _WIN32
    #include <windows.h>
    DWORD WINAPI receive_messages(LPVOID socket_desc);
    CRITICAL_SECTION mutex;
#else
    #include <pthread.h>
    void* receive_messages(void* socket_desc);
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
#endif

#define MAX_MESSAGES 100
#define MSG_LEN 256

char chat_history[MAX_MESSAGES][MSG_LEN];
int message_count = 0;

SOCKET sock = INVALID_SOCKET;
int connected = 0;
int running_thread = 0;

void add_message(const char* msg) {
#ifdef _WIN32
    EnterCriticalSection(&mutex);
#else
    pthread_mutex_lock(&mutex);
#endif

    if (message_count < MAX_MESSAGES) {
        snprintf(chat_history[message_count], MSG_LEN, "%s", msg);
        message_count++;
    } else {
        // Shift messages up
        for (int i = 0; i < MAX_MESSAGES - 1; i++) {
            strcpy(chat_history[i], chat_history[i + 1]);
        }
        snprintf(chat_history[MAX_MESSAGES - 1], MSG_LEN, "%s", msg);
    }

#ifdef _WIN32
    LeaveCriticalSection(&mutex);
#else
    pthread_mutex_unlock(&mutex);
#endif
}

#ifdef _WIN32
DWORD WINAPI receive_messages(LPVOID socket_desc) {
    SOCKET s = *(SOCKET*)socket_desc;
#else
void* receive_messages(void* socket_desc) {
    SOCKET s = *(SOCKET*)socket_desc;
#endif
    char buffer[BUFFER_SIZE];

    while (running_thread) {
        int bytes = recv(s, buffer, BUFFER_SIZE - 1, 0);
        if (bytes <= 0) {
            add_message("[Sistema]: Desconectado del servidor.");
            connected = 0;
            break;
        }
        buffer[bytes] = '\0';
        add_message(buffer);
    }
    return 0;
}

int main() {
    #ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    InitializeCriticalSection(&mutex);
    #endif

    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Chat C - Raylib GUI");
    SetTargetFPS(60);

    char ip_text[64] = "127.0.0.1";
    char name_text[32] = "Usuario";
    char msg_text[256] = "";
    
    bool ip_edit_mode = false;
    bool name_edit_mode = false;
    bool msg_edit_mode = false;

#ifdef _WIN32
    HANDLE thread = NULL;
#else
    pthread_t thread;
#endif

    while (!WindowShouldClose()) {
        // --- LOGIC / INPUT ---
        // Check mouse clicks for text boxes and buttons
        Vector2 mousePoint = GetMousePosition();

        // Rectangles for UI
        Rectangle ipBox = { 120, 20, 200, 30 };
        Rectangle nameBox = { 460, 20, 150, 30 };
        Rectangle connectBtn = { 630, 20, 140, 30 };

        Rectangle chatBox = { 20, 70, 760, 430 };
        Rectangle msgBox = { 20, 520, 630, 40 };
        Rectangle sendBtn = { 660, 520, 120, 40 };

        // Handle text box focus and typing
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            ip_edit_mode = CheckCollisionPointRec(mousePoint, ipBox);
            name_edit_mode = CheckCollisionPointRec(mousePoint, nameBox);
            msg_edit_mode = CheckCollisionPointRec(mousePoint, msgBox);
        }

        // Handle IP Text Input
        if (ip_edit_mode) {
            int key = GetCharPressed();
            while (key > 0) {
                if ((key >= 32) && (key <= 125) && (strlen(ip_text) < sizeof(ip_text) - 1)) {
                    int len = strlen(ip_text);
                    ip_text[len] = (char)key;
                    ip_text[len + 1] = '\0';
                }
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE)) {
                int len = strlen(ip_text);
                if (len > 0) ip_text[len - 1] = '\0';
            }
        }

        // Handle Name Text Input
        if (name_edit_mode) {
            int key = GetCharPressed();
            while (key > 0) {
                if ((key >= 32) && (key <= 125) && (strlen(name_text) < sizeof(name_text) - 1)) {
                    int len = strlen(name_text);
                    name_text[len] = (char)key;
                    name_text[len + 1] = '\0';
                }
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE)) {
                int len = strlen(name_text);
                if (len > 0) name_text[len - 1] = '\0';
            }
        }

        // Handle Message Text Input
        if (msg_edit_mode) {
            int key = GetCharPressed();
            while (key > 0) {
                if ((key >= 32) && (key <= 125) && (strlen(msg_text) < sizeof(msg_text) - 1)) {
                    int len = strlen(msg_text);
                    msg_text[len] = (char)key;
                    msg_text[len + 1] = '\0';
                }
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE)) {
                int len = strlen(msg_text);
                if (len > 0) msg_text[len - 1] = '\0';
            }
        }

        // Connect Button Click
        if (CheckCollisionPointRec(mousePoint, connectBtn) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (!connected) {
                // Connect to server
                sock = socket(AF_INET, SOCK_STREAM, 0);
                if (sock != INVALID_SOCKET) {
                    struct sockaddr_in server_addr;
                    memset(&server_addr, 0, sizeof(server_addr));
                    server_addr.sin_family = AF_INET;
                    server_addr.sin_port = htons(PORT);
                    inet_pton(AF_INET, ip_text, &server_addr.sin_addr);

                    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) != SOCKET_ERROR) {
                        connected = 1;
                        running_thread = 1;
                        add_message("[Sistema]: Conectado exitosamente.");

#ifdef _WIN32
                        DWORD thread_id;
                        thread = CreateThread(NULL, 0, receive_messages, &sock, 0, &thread_id);
#else
                        pthread_create(&thread, NULL, receive_messages, &sock);
#endif
                    } else {
                        add_message("[Sistema]: Error al conectar con el servidor.");
                        closesocket(sock);
                    }
                }
            } else {
                // Disconnect (Abandonar)
                running_thread = 0;
                if (sock != INVALID_SOCKET) {
                    closesocket(sock);
                    sock = INVALID_SOCKET;
                }
                connected = 0;
                add_message("[Sistema]: Desconectado manualmente.");
            }
        }

        // Send Message Button or Enter key
        if (connected && ((CheckCollisionPointRec(mousePoint, sendBtn) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) || (msg_edit_mode && IsKeyPressed(KEY_ENTER)))) {
            if (strlen(msg_text) > 0) {
                char full_msg[BUFFER_SIZE];
                snprintf(full_msg, sizeof(full_msg), "[%s]: %s\n", name_text, msg_text);
                send(sock, full_msg, strlen(full_msg), 0);

                // Show own message in chat
                char self_msg[BUFFER_SIZE];
                snprintf(self_msg, sizeof(self_msg), "Tú: %s", msg_text);
                add_message(self_msg);

                msg_text[0] = '\0';
                msg_edit_mode = false;
            }
        }

        // --- DRAWING ---
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Top bar: IP, Name, Connect Button
        DrawText("IP Servidor:", 20, 26, 18, DARKGRAY);
        DrawRectangleRec(ipBox, LIGHTGRAY);
        if (ip_edit_mode) DrawRectangleLines((int)ipBox.x, (int)ipBox.y, (int)ipBox.width, (int)ipBox.height, BLUE);
        DrawText(ip_text, (int)ipBox.x + 5, (int)ipBox.y + 6, 18, BLACK);

        DrawText("Nombre:", 390, 26, 18, DARKGRAY);
        DrawRectangleRec(nameBox, LIGHTGRAY);
        if (name_edit_mode) DrawRectangleLines((int)nameBox.x, (int)nameBox.y, (int)nameBox.width, (int)nameBox.height, BLUE);
        DrawText(name_text, (int)nameBox.x + 5, (int)nameBox.y + 6, 18, BLACK);

        // Connect / Disconnect button
        DrawRectangleRec(connectBtn, connected ? RED : GREEN);
        DrawText(connected ? "Abandonar" : "Conectar", (int)connectBtn.x + 25, (int)connectBtn.y + 6, 18, WHITE);

        // Chat History Box
        DrawRectangleRec(chatBox, WHITE);
        DrawRectangleLines((int)chatBox.x, (int)chatBox.y, (int)chatBox.width, (int)chatBox.height, DARKGRAY);

        // Render messages
#ifdef _WIN32
        EnterCriticalSection(&mutex);
#else
        pthread_mutex_lock(&mutex);
#endif

        int start_idx = message_count > 20 ? message_count - 20 : 0;
        int y_offset = (int)chatBox.y + 10;
        for (int i = start_idx; i < message_count; i++) {
            DrawText(chat_history[i], (int)chatBox.x + 10, y_offset, 16, DARKGRAY);
            y_offset += 20;
        }

#ifdef _WIN32
        LeaveCriticalSection(&mutex);
#else
        pthread_mutex_unlock(&mutex);
#endif

        // Bottom bar: Message input and Send button
        DrawRectangleRec(msgBox, LIGHTGRAY);
        if (msg_edit_mode) DrawRectangleLines((int)msgBox.x, (int)msgBox.y, (int)msgBox.width, (int)msgBox.height, BLUE);
        DrawText(msg_text, (int)msgBox.x + 5, (int)msgBox.y + 11, 18, BLACK);

        DrawRectangleRec(sendBtn, connected ? BLUE : GRAY);
        DrawText("Enviar", (int)sendBtn.x + 35, (int)sendBtn.y + 11, 18, WHITE);

        EndDrawing();
    }

    // Cleanup
    running_thread = 0;
    if (sock != INVALID_SOCKET) {
        closesocket(sock);
    }

#ifdef _WIN32
    DeleteCriticalSection(&mutex);
    WSACleanup();
#endif

    CloseWindow();
    return 0;
}
