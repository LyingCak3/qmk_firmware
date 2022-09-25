
#ifndef RNGESUS_HPP
#define RNGESUS_HPP

#include "lc_custom_light_base.hpp"
#include "lc_buffer.hpp"
#include "xorshift.hpp"

extern "C" {
#include <hal_st.h>
};

namespace LyingCak3
{

namespace RNGesus
{

class RNGesus : public CustomListBase
{

public:

    RNGesus();

    ~RNGesus();

    bool ProcessRGB( effect_params_t* params );

protected:

    void Initialize( effect_params_t* params );

    virtual void RNGinitialize();

    virtual HSV uintToHSV( uint8_t val );

    virtual RGB uintToRGB( uint8_t val );

private:

    XORShift::xorshift128p_state xorshiftState_;

    uint8_t RNGinitlized_;

    uint8_t baseValue_;
    uint8_t engagedValue_;

    uint16_t timerIncrement_;
    uint16_t timer_;

    bool trigger_;

};

}

}

#endif
