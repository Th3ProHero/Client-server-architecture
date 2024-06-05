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
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <IP> <puerto>\n", argv[0]);
        exit(1);
    }

    // Crear el socket del cliente
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Error al crear el socket");
        exit(1);
    }

    // Configurar la estructura de dirección del servidor
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));

    // Convertir la dirección IP de texto a binario
    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0) {
        perror("Error al convertir la dirección IP");
        close(sockfd);
        exit(1);
    }

    // Conectar al servidor
    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        perror("Error al conectar al servidor");
        close(sockfd);
        exit(1);
    }

    printf("Conectado al servidor %s:%s\n", argv[1], argv[2]);

    while (1) {
        // Leer el comando desde la entrada estándar
        char comando[MAX_BUFFER_SIZE];
        printf("Ingrese un comando: ");
        fgets(comando, sizeof(comando), stdin);

        // Eliminar el carácter de nueva línea de la entrada
        size_t len = strlen(comando);
        if (len > 0 && comando[len - 1] == '\n') {
            comando[len - 1] = '\0';
        }

        // Enviar el comando al servidor
        if (send(sockfd, comando, strlen(comando), 0) == -1) {
            perror("Error al enviar el comando al servidor");
            close(sockfd);
            exit(1);
        }

        // Recibir la salida del servidor
        char buffer[MAX_BUFFER_SIZE];
        memset(buffer, 0, sizeof(buffer));
        ssize_t bytesRecibidos = recv(sockfd, buffer, sizeof(buffer) - 1, 0);

        if (bytesRecibidos == -1) {
            perror("Error al recibir la salida del servidor");
            close(sockfd);
            exit(1);
        } else if (bytesRecibidos == 0) {
            // Servidor cerró la conexión
            printf("Conexión cerrada por el servidor.\n");
            break;
        }

        // Imprimir la salida del servidor
        printf("Salida del servidor:\n%s\n", buffer);
    }

    // Cerrar el socket del cliente
    close(sockfd);

    return 0;
}