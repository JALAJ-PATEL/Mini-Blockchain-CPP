// src/Transaction.cpp
#include "Transaction.h"
#include "utils/Timestamp.h"
#include "utils/Hashing.h"

Transaction::Transaction(std::string sender, std::string receiver, double amount)
    : sender(std::move(sender)), receiver(std::move(receiver)), amount(amount)
{
    timestamp = Timestamp::getCurrentUTCTime();  // e.g., "2025-07-25T23:59:59Z"
    signature = "";  // Placeholder for future signing logic
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
    // TODO: Implement digital signing using OpenSSL
    // For now, just simulate with hash
    signature = Hashing::sha256(privateKey + toString());
}

bool Transaction::isValid() const {
    // Placeholder for real validation
    return !sender.empty() && !receiver.empty() && amount > 0;
}
