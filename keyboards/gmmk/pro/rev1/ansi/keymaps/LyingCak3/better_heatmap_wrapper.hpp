
#ifndef BETTER_HEATMAP_WRAPPER_HPP
#define BETTER_HEATMAP_WRAPPER_HPP

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <rgb_matrix_types.h>

void BetterHeatmapProcessKeyPress( uint8_t row, uint8_t col  );

bool BetterHeatmapProcessRGB( effect_params_t* params, unsigned int mode );

void BetterHeatmapHandleIndicators( uint8_t led_min, uint8_t led_max );

void BetterHeatmapHandleIndicatorsVoid( void );

#ifdef __cplusplus
}
#endif

#endif
