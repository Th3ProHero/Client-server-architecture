#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <puerto>\n", argv[0]);
        exit(1);
    }

    // Crear el socket del servidor
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Error al crear el socket");
        exit(1);
    }

    // Configurar la estructura de dirección del servidor
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[1]));
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    // Vincular el socket a la dirección y puerto
    if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        perror("Error al vincular el socket");
        close(sockfd);
        exit(1);
    }

    // Poner el socket en estado de escucha
    if (listen(sockfd, 5) == -1) {
        perror("Error al poner el socket en estado de escucha");
        close(sockfd);
        exit(1);
    }

    printf("Servidor esperando conexiones en el puerto %s...\n", argv[1]);

    while (1) {
        // Aceptar una conexión entrante
        int clientfd = accept(sockfd, NULL, NULL);
        if (clientfd == -1) {
            perror("Error al aceptar la conexión");
            close(sockfd);
            exit(1);
        }

        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        if (getpeername(clientfd, (struct sockaddr*)&client_addr, &client_addr_len) == -1) {
            perror("Error al obtener la dirección del cliente");
            close(clientfd);
            close(sockfd);
            exit(1);
        }

        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip));

        printf("Cliente conectado desde %s:%d\n", client_ip, ntohs(client_addr.sin_port));

        while (1) {
            // Recibir el comando del cliente
            char comando[MAX_BUFFER_SIZE];
            memset(comando, 0, sizeof(comando));
            ssize_t bytesRecibidos = recv(clientfd, comando, sizeof(comando) - 1, 0);

            if (bytesRecibidos == -1) {
                perror("Error al recibir el comando del cliente");
                close(clientfd);
                close(sockfd);
                exit(1);
            } else if (bytesRecibidos == 0) {
                // Conexión cerrada por el cliente
                printf("Cliente desconectado desde %s:%d.\n", client_ip, ntohs(client_addr.sin_port));
                close(clientfd);
                break;
            }
			
			// Verificar si el cliente envió "exit"
            if (strcmp(comando, "exit") == 0) {
                printf("Cliente %s:%d solicitó cerrar la conexión.\n", client_ip, ntohs(client_addr.sin_port));
                close(clientfd);
                break;
            }

            // Ejecutar el comando y capturar la salida
            FILE *fp = popen(comando, "r");
            if (fp == NULL) {
                perror("Error al ejecutar el comando");
                close(clientfd);
                close(sockfd);
                exit(1);
            }

            // Leer la salida del comando
            char buffer[MAX_BUFFER_SIZE];
            memset(buffer, 0, sizeof(buffer));
            size_t bytesRead = fread(buffer, 1, sizeof(buffer) - 1, fp);

            // Enviar la salida al cliente
            if (send(clientfd, buffer, bytesRead, 0) == -1) {
                perror("Error al enviar la salida al cliente");
                close(clientfd);
                close(sockfd);
                pclose(fp);
                exit(1);
            }

            // Imprimir en la terminal del servidor que se envió la respuesta
            printf("Enviada respuesta al cliente %s:%d:\n%s\n", client_ip, ntohs(client_addr.sin_port), buffer);

            // Cerrar el descriptor de archivo del comando
            pclose(fp);
        }
    }

    // Cerrar el socket del servidor (esto nunca se alcanza en este bucle infinito)
    close(sockfd);

    return 0;
}
