#include "utils/MerkleTree.h"
#include "utils/Hashing.h"

std::string MerkleTree::computeMerkleRoot(const std::vector<std::string>& txHashes) {
    if (txHashes.empty()) return "";

    std::vector<std::string> currentLevel = txHashes;

    while (currentLevel.size() > 1) {
        std::vector<std::string> nextLevel;

        for (size_t i = 0; i < currentLevel.size(); i += 2) {
            std::string left = currentLevel[i];
            std::string right = (i + 1 < currentLevel.size()) ? currentLevel[i + 1] : left; // duplicate last if odd

            std::string combined = left + right;
            std::string hashed = Hashing::sha256(combined);
            nextLevel.push_back(hashed);
        }

        currentLevel = nextLevel;
    }

    return currentLevel.front(); // Merkle root
}
