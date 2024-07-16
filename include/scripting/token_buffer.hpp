//
// Created by rfish on 7/14/2024.
//

#ifndef KOISCRIPT_TOKEN_BUFFER_HPP
#define KOISCRIPT_TOKEN_BUFFER_HPP

namespace Koi {
namespace Scripting {

struct TokenBuffer final {
public:
    static const unsigned int MAX_SIZE = 64u;

private:
    char _buffer[MAX_SIZE] {};
    unsigned int _current_index = 0u;

public:
    unsigned int get_size() const;

    bool is_full() const;

    void push_back(const char& value);

    void reset();

};

} // Scripting
} // Koi

#endif //KOISCRIPT_TOKEN_BUFFER_HPP
