
#ifndef BETTER_HEATMAP_HPP
#define BETTER_HEATMAP_HPP

#include <cstdint>

extern "C" {
#include <rgb_matrix_types.h>
};

namespace LyingCak3
{

class BetterHeatMap
{

public:

    BetterHeatMap( void );

    ~BetterHeatMap( void );

    void ProcessKeyPress( uint8_t row, uint8_t col );

    bool ProcessRGB( effect_params_t* params );

protected:

    void Initialize( effect_params_t* params );

    uint16_t qadd16( uint16_t lhs, uint16_t rhs, uint16_t max_value );

    uint16_t qsub16( uint16_t lhs, uint16_t rhs );

    HSV uintToHSV( uint8_t val );

    RGB uintToRGB( uint8_t val );

private:

    uint16_t buffer_[ DRIVER_LED_TOTAL ];

    const uint16_t baseValue_;

    uint16_t timerIncrement_;
    uint16_t timer_;
    bool decrease_;

    const float baseIncrement_;
    const float scaleFactor_;

};

}

#endif
