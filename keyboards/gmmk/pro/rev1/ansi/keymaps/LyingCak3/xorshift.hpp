
#ifndef XORSHIFT_HPP
#define XORSHIFT_HPP

#include <stdint.h>

namespace LyingCak3
{

namespace XORShift
{

struct xorshift128p_state {
    uint64_t x[2];
};

/* The state must be seeded so that it is not all zero */
uint64_t xorshift128p(xorshift128p_state& state);

}

}


#endif
