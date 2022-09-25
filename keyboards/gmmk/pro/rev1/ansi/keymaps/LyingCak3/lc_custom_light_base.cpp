
#include "lc_custom_light_base.hpp"

extern "C"
{
    #include <quantum/rgb_matrix/rgb_matrix.h>
}


LyingCak3::CustomListBase::CustomListBase()
{}

LyingCak3::CustomListBase::~CustomListBase()
{}

void LyingCak3::CustomListBase::HandleIndicators( uint8_t led_min, uint8_t led_max )
{

    if (host_keyboard_led_state().caps_lock)
    {
            RGB_MATRIX_INDICATOR_SET_COLOR(CustomLightConfig::CAPS_LOCK, 255, 255, 255); // assuming caps lock is at led #5
    }

}

void LyingCak3::CustomListBase::HandleIndicators( void )
{
    
}

uint16_t LyingCak3::CustomListBase::qadd16( uint16_t lhs, uint16_t rhs, uint16_t max_value )
{
    uint32_t t = lhs + rhs;
    if ( t > max_value ) t = max_value;
    return t;
}

uint16_t LyingCak3::CustomListBase::qsub16( uint16_t lhs, uint16_t rhs, uint16_t min_value )
{
    int32_t t = lhs - rhs;
    if ( t < min_value ) t = min_value;
    return t;
}

uint8_t LyingCak3::CustomListBase::qadd8Custom( uint8_t lhs, uint8_t rhs, uint16_t maxValue )
{
    uint16_t t = lhs + rhs;
    if (t > maxValue) t = maxValue;
    return t;
}

uint8_t LyingCak3::CustomListBase::qsub8Custom( uint8_t i, uint8_t j, int16_t minValue )
{
    int16_t t = i - j;
    if (t < minValue) t = minValue;
    return t;
}
