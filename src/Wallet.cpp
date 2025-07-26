// src/Wallet.cpp
#include "../../include/Wallet.h"
#include "../../include/utils/Hashing.h"
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <vector>
#include <sstream>
#include <iostream>

// Base64 encoding helper functions
std::string base64Encode(const std::vector<unsigned char>& data) {
    BIO* bio = BIO_new(BIO_s_mem());
    BIO* b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bio = BIO_push(b64, bio);
    
    BIO_write(bio, data.data(), data.size());
    BIO_flush(bio);
    
    BUF_MEM* bufferPtr;
    BIO_get_mem_ptr(bio, &bufferPtr);
    std::string result(bufferPtr->data, bufferPtr->length);
    
    BIO_free_all(bio);
    return result;
}

std::vector<unsigned char> base64Decode(const std::string& encoded) {
    BIO* bio = BIO_new_mem_buf(encoded.data(), encoded.length());
    BIO* b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bio = BIO_push(b64, bio);
    
    std::vector<unsigned char> result(encoded.length());
    int decoded_length = BIO_read(bio, result.data(), encoded.length());
    result.resize(decoded_length);
    
    BIO_free_all(bio);
    return result;
}

Wallet::Wallet() {
    keyPair = EVP_PKEY_new();
    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, nullptr);
    EVP_PKEY_keygen_init(ctx);
    EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, 2048);
    EVP_PKEY_keygen(ctx, &keyPair);
    EVP_PKEY_CTX_free(ctx);
}

Wallet::~Wallet() {
    if (keyPair) {
        EVP_PKEY_free(keyPair);
    }
}

std::string Wallet::getPublicKey() const {
    BIO* bio = BIO_new(BIO_s_mem());
    PEM_write_bio_PUBKEY(bio, keyPair);
    BUF_MEM* bufferPtr;
    BIO_get_mem_ptr(bio, &bufferPtr);
    std::string pubKey(bufferPtr->data, bufferPtr->length);
    BIO_free(bio);
    return pubKey;
}

std::string Wallet::getPrivateKey() const {
    BIO* bio = BIO_new(BIO_s_mem());
    PEM_write_bio_PrivateKey(bio, keyPair, nullptr, nullptr, 0, nullptr, nullptr);
    BUF_MEM* bufferPtr;
    BIO_get_mem_ptr(bio, &bufferPtr);
    std::string privKey(bufferPtr->data, bufferPtr->length);
    BIO_free(bio);
    return privKey;
}

std::string Wallet::getAddress() const {
    return Hashing::sha256(getPublicKey());  // Simplified address format
}

std::string Wallet::signMessage(const std::string& message) const {
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    EVP_PKEY_CTX* pctx = nullptr;

    EVP_DigestSignInit(ctx, &pctx, EVP_sha256(), nullptr, keyPair);
    EVP_DigestSignUpdate(ctx, message.c_str(), message.length());

    size_t sigLen = 0;
    EVP_DigestSignFinal(ctx, nullptr, &sigLen);
    std::vector<unsigned char> signature(sigLen);
    EVP_DigestSignFinal(ctx, signature.data(), &sigLen);

    EVP_MD_CTX_free(ctx);

    return base64Encode(signature);
}

bool Wallet::verifySignature(const std::string& publicKeyPem, const std::string& message, const std::string& signatureBase64) {
    BIO* bio = BIO_new_mem_buf(publicKeyPem.data(), -1);
    EVP_PKEY* pubKey = PEM_read_bio_PUBKEY(bio, nullptr, nullptr, nullptr);
    BIO_free(bio);

    if (!pubKey) return false;

    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    EVP_DigestVerifyInit(ctx, nullptr, EVP_sha256(), nullptr, pubKey);
    EVP_DigestVerifyUpdate(ctx, message.c_str(), message.length());

    std::vector<unsigned char> sigBytes = base64Decode(signatureBase64);
    bool result = EVP_DigestVerifyFinal(ctx, sigBytes.data(), sigBytes.size()) == 1;

    EVP_MD_CTX_free(ctx);
    EVP_PKEY_free(pubKey);

    return result;
}
