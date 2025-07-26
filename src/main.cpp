#include <iostream>
#include <memory>
#include <vector>
#include "Blockchain.h"
#include "Transaction.h"
#include "Wallet.h"

int main() {
    std::cout << "🔗 Mini-Blockchain Started - Expanded Capacity Demo\n";
    std::cout << "================================================\n\n";

    // Initialize multiple wallets
    Wallet minerWallet;
    Wallet Jalaj;
    Wallet Het;
    Wallet Matang;
    Wallet Riken;
    Wallet Dhrumil;

    std::cout << "Created 6 wallets with unique addresses:\n";
    std::cout << "Miner:   " << minerWallet.getAddress().substr(0, 16) << "...\n";
    std::cout << "Jalaj:   " << Jalaj.getAddress().substr(0, 16) << "...\n";
    std::cout << "Het:     " << Het.getAddress().substr(0, 16) << "...\n";
    std::cout << "Matang: " << Matang.getAddress().substr(0, 16) << "...\n";
    std::cout << "Riken:   " << Riken.getAddress().substr(0, 16) << "...\n";
    std::cout << "Dhrumil:     " << Dhrumil.getAddress().substr(0, 16) << "...\n\n";

    // Create the blockchain
    Blockchain blockchain(minerWallet.getAddress());

    // === BLOCK 1: Multiple transactions ===
    std::cout << "Creating Block 1 with multiple transactions...\n";
    
    Transaction tx1(Jalaj.getAddress(), Het.getAddress(), 25.0);
    Transaction tx2(Jalaj.getAddress(), Matang.getAddress(), 15.0);
    Transaction tx3(Het.getAddress(), Riken.getAddress(), 8.5);
    
    blockchain.addTransaction(tx1);
    blockchain.addTransaction(tx2);
    blockchain.addTransaction(tx3);
    
    std::cout << "Added 3 transactions to pending pool\n";
    blockchain.minePendingTransactions(minerWallet.getAddress());
    std::cout << "Block 1 mined successfully!\n\n";

    // === BLOCK 2: More complex transactions ===
    std::cout << "Creating Block 2 with more transactions...\n";
    
    Transaction tx4(Matang.getAddress(), Dhrumil.getAddress(), 5.0);
    Transaction tx5(Riken.getAddress(), Jalaj.getAddress(), 3.0);
    Transaction tx6(Het.getAddress(), Matang.getAddress(), 12.0);
    Transaction tx7(Dhrumil.getAddress(), Riken.getAddress(), 2.5);
    Transaction tx8(Jalaj.getAddress(), Het.getAddress(), 7.5);
    
    blockchain.addTransaction(tx4);
    blockchain.addTransaction(tx5);
    blockchain.addTransaction(tx6);
    blockchain.addTransaction(tx7);
    blockchain.addTransaction(tx8);
    
    std::cout << "Added 5 transactions to pending pool\n";
    blockchain.minePendingTransactions(minerWallet.getAddress());
    std::cout << "Block 2 mined successfully!\n\n";

    // === BLOCK 3: High volume transactions ===
    std::cout << "Creating Block 3 with high volume transactions...\n";
    
    // Create 10 transactions for demonstration
    std::vector<Transaction> highVolumeTxs = {
        Transaction(Jalaj.getAddress(), Het.getAddress(), 1.0),
        Transaction(Het.getAddress(), Matang.getAddress(), 2.0),
        Transaction(Matang.getAddress(), Riken.getAddress(), 1.5),
        Transaction(Riken.getAddress(), Dhrumil.getAddress(), 3.0),
        Transaction(Dhrumil.getAddress(), Jalaj.getAddress(), 0.5),
        Transaction(Jalaj.getAddress(), Matang.getAddress(), 4.0),
        Transaction(Het.getAddress(), Riken.getAddress(), 2.5),
        Transaction(Matang.getAddress(), Het.getAddress(), 1.8),
        Transaction(Riken.getAddress(), Jalaj.getAddress(), 0.7),
        Transaction(Dhrumil.getAddress(), Het.getAddress(), 3.2)
    };
    
    for(const auto& tx : highVolumeTxs) {
        blockchain.addTransaction(tx);
    }
    
    std::cout << "Added 10 transactions to pending pool\n";
    blockchain.minePendingTransactions(minerWallet.getAddress());
    std::cout << "Block 3 mined successfully!\n\n";

    // === Display complete blockchain ===
    std::cout << "=== COMPLETE BLOCKCHAIN STATE ===\n";
    blockchain.printChain();

    // === Display all balances ===
    std::cout << "\n=== FINAL BALANCES ===\n";
    std::cout << "Miner:   " << blockchain.getBalanceOfAddress(minerWallet.getAddress()) << " coins\n";
    std::cout << "Jalaj:   " << blockchain.getBalanceOfAddress(Jalaj.getAddress()) << " coins\n";
    std::cout << "Het:     " << blockchain.getBalanceOfAddress(Het.getAddress()) << " coins\n";
    std::cout << "Matang: " << blockchain.getBalanceOfAddress(Matang.getAddress()) << " coins\n";
    std::cout << "Riken:   " << blockchain.getBalanceOfAddress(Riken.getAddress()) << " coins\n";
    std::cout << "Dhrumil:     " << blockchain.getBalanceOfAddress(Dhrumil.getAddress()) << " coins\n";

    // === Blockchain statistics ===
    std::cout << "\n=== BLOCKCHAIN STATISTICS ===\n";
    auto chain = blockchain.getChain();
    std::cout << "Total Blocks: " << chain.size() << "\n";
    
    int totalTransactions = 0;
    for(const auto& block : chain) {
        totalTransactions += block.getTransactions().size();
    }
    std::cout << "Total Transactions: " << totalTransactions << "\n";
    std::cout << "Mining Difficulty: " << blockchain.getDifficulty() << "\n";
    std::cout << "Chain Valid: " << (blockchain.isChainValid() ? "✅ YES" : "❌ NO") << "\n";

    std::cout << "\nMini-Blockchain Demo Completed Successfully!\n";
    return 0;
}
