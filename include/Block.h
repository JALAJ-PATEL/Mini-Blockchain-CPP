// include/Block.h
#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <vector>
#include "Transaction.h"

class Block {
private:
    int index;
    long long timestamp;
    std::string previousHash;
    std::string hash;
    std::string merkleRoot;
    int nonce;
    std::vector<Transaction> transactions;

public:
    Block(int idx, const std::vector<Transaction>& txs, const std::string& prevHash);

    std::string calculateHash() const;
    void mineBlock(int difficulty);

    // Getters
    std::string getHash() const;
    std::string getPreviousHash() const;
    std::vector<Transaction> getTransactions() const;
    long long getTimestamp() const;
    int getIndex() const;
};

#endif
