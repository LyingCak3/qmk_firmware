

#include "better_heatmap_wrapper.hpp"
#include "better_heatmap.hpp"

static LyingCak3::BetterHeatMap betterHeatMap;

void BetterHeatmapProcessKeyPress( uint8_t row, uint8_t col  )
{
    betterHeatMap.ProcessKeyPress( row, col );
}

bool BetterHeatmapProcessRGB( effect_params_t* params )
{
    return betterHeatMap.ProcessRGB( params );
}