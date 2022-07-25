
#ifndef LC_BUFFER_HPP
#define LC_BUFFER_HPP

#include <cstdint>

extern "C" {
#include <rgb_matrix_types.h>
};

namespace LyingCak3
{

namespace Buffers
{

class LedBuffers
{

public:
    static uint8_t LED_BUFFER[ DRIVER_LED_TOTAL ];

};

}

}

#endif
