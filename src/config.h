#pragma once

const float MASS     = 25.0f;       // kg
const float G  = 9.81f;       // m/s²
const float THRUST_MAX   = 60.0f;      // N
const float FIXED_DT = 1.0f / 120.0f;

const float PITCH_RATE = 1.05f;
const float THETA_LIMIT = 0.26f;         // ~60°/s ve ~15°
const float S = 1.2f;       //m²
const float RHO = 1.225f;        // kg/m³
const float CL0 = 0.30f;        // α=0 lift katsayısı
const float CL_ALPHA = 5.0f;        //lift curve slope
const float CD0 = 0.030f;        //parazit drag
const float K_INDUCED = 0.050f;         //induced drag faktörü