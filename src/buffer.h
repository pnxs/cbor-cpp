#pragma once

#include <string>

namespace cbor
{
class buffer
{
public:
    virtual ~buffer() {};
    virtual std::string toString() const = 0;
};

std::string hexlify(const uint8_t* data, int length);


}