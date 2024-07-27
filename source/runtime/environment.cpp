/*
 * MIT License
 *
 * Copyright (c) 2024 kiyasui-hito
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


#include <utility>

#include "scripting/runtime/environment.hpp"


namespace Koi {
namespace Scripting {
namespace Runtime {

std::shared_ptr<const IMeta> Environment::get(const std::string& key) const {
    std::shared_ptr<const IMeta> result;
    if (_declarations.find(key) != _declarations.end()) {
        result = _declarations.at(key);
    }

    return result;
}


bool Environment::register_declaration(const std::string& key) {
    bool result = false;

    result = _declarations.emplace(key, std::shared_ptr<const IMeta>()).second;

    return result;
}


bool Environment::set(const std::string& key, std::shared_ptr<const IMeta> value) {
    bool result = false;

    if (_declarations.find(key) != _declarations.end()) {
        _declarations.at(key) = std::move(value);
        result = true;
    } else {
        std::shared_ptr<Environment> environment = _resolve(key);

        if (environment) {
            result = environment->set(key, value);
        }
    }

    return result;
}


void Environment::set_parent_environment(std::shared_ptr<Environment> in_parent) {
    _parent = std::move(in_parent);
}


std::shared_ptr<Environment> Environment::_resolve(const std::string& key) {
    std::shared_ptr<Environment> result = _parent;

    while (result && result->_has_key(key)) {
        result = result->_parent;
    }

    return result;
}


bool Environment::_has_key(const std::string& key) const {
    bool result = false;

    result = _declarations.find(key) != _declarations.cend();

    return result;
}

} // Runtime
} // Scripting
} // Koi