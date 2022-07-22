
#ifndef BETTER_HEATMAP_HPP
#define BETTER_HEATMAP_HPP

#include "lc_custom_light_base.hpp"

#include <cstdint>

extern "C" {
#include <rgb_matrix_types.h>
};

namespace LyingCak3
{

class BetterHeatMap : public CustomListBase
{

public:

    BetterHeatMap( void );

    ~BetterHeatMap( void );

    virtual void ProcessKeyPress( uint8_t row, uint8_t col );

    virtual bool ProcessRGB( effect_params_t* params );

protected:

    virtual void Initialize( effect_params_t* params );

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
