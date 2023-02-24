import socket
import threading
import json
from chain import Chain
from block import Block

# Define the host and port for the node
HOST = '127.0.0.1'
PORT = 5000

# Create a blockchain instance
blockchain = Blockchain()

# Define the thread function to handle incoming client connections
def handle_client(conn, addr):
    print("Client connected:", addr)

    # Keep listening for messages from the client
    while True:
        try:
            # Receive the message from the client and decode it
            data = conn.recv(1024).decode("utf-8")
            if not data:
                break

            # Parse the message into its components
            parts = data.split(":")
            command = parts[0]

            # Handle the command based on its type
            if command == "add_block":
                index = int(parts[1])
                timestamp = float(parts[2])
                data = parts[3]
                previous_hash = parts[4]

                # Create a new block and add it to the blockchain
                new_block = Block(index, timestamp, data, previous_hash)
                blockchain.add_block(new_block)

        except Exception as e:
            print("Error handling client:", e)

    # Close the connection when the client disconnects
    print("Client disconnected:", addr)
    conn.close()

# Define the function to start the server and listen for client connections
def start_server():
    # Create a server socket and bind it to the host and port
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((HOST, PORT))
    server.listen()

    # Print a message to indicate that the server is listening
    print("Server listening on", HOST, ":", PORT)

    # Keep accepting client connections and spawn a new thread to handle each one
    while True:
        conn, addr = server.accept()
        thread = threading.Thread(target=handle_client, args=(conn, addr))
        thread.start()

# Define the main function to start the blockchain node
def main():
    # Register the node with the blockchain
    blockchain.register_node(Node(HOST, PORT))

    # Start the server and listen for client connections
    server_thread = threading.Thread(target=start_server)
    server_thread.start()

    # Keep mining new blocks and adding them to the chain
    while True:
        new_block = Block(len(blockchain.chain), time.time(), "Data for block " + str(len(blockchain.chain)), blockchain.get_latest_block().hash)
        blockchain.add_block(new_block)
        time.sleep(10)

# Define a Node class to store the host and port information for each node
class Node:
    def __init__(self, host, port):
        self.host = host
        self.port = port

# Call the main function to start the node
if __name__ == "__main__":
    main()
