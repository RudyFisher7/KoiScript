//
// Created by rfish on 7/14/2024.
//

#include "token_buffer.hpp"


namespace Koi {
namespace Scripting {

unsigned int TokenBuffer::get_size() const {
    return _current_index;
}


bool TokenBuffer::is_full() const {
    return _current_index >= MAX_SIZE;
}


void TokenBuffer::push_back(const char& value) {
    _buffer[_current_index++] = value;
}


void TokenBuffer::reset() {
    _current_index = 0u;
}

} // Scripting
} // Koi