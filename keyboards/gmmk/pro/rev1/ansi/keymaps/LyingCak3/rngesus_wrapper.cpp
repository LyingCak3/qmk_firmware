
#include "rngesus.hpp"
#include "rngesus_wrapper.hpp"

static LyingCak3::RNGesus::RNGesus rngesus;

bool RNGesusProcessRGB( effect_params_t* params )
{
    return rngesus.ProcessRGB( params );
}
