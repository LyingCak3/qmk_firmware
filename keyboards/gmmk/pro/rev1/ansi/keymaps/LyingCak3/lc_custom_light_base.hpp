
#ifndef LC_CUSTOM_LIGHT_BASE_HPP
#define LC_CUSTOM_LIGHT_BASE_HPP

#include "lc_custom_light_config.hpp"

#include <cstdint>

extern "C" {
#include <host.h>
#include <rgb_matrix_types.h>
};

namespace LyingCak3
{

class CustomListBase
{

public:

    CustomListBase();

    ~CustomListBase();

    virtual void HandleIndicators( uint8_t led_min, uint8_t led_max );

    virtual void HandleIndicators( void );

protected:

    virtual void Initialize( effect_params_t* params ) = 0;

    uint16_t qadd16( uint16_t lhs, uint16_t rhs, uint16_t max_value );

    uint16_t qsub16( uint16_t lhs, uint16_t rhs, uint16_t min_value = 0 );

private:

};

}

#endif
