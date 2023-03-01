#include "property.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080

using namespace std;

struct Transaction {
    string sender;
    string receiver;
    int amount;
};

struct Block {
    int index;
    vector<Transaction> transactions;
    string prevHash;
    string currHash;
    int nonce;
};

map<int, Property> propertiesByID;
map<int, int> idToMoney;

void handleTransaction(int sockfd, Transaction tx) {
    // Verify transaction
    bool isValid = true;
    if (idToMoney[tx.sender] < tx.amount) {
        isValid = false;
    }
    if (isValid) {
        idToMoney[tx.sender] -= tx.amount;
        idToMoney[tx.receiver] += tx.amount;
        // Forward transaction to other nodes in network
        // ...
    }
}

void handleBlock(int sockfd, Block block) {
    // Verify block
    bool isValid = true;
    // Check prevHash and currHash consistency
    // Check nonce validity
    // Check transactions validity
    if (isValid) {
        // Add block to blockchain
        // ...
        // Forward block to other nodes in network
        // ...
    }
}

int main(){
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
                                 sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    while (true) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                       (socklen_t*)&addrlen))<0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        int option = 1;
        setsockopt(new_socket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

        char buffer[1024] = {0};
        read( new_socket , buffer, 1024);

        // Parse incoming message
        string message(buffer);
        if (message.substr(0, 11) == "Transaction") {
            string sender = message.substr(12, 6);
            string receiver = message.substr(20, 6);
            int amount = stoi(message.substr(28, message.size() - 29));
            Transaction tx = {sender, receiver, amount};
            handleTransaction(new_socket, tx);
        } else if (message.substr(0, 5) == "Block") {
            // Parse block
            // ...
            handleBlock(new_socket, block);
        }
        close(new_socket);
    }
    return 0;
}
