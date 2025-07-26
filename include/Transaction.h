// include/Transaction.h
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction {
private:
    std::string sender;
    std::string receiver;
    double amount;
    std::string timestamp;
    std::string signature;  // Placeholder for digital signature

public:
    Transaction(std::string sender, std::string receiver, double amount);

    std::string getSender() const;
    std::string getReceiver() const;
    double getAmount() const;
    std::string getTimestamp() const;
    std::string getSignature() const;

    std::string toString() const;  // For hashing/Merkle Root

    void signTransaction(const std::string& privateKey);  // [Optional for now]
    bool isValid() const;
};

#endif
