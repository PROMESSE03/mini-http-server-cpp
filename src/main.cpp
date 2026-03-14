#include <iostream>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main() {
    // 1) Créer la socket serveur
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd == -1) {
        std::cerr << "Erreur lors de la création de la socket" << std::endl;
        return 1;
    }

    int opt = 1; 
    if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        std::cerr << "Erreur lors de la configuration de la socket" << std::endl;
        close(server_fd);
        return 1;
    }

    // 2) Configurer l'adresse du serveur
    sockaddr_in address {};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    // 3) Lier la socket au port
    if(bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "Erreur lors du bind de la socket" << std::endl;
        close(server_fd);
        return 1;
    }

    // 4 ) Écouter les connexions entrantes
    if(listen(server_fd, 5) < 0) {
        std::cerr << "Erreur lors de l'écoute des connexions" << std::endl;
        close(server_fd);
        return 1;
    }

    std::cout << "Notre serveur est en écoute sur le port 8080..." << std::endl;
    
    while (true)
    {
        /* code */
    }

    close(server_fd);
    return 0;
    
}