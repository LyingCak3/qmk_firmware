

#include "better_heatmap.hpp"

#include <math.h>
extern "C" {
#include <lib/lib8tion/lib8tion.h>
#include <quantum/rgb_matrix/rgb_matrix.h>
#include <debug.h>
}

LyingCak3::BetterHeatMap::BetterHeatMap( void )
    : CustomListBase()
    , baseValue_( 0 )
    , timerIncrement_( 25 )
    , timer_( 0 )
    , decrease_( false )
    , baseIncrement_( 16.0f )
    , scaleFactor_( 1.0f - 0.03f )
    , mode_( BetterHeatmapConfig::COLOR )
{}

LyingCak3::BetterHeatMap::~BetterHeatMap( void ){}

void LyingCak3::BetterHeatMap::ProcessKeyPress( uint8_t row, uint8_t col, bool pressed )
{

    if ( false == pressed ) return;

    uint8_t pressed_led_point = g_led_config.matrix_co[ row ][ col ];
    if ( ( NO_LED != pressed_led_point ) )
    {
        const uint8_t led_min = 0;
        const uint8_t led_max = DRIVER_LED_TOTAL;
        for ( uint8_t i = led_min; i < led_max; ++i )
        {

            if ( HAS_ANY_FLAGS( g_led_config.flags[i], LED_FLAG_UNDERGLOW  ) ){ continue; }

            int16_t dx = g_led_config.point[i].x - g_led_config.point[pressed_led_point].x;
            int16_t dy = g_led_config.point[i].y - g_led_config.point[pressed_led_point].y;

            float dist = sqrt16(dx * dx + dy * dy);

            float increase_val = std::pow( scaleFactor_, (float)dist) * baseIncrement_;

            LyingCak3::Buffers::LedBuffers::LED_BUFFER[ i ] = qadd16( LyingCak3::Buffers::LedBuffers::LED_BUFFER[ i ], (uint16_t)( increase_val), 234 );
        }
    }
}

bool LyingCak3::BetterHeatMap::ProcessRGB( effect_params_t* params, BetterHeatmapConfig::BETTER_HEATMAP_MODE mode )
{

    mode_ = mode;

    if ( params->init )
    {
        Initialize( params );
    }

    // The heatmap animation might run in several iterations depending on
    // `RGB_MATRIX_LED_PROCESS_LIMIT`, therefore we only want to update the
    // timer when the animation starts.
    if (params->iter == 0) {
        decrease_ = timer_elapsed(timer_) >= timerIncrement_;

        // Restart the timer if we are going to decrease the heatmap this frame.
        if (decrease_) {
            timer_ = timer_read();
        }
    }

    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    
    for ( uint8_t i = led_min; i < led_max; ++i )
    {
        if (!HAS_ANY_FLAGS( g_led_config.flags[i], params->flags ) ) continue;

        uint16_t val = LyingCak3::Buffers::LedBuffers::LED_BUFFER[ i ];
        uint8_t  val8 = 0;
        if ( 255 < val )
        {
            val8 = 255;
        }
        else
        {
            val8 = val;
        }
        RGB rgb = uintToRGB( val8 );
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);

        if ( decrease_ ) {
            val = qsub16(val, 4, baseValue_);
            LyingCak3::Buffers::LedBuffers::LED_BUFFER[ i ] = val;
        }
    }

    return rgb_matrix_check_finished_leds(led_max);
}

void LyingCak3::BetterHeatMap::Initialize( effect_params_t* params )
{
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    uint8_t val = baseValue_;
    RGB rgb = uintToRGB( val );
    rgb_matrix_set_color_all( rgb.r, rgb.g, rgb.b);
    for ( uint8_t i = led_min; i < led_max; ++i )
    {
        LyingCak3::Buffers::LedBuffers::LED_BUFFER[ i ] = baseValue_;
    }
}

HSV LyingCak3::BetterHeatMap::uintToHSV( uint8_t val )
{
    // unsigned mask;
    // mask = ((1 << 2) - 1) << 0;
    // uint8_t sat = val & mask;
    // sat = 0x3F | ( sat << 6 );
    // mask = ((1 << 8) - 1) << 2;
    // uint8_t hue = val & mask;
    // dprintf( "sat: %u, hue: %u\n", sat, hue );

    HSV r = { 0, 0, 0};
    if ( mode_ == BetterHeatmapConfig::COLOR )
    {

        r = { 160 - qsub8(val, 50), rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v };
    }
    else if ( mode_ == BetterHeatmapConfig::SATURATION )
    {
        r = { rgb_matrix_config.hsv.h, val , rgb_matrix_config.hsv.v };
    }
    return r;
}

RGB LyingCak3::BetterHeatMap::uintToRGB( uint8_t val )
{
    HSV hsv = uintToHSV( val );
    return hsv_to_rgb( hsv) ;
}
