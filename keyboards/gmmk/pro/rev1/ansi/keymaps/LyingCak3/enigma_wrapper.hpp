
#ifndef ENIGMA_WRAPPER_HPP
#define ENIGMA_WRAPPER_HPP

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <debug.h>
#include <rgb_matrix_types.h>

bool EnigmaProcessRGB( effect_params_t* params );

#ifdef __cplusplus
}
#endif

#endif
