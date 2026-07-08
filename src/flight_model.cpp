#include "flight_model.h"
#include "config.h"
#include <cmath>
#include <algorithm>

Derivatives computeDerivatives(const AircraftState& s, float thrust, float windX) {
    //  Angle of attack:  α = θ − γ
    float alpha = s.theta - s.gamma;

    //  dinamik basınç:  q = ½ · ρ · V²
    float q = 0.5f * RHO * s.V * s.V;

    //  lift katsayısı ve kuvveti:  CL = CL0 + CLα·α  ;  L = q·S·CL
    float CL = CL0 + CL_ALPHA * alpha ;
    float L = q * S * CL;

    //  drag katsayısı ve kuvveti:  CD = CD0 + k·CL²  ;  D = q·S·CD
    float CD = CD0 + K_INDUCED * CL * CL;
    float D = q * S * CD;

    //  hareket denklemleri (cheatsheet Bölüm 3):
    Derivatives d;
    d.dV     = (thrust * std::cos(alpha) - D) / MASS - G * std::sin(s.gamma);   // (T·cosα − D)/m − g·sinγ
    d.dGamma = (thrust * std::sin(alpha) + L) / (MASS * s.V) - (G/s.V) * std::cos(s.gamma);   // (T·sinα + L)/(m·V) − (g/V)·cosγ
    d.dX     = s.V * std::cos(s.gamma) + windX;   // V·cosγ + windX
    d.dH     = s.V * std::sin(s.gamma);   // V·sinγ
    return d;
}

void integrate(AircraftState& s, float thrust, float thetaCmd, float windX, float dt) {
    //   pitch i thetaCmd'ye doğru sınırlı hızla yaklaştır 
    float maxStep = PITCH_RATE * dt;        // bu adımda theta en fazla bu kadar değişebilir
    float diff = thetaCmd - s.theta;        // hedefe uzaklık
    diff = std::clamp(diff, -maxStep, maxStep);  // farkı ±maxStep ile kırp
    s.theta = s.theta + diff;
    s.theta = std::clamp(s.theta, -THETA_LIMIT, THETA_LIMIT);  // ±15° sınırı

    //   türev al (Euler) 
    Derivatives d = computeDerivatives(s, thrust, windX);
    s.V     =  s.V + d.dV * dt;   // eski + türev × dt
    s.gamma = s.gamma + d.dGamma * dt;
    s.x     = s.x + d.dX * dt;
    s.h     = s.h + d.dH * dt;
}