
#include "rngesus.hpp"

extern "C"
{
#include <lib/lib8tion/lib8tion.h>
#include <quantum/rgb_matrix/rgb_matrix.h>
#include <debug.h>
}

LyingCak3::RNGesus::RNGesus::RNGesus()
    : xorshiftState_{0}
    , RNGinitlized_(0)
    , baseValue_( 0 )
    , engagedValue_( 250 )
    , timerIncrement_( 200 )
    , timer_( 0 )
    , trigger_( false )
{
}

LyingCak3::RNGesus::RNGesus::~RNGesus()
{}

bool LyingCak3::RNGesus::RNGesus::ProcessRGB( effect_params_t* params )
{

    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    if ( params->init )
    {

        if ( 0 == params->iter)
        {
            RNGinitialize();
        }

        Initialize( params );
    }



    if (params->iter == 0) {
        trigger_ = timer_elapsed(timer_) >= timerIncrement_;

        // Restart the timer if we are going to decrease the heatmap this frame.
        if (trigger_) {
            timer_ = timer_read();
        }

    }

    for( int i = led_min; i < led_max; ++i )
    {

        LyingCak3::Buffers::LedBuffers::LED_BUFFER[ i ] = qsub8Custom(LyingCak3::Buffers::LedBuffers::LED_BUFFER[ i ], 4, baseValue_);

    }

    if (params->iter == 0)
    {

        if ( true == trigger_ )
        {
            uint64_t rng =  LyingCak3::XORShift::xorshift128p(xorshiftState_);
            uint8_t id = scale8( rng & 0xff, RGB_MATRIX_LED_COUNT );
            LyingCak3::Buffers::LedBuffers::LED_BUFFER[id] = engagedValue_;

        }

    }

    for( int i = led_min; i < led_max; ++i )
    {

        RGB rgb = uintToRGB( LyingCak3::Buffers::LedBuffers::LED_BUFFER[i] );
        rgb_matrix_set_color( i, rgb.r, rgb.g, rgb.b );

    }

    return rgb_matrix_check_finished_leds(led_max);

}

void LyingCak3::RNGesus::RNGesus::Initialize( effect_params_t* params )
{

    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    RGB rgb = uintToRGB( baseValue_ );
    for( int i = led_min; i < led_max; ++i )
    {
        rgb_matrix_set_color( i, rgb.r, rgb.g, rgb.b );
        LyingCak3::Buffers::LedBuffers::LED_BUFFER[i] = baseValue_;
    }

}

void LyingCak3::RNGesus::RNGesus::RNGinitialize( )
{

    xorshiftState_.x[0] = stGetCounter();
    xorshiftState_.x[0] = xorshiftState_.x[0] << 32;
    xorshiftState_.x[0] = xorshiftState_.x[0] | stGetCounter();

    xorshiftState_.x[1] = stGetCounter();
    xorshiftState_.x[1] = xorshiftState_.x[1] << 32;
    xorshiftState_.x[1] = xorshiftState_.x[1] | stGetCounter();

}

HSV LyingCak3::RNGesus::RNGesus::uintToHSV( uint8_t val )
{
    HSV r = { 160 - qsub8(val, 50), rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v };
    return r;
}

RGB LyingCak3::RNGesus::RNGesus::uintToRGB( uint8_t val )
{
    HSV hsv = uintToHSV( val );
    return hsv_to_rgb( hsv) ;
}
