
// !!! DO NOT ADD #pragma once !!! //

#include <stdint.h>

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT( better_heatmap_color )
RGB_MATRIX_EFFECT( better_heatmap_sat )
RGB_MATRIX_EFFECT( enigma )
RGB_MATRIX_EFFECT( RNGesus )

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#include "better_heatmap_wrapper.hpp"
#include "enigma_wrapper.hpp"
#include "rngesus_wrapper.hpp"

static void better_heatmap_handle_keypress(uint8_t row, uint8_t col, bool pressed)
{
    BetterHeatmapProcessKeyPress( row, col, pressed );
}

static bool better_heatmap_color( effect_params_t* params )
{
    return BetterHeatmapProcessRGB( params, 0 );
}

static bool better_heatmap_sat( effect_params_t* params )
{
    return BetterHeatmapProcessRGB( params, 1 );
}

static bool enigma( effect_params_t* params )
{

    return EnigmaProcessRGB( params );
}

static bool RNGesus( effect_params_t* params )
{

    return RNGesusProcessRGB( params );
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS