
#ifndef ENIGMA_RGB_HPP
#define ENIGMA_RGB_HPP

#include "lc_custom_light_base.hpp"

#include <lib/enigma/src/enigma/Enigma.hpp>

namespace LyingCak3
{

namespace Enigma
{

const size_t ROTOR_1_VALUES[ 82 ] = { 34, 6, 12, 39, 85, 58, 28, 96, 38, 17, 90, 4, 2, 19, 53, 86, 5, 44, 14, 63, 0, 16, 52, 40, 27, 55, 75, 30, 95, 50, 8, 65, 25, 24, 32, 56, 35, 7, 9, 11, 45, 93, 23, 66, 47, 33, 21, 61, 82, 10, 3, 79, 13, 72, 49, 1, 15, 78, 18, 64, 59, 22, 36, 60, 94, 20, 69, 26, 42, 48, 31, 51, 41, 97, 89, 54, 37, 29, 62, 46, 57, 43 };
const size_t ROTOR_2_VALUES[ 82 ] = { 9, 28, 56, 48, 43, 89, 12, 7, 50, 31, 2, 82, 41, 21, 97, 15, 60, 53, 96, 51, 49, 52, 75, 85, 72, 22, 20, 39, 64, 37, 29, 8, 47, 63, 79, 93, 1, 4, 78, 13, 54, 38, 24, 25, 86, 0, 6, 42, 23, 65, 19, 90, 46, 10, 95, 34, 36, 62, 61, 55, 58, 3, 44, 30, 94, 57, 59, 40, 35, 18, 27, 26, 66, 5, 33, 17, 16, 11, 14, 45, 69, 32 };
const size_t ROTOR_3_VALUES[ 82 ] = { 56, 47, 15, 0, 50, 32, 96, 39, 42, 86, 36, 21, 63, 82, 8, 35, 22, 4, 11, 29, 72, 85, 1, 66, 34, 65, 30, 40, 52, 51, 2, 61, 13, 79, 12, 19, 53, 46, 38, 9, 48, 59, 5, 60, 26, 62, 3, 10, 17, 75, 94, 24, 57, 20, 33, 6, 41, 7, 55, 49, 14, 58, 31, 25, 43, 64, 93, 95, 44, 90, 97, 69, 78, 89, 18, 54, 16, 27, 23, 45, 28, 37 };

const size_t ROTOR_1_NOTCHES[ 8 ] = { 22, 56, 51, 23, 53, 34, 72, 39 };
const size_t ROTOR_2_NOTCHES[ 10 ] = { 61, 56, 57, 85, 63, 24, 39, 37, 52, 30 };
const size_t ROTOR_3_NOTCHES[ 9 ] = { 41, 78, 36, 16, 51, 60, 42, 39, 27 };

const size_t REFLECTOR_VALUES[ 82 ] = { 53, 9, 95, 94, 42, 44, 20, 52, 33, 65, 97, 17, 15, 5, 4, 63, 66, 29, 58, 40, 46, 59, 43, 90, 39, 23, 18, 82, 86, 31, 51, 19, 55, 32, 7, 89, 85, 34, 62, 30, 3, 56, 12, 93, 13, 57, 35, 45, 48, 49, 72, 38, 36, 25, 16, 60, 24, 41, 47, 0, 69, 54, 2, 21, 27, 22, 78, 28, 11, 37, 50, 14, 61, 26, 10, 64, 79, 75, 1, 96, 8, 6 };

class EnigmaRGB : public LyingCak3::CustomListBase
{

public:

    EnigmaRGB();

    void Initialize( effect_params_t* params );

    bool ProcessRGB( effect_params_t* params );

private:

    LyingCak3::Enigma::Rotor rotor1_;
    LyingCak3::Enigma::Rotor rotor2_;
    LyingCak3::Enigma::Rotor rotor3_;

    LyingCak3::Enigma::Reflector reflector_;
    LyingCak3::Enigma::Enigma< 3 > enigma_;

};

}

}

#endif
