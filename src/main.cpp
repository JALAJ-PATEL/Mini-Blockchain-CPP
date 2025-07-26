#include <iostream>
#include <memory>
#include "../include/Blockchain.h"
#include "../include/Transaction.h"
#include "../include/Wallet.h"

int main() {
    std::cout << "Mini-Blockchain Started\n";

    // Initialize wallets
    Wallet minerWallet;
    Wallet userA;
    Wallet userB;

    // Create the blockchain
    Blockchain blockchain(minerWallet.getAddress());

    // Create a transaction from Alice to Bob
    Transaction tx1(userA.getAddress(), userB.getAddress(), 10.5);
    blockchain.addTransaction(tx1);

    // Mine the pending transactions
    blockchain.minePendingTransactions(minerWallet.getAddress());

    // Display blockchain
    std::cout << "\n=== Blockchain State ===\n";
    blockchain.printChain();

    // Check balance
    std::cout << "\nMiner Balance: " << blockchain.getBalanceOfAddress(minerWallet.getAddress()) << "\n";

    return 0;
}
