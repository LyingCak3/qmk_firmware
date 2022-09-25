
#include "xorshift.hpp"

// From https://en.wikipedia.org/wiki/Xorshift
uint64_t LyingCak3::XORShift::xorshift128p(xorshift128p_state& state)
{
	uint64_t t = state.x[0];
	uint64_t const s = state.x[1];
	state.x[0] = s;
	t ^= t << 23;		// a
	t ^= t >> 18;		// b -- Again, the shifts and the multipliers are tunable
	t ^= s ^ (s >> 5);	// c
	state.x[1] = t;
	return t + s;
}
