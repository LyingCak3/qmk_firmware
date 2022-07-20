
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


static MUTEX_DECL( better_heatmap_mutex );

static uint16_t better_heatmap_base_value = 95;

static bool better_heatmap_initialized = false;
// A timer to track the last time we decremented all heatmap values.
static uint16_t better_heatmap_decrease_timer = 0;
// Whether we should decrement the heatmap values during the next update.
static bool better_decrease_heatmap_values = false;

static float better_heatmap_max_increase = 16.0f;
static float better_heatmap_scale_factor = (1.0f - 0.03f);

static uint16_t better_heatmap_qadd16( uint16_t lhs, uint16_t rhs )
{
    uint32_t t = lhs + rhs;
    if ( t > 275 ) t = 275;
    return t;
}

static uint16_t better_heatmap_qsub16( uint16_t lhs, uint16_t rhs )
{
    int32_t t = lhs - rhs;
    if ( t < 0 ) t = 0;
    return t;
}

static void better_heatmap_handle_keypress(uint8_t row, uint8_t col)
{
    if ( better_heatmap_initialized )
    {
        uint8_t pressed_led_point = g_led_config.matrix_co[ row ][ col ];
        if ( ( NO_LED != pressed_led_point ) && chMtxTryLock( &better_heatmap_mutex ) )
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

                float increase_val = pow( better_heatmap_scale_factor, (float)dist) * better_heatmap_max_increase;

                lc_rgb_frame_buffer[ i ] = better_heatmap_qadd16( lc_rgb_frame_buffer[ i ], (uint16_t)( increase_val) );
                #ifdef CONSOLE_ENABLE
                if ( ( i % 10 ) == 0 )
                {
                    dprintf( "i: %u, val: %u, dist: %u, inc: %u \n", i, lc_rgb_frame_buffer[ i ], dist, (uint8_t)increase_val );
                }
                #endif
            }
        #endif
            chMtxUnlock( &better_heatmap_mutex );
        }
    }
}

static bool better_heatmap( effect_params_t* params )
{

    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    if ( params->init )
    {
        uint8_t val = better_heatmap_base_value;
        HSV hsv = {170 - qsub8(val, 85), rgb_matrix_config.hsv.s, scale8((qadd8(170, val) - 170) * 3, rgb_matrix_config.hsv.v)};
        RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
        rgb_matrix_set_color_all( rgb.r, rgb.g, rgb.b);
        for ( uint8_t i = led_min; i < led_max; ++i )
        {
            lc_rgb_frame_buffer[ i ] = better_heatmap_base_value;
        }
    }
    else
    {
        better_heatmap_initialized = true;
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
        if (!HAS_ANY_FLAGS( g_led_config.flags[i], params->flags ) ) continue;

        uint16_t val = lc_rgb_frame_buffer[ i ];
        uint8_t  val8 = 0;
        if ( 255 < val )
        {
            val8 = 255;
        }
        else
        {
            val8 = val;
        }
        HSV hsv = {170 - qsub8(val8, 85), rgb_matrix_config.hsv.s, scale8((qadd8(170, val8) - 170) * 3, rgb_matrix_config.hsv.v)};
        RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);

        if ( better_decrease_heatmap_values && chMtxTryLock( &better_heatmap_mutex ) ) {
            val = better_heatmap_qsub16(val, 4);
            if ( better_heatmap_base_value > val )
            {
                lc_rgb_frame_buffer[ i ] =  better_heatmap_base_value;
            }
            else
            {
                lc_rgb_frame_buffer[ i ] = val;
            }
            chMtxUnlock( &better_heatmap_mutex );
        }
    }

    return rgb_matrix_check_finished_leds(led_max);

}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS