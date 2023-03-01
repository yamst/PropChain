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
    // Listen for incoming transaction requests
    // ...

    // Create new block with verified transactions
    Block block;
    block.index = getLastBlockIndex() + 1; // Get the next index for the new block
    block.transactions = getVerifiedTransactions(); // Get the verified transactions from the transaction pool
    block.prevHash = getLastBlockHash(); // Get the hash of the previous block
    block.currHash = calculateBlockHash(block); // Calculate the hash of the new block
    block.nonce = mineBlock(block); // Mine the block to find a valid nonce

    // Add new block to blockchain
    // ...

    // Broadcast new block to other nodes in the network
    // ...
}
return 0;
}
