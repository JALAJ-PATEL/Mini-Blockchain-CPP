// src/Blockchain.cpp
#include "../include/Blockchain.h"
#include "../include/utils/Timestamp.h"
#include <iostream>
#include <sstream>

Blockchain::Blockchain(const std::string& genesisAddress) {
    difficulty = 2; // Start with low difficulty
    miningReward = 100.0; // Mining reward amount
    
    // Create genesis block
    chain.push_back(createGenesisBlock());
}

Block Blockchain::createGenesisBlock() {
    std::vector<Transaction> genesisTransactions;
    // Genesis block has no transactions
    return Block(0, genesisTransactions, "0");
}

void Blockchain::addTransaction(const Transaction& transaction) {
    pendingTransactions.push_back(transaction);
}

void Blockchain::minePendingTransactions(const std::string& miningRewardAddress) {
    // Add mining reward transaction
    Transaction rewardTransaction("", miningRewardAddress, miningReward);
    pendingTransactions.push_back(rewardTransaction);
    
    // Create new block with pending transactions
    Block newBlock(chain.size(), pendingTransactions, getLatestBlock().getHash());
    newBlock.mineBlock(difficulty);
    
    std::cout << "Block successfully mined: " << newBlock.getHash() << std::endl;
    
    // Add block to chain and clear pending transactions
    chain.push_back(newBlock);
    pendingTransactions.clear();
}

double Blockchain::getBalanceOfAddress(const std::string& address) const {
    double balance = 0.0;
    
    // Go through all blocks and transactions
    for (const auto& block : chain) {
        for (const auto& transaction : block.getTransactions()) {
            // If address is sender, subtract amount
            if (transaction.getSender() == address) {
                balance -= transaction.getAmount();
            }
            
            // If address is receiver, add amount
            if (transaction.getReceiver() == address) {
                balance += transaction.getAmount();
            }
        }
    }
    
    return balance;
}

bool Blockchain::isChainValid() const {
    for (size_t i = 1; i < chain.size(); i++) {
        const Block& currentBlock = chain[i];
        const Block& previousBlock = chain[i - 1];
        
        // Check if current block's hash is valid
        if (currentBlock.getHash() != currentBlock.calculateHash()) {
            return false;
        }
        
        // Check if current block points to previous block
        if (currentBlock.getPreviousHash() != previousBlock.getHash()) {
            return false;
        }
    }
    
    return true;
}

void Blockchain::printChain() const {
    for (size_t i = 0; i < chain.size(); i++) {
        const Block& block = chain[i];
        std::cout << "\n=== Block " << i << " ===\n";
        std::cout << "Hash: " << block.getHash() << "\n";
        std::cout << "Previous Hash: " << block.getPreviousHash() << "\n";
        std::cout << "Timestamp: " << block.getTimestamp() << "\n";
        std::cout << "Transactions: " << block.getTransactions().size() << "\n";
        
        // Print transaction details
        for (size_t j = 0; j < block.getTransactions().size(); j++) {
            const Transaction& tx = block.getTransactions()[j];
            std::cout << "  Transaction " << j + 1 << ": ";
            if (tx.getSender().empty()) {
                std::cout << "Mining Reward -> " << tx.getReceiver() << " (" << tx.getAmount() << ")\n";
            } else {
                std::cout << tx.getSender() << " -> " << tx.getReceiver() << " (" << tx.getAmount() << ")\n";
            }
        }
    }
}

Block Blockchain::getLatestBlock() const {
    return chain.back();
}

std::vector<Block> Blockchain::getChain() const {
    return chain;
}

int Blockchain::getDifficulty() const {
    return difficulty;
}

std::vector<Transaction> Blockchain::getPendingTransactions() const {
    return pendingTransactions;
}
