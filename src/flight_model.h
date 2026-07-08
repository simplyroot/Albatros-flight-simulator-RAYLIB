#pragma once
#include "aircraft.h"

struct Derivatives
{
    float dV;      // V̇
    float dGamma;  // γ̇
    float dX;      // ẋ
    float dH;      // ḣ
};


Derivatives computeDerivatives(const AircraftState& s, float thrust, float windX);
void integrate(AircraftState& s, float thrust, float thetaCmd, float windX, float dt);
