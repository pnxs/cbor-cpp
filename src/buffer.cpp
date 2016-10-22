#include "buffer.h"
#include <sstream>
#include <iomanip>

namespace cbor
{

std::string hexlify(const uint8_t *data, int length)
{
    std::ostringstream os;

    for (int i = 0; i < length; ++i)
    {
        int d = data[i];
        os << std::setw(2) << std::setfill('0') << std::hex << (d & 0xff);
    }

    return os.str();
}

}