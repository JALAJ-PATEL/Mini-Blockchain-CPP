#include<Block.h>
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>

// Constructor implementation
Block::Block(int idx, const std::string& data, const std::string& previousHash)
    : index(idx), data(data), previousHash(previousHash) 
{
    timestamp = std::time(nullptr);
    hash = computeHash(); // Compute the hash when the block is created
}

// Getters implementation
int Block::getIndex() const { return index; }
std::time_t Block::getTimestamp() const { return timestamp; }
std::string Block::getData() const { return data; }
std::string Block::getPreviousHash() const { return previousHash; }
std::string Block::getHash() const { return hash; }

// Compute SHA256 hash based on block contents
std::string Block::computeHash() const {
    std::stringstream ss;
    ss << index << timestamp << data << previousHash;

    std::string input = ss.str();
    unsigned char hashBytes[SHA256_DIGEST_LENGTH];

    SHA256(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), hashBytes);

    std::stringstream hexStream;
    for( unsigned char byte : hashBytes) {
        hexStream << std::hex << std::setw(2) << std::setfill('0') << (int)byte;
    }

    return hexStream.str();
}