//g++ -Wall -Wextra src/main.cpp src/flight_model.cpp src/render.cpp -o albatros.exe -lraylib -lopengl32 -lgdi32 -lwinmm
#include <raylib.h>
#include "vec2.h"
#include "aircraft.h"
#include "config.h"
#include "flight_model.h"
#include <algorithm>
#include "render.h"


int main(){

InitWindow(1280,720,"Albatros");
SetTargetFPS(165);
float accumulator = 0.0f;
AircraftState state{25,0,DEG2RAD*2.0f,0,100};
float thrust = 21.0f;
float thetaCmd = 0.0f;

while(!WindowShouldClose()){
    float dt = GetFrameTime();  

    // UPDATE
    accumulator += dt;
    if (IsKeyDown(KEY_T)){
        thrust += 30.0f * dt;                      
    }
    if (IsKeyDown(KEY_G)){
        thrust -= 30.0f * dt;                      
    }   
    thrust = std::clamp(thrust, 0.0f, THRUST_MAX);    
    if (IsKeyDown(KEY_UP)){
        thetaCmd += 1.0f * dt;                      
    }   
    if (IsKeyDown(KEY_DOWN)){
        thetaCmd -= 1.0f * dt;                      
    }      
    thetaCmd = std::clamp(thetaCmd, -THETA_LIMIT, THETA_LIMIT);
    
    while (accumulator >= FIXED_DT) {
        integrate(state, thrust, thetaCmd, 0.0f, FIXED_DT);
        accumulator -= FIXED_DT;
    }

    renderScene(state, thrust);




}
CloseWindow();
}