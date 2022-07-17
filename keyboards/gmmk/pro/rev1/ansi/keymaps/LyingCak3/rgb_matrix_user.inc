
// !!! DO NOT ADD #pragma once !!! //

#include <stdint.h>

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT( better_heatmap )

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#ifndef RGB_MATRIX_TYPING_BETTER_HEATMAP_DECREASE_DELAY_MS
#define RGB_MATRIX_TYPING_BETTER_HEATMAP_DECREASE_DELAY_MS 15
#endif

#ifndef RGB_MATRIX_TYPING_BETTER_HEATMAP_LOWESEST_VALUE
#define RGB_MATRIX_TYPING_BETTER_HEATMAP_LOWESEST_VALUE 0x2f
#endif

// A timer to track the last time we decremented all heatmap values.
static uint16_t better_heatmap_decrease_timer = 0;
// Whether we should decrement the heatmap values during the next update.
static bool better_decrease_heatmap_values = false;

static void better_heatmap_handle_keypress(uint8_t row, uint8_t col)
{
    
    uint8_t pressed_led_point = g_led_config.matrix_co[ row ][ col ];
    lc_rgb_frame_buffer[ pressed_led_point ] = qadd8(lc_rgb_frame_buffer[ pressed_led_point ], 16);

    if ( NO_LED != pressed_led_point )
    {
    #if defined(RGB_MATRIX_LED_PROCESS_LIMIT) && RGB_MATRIX_LED_PROCESS_LIMIT > 1
        return;
    #else
        const uint8_t led_min = 0;
        const uint8_t led_max = DRIVER_LED_TOTAL;
        for ( uint8_t i = led_min; i < led_max; ++i )
        {
            int16_t dx = g_led_config.point[i].x - g_led_config.point[pressed_led_point].x;
            int16_t dy = g_led_config.point[i].y - g_led_config.point[pressed_led_point].y;

            uint8_t dist = sqrt16(dx * dx + dy * dy);

            if ( dist == 0 )
            {
                continue;
            }
            else if ( dist > 0 && dist < 12 )
            {
               lc_rgb_frame_buffer[ i ] = qadd8(lc_rgb_frame_buffer[ i ], 16);
            }
            else if ( dist >= 12 && dist < 24 )
            {
               lc_rgb_frame_buffer[ i ] = qadd8(lc_rgb_frame_buffer[ i ], 8);
            }
            else if ( dist >= 24 && dist < 36 )
            {
               lc_rgb_frame_buffer[ i ] = qadd8(lc_rgb_frame_buffer[ i ], 4);
            }
            else if ( dist >= 36 && dist < 48 )
            {
               lc_rgb_frame_buffer[ i ] = qadd8(lc_rgb_frame_buffer[ i ], 2);
            }
            else if ( dist >= 48 )
            {
               lc_rgb_frame_buffer[ i ] = qadd8(lc_rgb_frame_buffer[ i ], 1);
            }

        }
    #endif
    }
}

static bool better_heatmap( effect_params_t* params )
{

    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    if ( params->init )
    {
        rgb_matrix_set_color_all(0x0, 0x0, 0x0);
        memset(lc_rgb_frame_buffer, 0, sizeof lc_rgb_frame_buffer);
    }

    // The heatmap animation might run in several iterations depending on
    // `RGB_MATRIX_LED_PROCESS_LIMIT`, therefore we only want to update the
    // timer when the animation starts.
    if (params->iter == 0) {
        better_decrease_heatmap_values = timer_elapsed(better_heatmap_decrease_timer) >= RGB_MATRIX_TYPING_BETTER_HEATMAP_DECREASE_DELAY_MS;

        // Restart the timer if we are going to decrease the heatmap this frame.
        if (better_decrease_heatmap_values) {
            better_heatmap_decrease_timer = timer_read();
        }
    }

    for ( uint8_t i = led_min; i < led_max; ++i )
    {
        if (!HAS_ANY_FLAGS(g_led_config.flags[i], params->flags)) continue;

        uint8_t val = lc_rgb_frame_buffer[ i ];
        HSV hsv = {170 - qsub8(val, 85), rgb_matrix_config.hsv.s, scale8((qadd8(170, val) - 170) * 3, rgb_matrix_config.hsv.v)};
        RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);

        if (better_decrease_heatmap_values) {
            lc_rgb_frame_buffer[ i ] = qsub8(val, 4);
        }

        if ( RGB_MATRIX_TYPING_BETTER_HEATMAP_LOWESEST_VALUE > lc_rgb_frame_buffer[ i ] )
        {
            lc_rgb_frame_buffer[ i ] = RGB_MATRIX_TYPING_BETTER_HEATMAP_LOWESEST_VALUE;
        }

    }

    return rgb_matrix_check_finished_leds(led_max);

}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS