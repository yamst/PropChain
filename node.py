import socket
import threading

class Node:
    def __init__(self, host, port, blockchain):
        self.host = host
        self.port = port
        self.blockchain = blockchain

        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server.bind((self.host, self.port))
        self.server.listen(1)

    def handle_client(self, client_socket):
        while True:
            data = client_socket.recv(1024)
            if not data:
                break
            message = data.decode("utf-8")
            if message.startswith("add_block"):
                block_data = message.split(":")[1]
                index, timestamp, data, previous_hash = block_data.split(",")
                new_block = Block(int(index), timestamp, data, previous_hash)
                new_block.mine_block(4)
                self.blockchain.add_block(new_block)
                print("Block added to the chain: ", new_block.hash)

        client_socket.close()

    def start(self):
        print("Node started listening on", self.host, ":", self.port)
        while True:
            client, address = self.server.accept()
            print("Incoming connection from", address)
            client_handler = threading.Thread(target=self.handle_client, args=(client,))
            client_handler.start()
