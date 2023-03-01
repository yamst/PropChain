#include <iostream>
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

int sockfd;

void sendTransaction(Transaction tx) {
    string message = "Transaction " + tx.sender + " " + tx.receiver + " " + to_string(tx.amount);
    send(sockfd, message.c_str(), message.length(), 0);
}

void handleBlock(string message) {
    // Parse block
    // ...
    // Add block to local blockchain
    // ...
}

void receiveUpdates() {
    char buffer[1024] = {0};
    while (true) {
        int bytesReceived = recv(sockfd, buffer, 1024, 0);
        if (bytesReceived == 0) {
            cout << "Connection closed" << endl;
            break;
        }
        if (bytesReceived == -1) {
            cout << "Error in receiving data" << endl;
            break;
        }

        // Parse incoming message
        string message(buffer);
        if (message.substr(0, 5) == "Block") {
            handleBlock(message);
        }
    }
}

int main() {
    struct sockaddr_in serv_addr;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        cout << "Socket creation error" << endl;
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        cout << "Invalid address/ Address not supported" << endl;
        return -1;
    }

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        cout << "Connection Failed" << endl;
        return -1;
    }

    // Send transaction requests to full node
    Transaction tx1 = {"alice", "bob", 100};
    Transaction tx2 = {"bob", "charlie", 50};
    sendTransaction(tx1);
    sendTransaction(tx2);

    // Listen for incoming block updates
    receiveUpdates();

    return 0;
}
