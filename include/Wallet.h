// include/Wallet.h
#ifndef WALLET_H
#define WALLET_H

#include <string>
#include <openssl/evp.h> // Declares OpenSSL’s high-level EVP API

class Wallet {
private:
    EVP_PKEY* keyPair;  // OpenSSL key pair for public and private keys

public:
    Wallet();  // Constructor generates key pair
    ~Wallet(); // Destructor to free keyPair

    std::string getPublicKey() const;
    std::string getPrivateKey() const;  // Optional: for testing
    std::string getAddress() const;     // SHA-256 hash of public key

    std::string signMessage(const std::string& message) const;
    static bool verifySignature(const std::string& publicKeyPem, const std::string& message, const std::string& signatureBase64);
};

#endif
