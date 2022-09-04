
#ifndef BETTER_HEATMAP_HPP
#define BETTER_HEATMAP_HPP

#include "better_heatmap_config.hpp"
#include "lc_custom_light_base.hpp"
#include "lc_buffer.hpp"

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

    virtual void ProcessKeyPress( uint8_t row, uint8_t col, bool pressed );

    virtual bool ProcessRGB( effect_params_t* params, BetterHeatmapConfig::BETTER_HEATMAP_MODE mode );

protected:

    virtual void Initialize( effect_params_t* params );

    HSV uintToHSV( uint8_t val );

    RGB uintToRGB( uint8_t val );

private:

    const uint8_t baseValue_;

    uint16_t timerIncrement_;
    uint16_t timer_;
    bool decrease_;

    const float baseIncrement_;
    const float scaleFactor_;

    BetterHeatmapConfig::BETTER_HEATMAP_MODE mode_;

};

}

#endif
