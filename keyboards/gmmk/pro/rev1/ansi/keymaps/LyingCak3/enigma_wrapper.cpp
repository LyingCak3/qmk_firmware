
#include "enigma_wrapper.hpp"

#include "enigma_rgb.hpp"

static  LyingCak3::Enigma::EnigmaRGB enigmaRGB;

bool EnigmaProcessRGB( effect_params_t* params )
{

    return enigmaRGB.ProcessRGB( params );

}
