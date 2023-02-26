import hashlib
from block import Block
import json
import time
import socket

class Chain:
    def __init__(self):
        self.chain = [self.create_genesis_block()]
        self.difficulty = 4
        self.nodes = []

    def create_genesis_block(self):
        return Block(0, time.time(), "Genesis Block", "0")

    def get_latest_block(self):
        return self.chain[-1]

    def add_block(self, new_block):
        if new_block.index == self.get_latest_block().index + 1 and new_block.previous_hash == self.get_latest_block().hash:
            new_block.mine_block(self.difficulty)
            self.chain.append(new_block)
            self.broadcast_new_block(new_block)
            return True
        else:
            return False

    def is_valid(self):
        for i in range(1, len(self.chain)):
            current_block = self.chain[i]
            previous_block = self.chain[i-1]

            if current_block.hash != current_block.calculate_hash():
                return False
            if current_block.previous_hash != previous_block.hash:
                return False

        return True

    def register_node(self, node):
        self.nodes.append(node)

    def broadcast_new_block(self, new_block):
        for node in self.nodes:
            client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            client.connect((node.host, node.port))
            message = "add_block:{}:{}:{}:{}".format(new_block.index, new_block.timestamp, new_block.data, new_block.previous_hash)
            client.sendall(message.encode("utf-8"))
            client.close()