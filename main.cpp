#include "Block.h"
#include <iostream>

int main() {
    Block genesis(0, "Genesis Block", "0");
    std::cout << "Block Hash: " << genesis.getHash() << "\n";
    return 0;
}
