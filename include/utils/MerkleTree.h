#ifndef MERKLE_TREE_H
#define MERKLE_TREE_H

#include <vector>
#include <string>

class MerkleTree {
public:
    // Computes and returns the Merkle Root from a list of transaction hashes
    static std::string computeMerkleRoot(const std::vector<std::string>& txHashes);
};

#endif // MERKLE_TREE_H
