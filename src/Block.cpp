// src/Block.cpp
#include "../../include/Block.h"
#include "../../include/utils/Hashing.h"
#include "../../include/utils/Timestamp.h"
#include "../../include/utils/MerkleTree.h"

#include <sstream>
#include <iomanip>
#include <chrono>

Block::Block(int idx, const std::vector<Transaction>& txs, const std::string& prevHash)
    : index(idx), transactions(txs), previousHash(prevHash), nonce(0)
{
    // Get current timestamp as Unix epoch
    auto now = std::chrono::system_clock::now();
    timestamp = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
    
    // Compute Merkle root from transaction hashes
    std::vector<std::string> txHashes;
    for (const auto& tx : transactions) {
        txHashes.push_back(Hashing::sha256(tx.toString()));
    }
    merkleRoot = MerkleTree::computeMerkleRoot(txHashes);
    
    hash = calculateHash();
}

std::string Block::calculateHash() const {
    std::stringstream ss;
    ss << index << timestamp << previousHash << merkleRoot << nonce;
    return Hashing::sha256(ss.str());
}

void Block::mineBlock(int difficulty) {
    std::string target(difficulty, '0');
    do {
        nonce++;
        hash = calculateHash();
    } while (hash.substr(0, difficulty) != target);
}

std::string Block::getHash() const {
    return hash;
}

std::string Block::getPreviousHash() const {
    return previousHash;
}

std::vector<Transaction> Block::getTransactions() const {
    return transactions;
}

long long Block::getTimestamp() const {
    return timestamp;
}

int Block::getIndex() const {
    return index;
}
