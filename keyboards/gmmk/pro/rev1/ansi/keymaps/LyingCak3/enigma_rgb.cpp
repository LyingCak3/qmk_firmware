
#include "enigma_rgb.hpp"

#include "lc_buffer.hpp"

extern "C" {
#include <color.h>
#include <lib/lib8tion/lib8tion.h>
#include <quantum/rgb_matrix/rgb_matrix.h>
#include <debug.h>
}

LyingCak3::Enigma::EnigmaRGB::EnigmaRGB()
    : LyingCak3::CustomListBase()
    , rotor1_( &ROTOR_1_VALUES, &ROTOR_1_NOTCHES )
    , rotor2_( &ROTOR_2_VALUES, &ROTOR_2_NOTCHES )
    , rotor3_( &ROTOR_3_VALUES, &ROTOR_3_NOTCHES )
    , enigma_()
{

    reflector_ = { REFLECTOR_VALUES };

    enigma_.InstallRotor( 0, &rotor1_ );
    enigma_.InstallRotor( 1, &rotor2_ );
    enigma_.InstallRotor( 2, &rotor3_ );

    enigma_.InstallReflector( &reflector_ );

}

void LyingCak3::Enigma::EnigmaRGB::Initialize( effect_params_t* params )
{
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    HSV hsv = { 225, 0, rgb_matrix_config.hsv.v };
    RGB rgb = hsv_to_rgb( hsv );
    rgb_matrix_set_color_all( rgb.r, rgb.g, rgb.b );
    for ( uint8_t i = led_min; i < led_max; ++i )
    {
        LyingCak3::Buffers::LedBuffers::LED_BUFFER[ i ] = 0;
    }
}

bool LyingCak3::Enigma::EnigmaRGB::ProcessRGB( effect_params_t* params )
{
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    if ( params->init )
    {
        Initialize( params );
    }

    for (uint8_t i = led_min; i < led_max; i++)
    {
        LyingCak3::Buffers::LedBuffers::LED_BUFFER[ i ] = qsub8( LyingCak3::Buffers::LedBuffers::LED_BUFFER[ i ], 8 );
        RGB_MATRIX_TEST_LED_FLAGS();
        for (int8_t j = g_last_hit_tracker.count - 1; j >= 0; j--) {
            if ( g_last_hit_tracker.index[j] == i )
            {

                uint8_t enigmaValue = enigma_.ProcessChiper( i );
                LyingCak3::Buffers::LedBuffers::LED_BUFFER[ enigmaValue ] = 255;
                
            }
        }
    }

    for (uint8_t i = led_min; i < led_max; i++)
    {
        HSV hsv = { 225, LyingCak3::Buffers::LedBuffers::LED_BUFFER[ i ], rgb_matrix_config.hsv.v };
        RGB rgb = hsv_to_rgb( hsv );
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }

    return rgb_matrix_check_finished_leds(led_max);

}
