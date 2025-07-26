// include/Blockchain.h
#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <vector>
#include <string>
#include "Block.h"
#include "Transaction.h"

class Blockchain {
private:
    std::vector<Block> chain;
    int difficulty;
    std::vector<Transaction> pendingTransactions;
    double miningReward;

    Block createGenesisBlock();

public:
    Blockchain(const std::string& genesisAddress);
    
    void addTransaction(const Transaction& transaction);
    void minePendingTransactions(const std::string& miningRewardAddress);
    
    double getBalanceOfAddress(const std::string& address) const;
    
    bool isChainValid() const;
    void printChain() const;
    
    // Getters
    Block getLatestBlock() const;
    std::vector<Block> getChain() const;
    int getDifficulty() const;
    std::vector<Transaction> getPendingTransactions() const;
};

#endif // BLOCKCHAIN_H
