

#include "better_heatmap_wrapper.hpp"
#include "better_heatmap.hpp"

static LyingCak3::BetterHeatMap betterHeatMap;

void BetterHeatmapProcessKeyPress( uint8_t row, uint8_t col  )
{
    betterHeatMap.ProcessKeyPress( row, col );
}

bool BetterHeatmapProcessRGB( effect_params_t* params, unsigned int mode )
{
    return betterHeatMap.ProcessRGB( params, static_cast< LyingCak3::BetterHeatmapConfig::BETTER_HEATMAP_MODE>( mode ) );
}

void BetterHeatmapHandleIndicators( uint8_t led_min, uint8_t led_max )
{
    betterHeatMap.HandleIndicators( led_min, led_max );
}

void BetterHeatmapHandleIndicatorsVoid( void )
{
    betterHeatMap.HandleIndicators();
}
