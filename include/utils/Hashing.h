#ifndef HASHING_H
#define HASHING_H

#include <string>

class Hashing {
public:
    static std::string sha256(const std::string& input);
};

#endif // HASHING_H
