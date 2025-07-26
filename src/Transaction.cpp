// src/Transaction.cpp
#include "Transaction.h"
#include "utils/Timestamp.h"
#include "utils/Hashing.h"

Transaction::Transaction(std::string sender, std::string receiver, double amount)
    : sender(std::move(sender)), receiver(std::move(receiver)), amount(amount)
{
    timestamp = Timestamp::getCurrentUTCTime();  // e.g., "2025-07-25T23:59:59Z"
    signature = "";  // Placeholder : For Complex Cryptographic signing and Validation
}

std::string Transaction::getSender() const {
    return sender;
}

std::string Transaction::getReceiver() const {
    return receiver;
}

double Transaction::getAmount() const {
    return amount;
}

std::string Transaction::getTimestamp() const {
    return timestamp;
}

std::string Transaction::getSignature() const {
    return signature;
}

std::string Transaction::toString() const {
    return sender + receiver + std::to_string(amount) + timestamp;
}

void Transaction::signTransaction(const std::string& privateKey) {
    signature = Hashing::sha256(privateKey + toString());
}

bool Transaction::isValid() const { 
    // basic validation logic : sender and receiver should not be empty, amount should be positive
    return !sender.empty() && !receiver.empty() && amount > 0;
}
