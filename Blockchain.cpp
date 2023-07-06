#include <iostream>
#include <vector>
#include <ctime>
#include <openssl/sha.h>
#include <sstream>
#include<bits/stdc++.h>
using namespace std;
struct Block {
    int index;
    string previousHash;
    time_t timestamp;
    string data;
    string hash;

    Block(int index, const string& previousHash, const string& data) {
        this->index = index;
        this->previousHash = previousHash;
        this->timestamp = time(nullptr);
        this->data = data;
        this->hash = calculateHash();
    }

    string calculateHash() {
        stringstream ss;
        ss << index << previousHash << timestamp << data;
        string input = ss.str();

        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256((unsigned char*)input.c_str(), input.length(), hash);

        stringstream hashed_ss;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
            hashed_ss << hex << setw(2) << setfill('0') << (int)hash[i];
        }

        return hashed_ss.str();
    }
};

class Blockchain {
private:
    vector<Block> chain;

public:
    Blockchain() {
        chain.push_back(createGenesisBlock());
    }

    Block createGenesisBlock() {
        return Block(0, "0", "Genesis Block");
    }

    Block getLatestBlock() const {
        return chain.back();
    }

    void addBlock(const std::string& data) {
        int index = chain.size();
        Block latestBlock = getLatestBlock();
        Block newBlock(index, latestBlock.hash, data);
        chain.push_back(newBlock);
    }

    void displayChain() const {
        for (const Block& block : chain) {
            cout << "Block Index: " << block.index << endl;
            cout << "Previous Hash: " << block.previousHash << endl;
            cout << "Timestamp: " << ctime(&block.timestamp);
            cout << "Data: " << block.data << endl;
            cout << "Hash: " << block.hash << endl;
            cout << "------------------------------------" << endl;
        }
    }
};

int main() {
    Blockchain blockchain;
    blockchain.addBlock("Data 1");
    blockchain.addBlock("Data 2");
    blockchain.addBlock("Data 3");
    blockchain.displayChain();

    return 0;
}

