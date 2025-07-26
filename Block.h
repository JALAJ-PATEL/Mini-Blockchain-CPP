#pragma once

#include<string>
#include<ctime>

class Block {
    private:
        int index;
        std::time_t timestamp;
        std::string data;
        std::string previousHash;
        std::string hash;

    public:
        //Constructor
        Block(int idx, const std::string& data, const std::string& previousHash);

        // Getters
        int getIndex() const;
        std::time_t getTimestamp() const;
        std::string getData() const;
        std::string getPreviousHash() const;
        std::string getHash() const;

        // Compute SHA256 hash based on block contents
        std::string computeHash() const;
};