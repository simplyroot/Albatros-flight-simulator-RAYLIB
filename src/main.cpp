//g++ -Wall -Wextra src/main.cpp src/flight_model.cpp -o albatros.exe -lraylib -lopengl32 -lgdi32 -lwinmm && ./albatros.exe
#include <raylib.h>
#include "vec2.h"
#include "aircraft.h"
#include "config.h"
#include "flight_model.h"
#include <algorithm>


int main(){

InitWindow(1280,720,"Albatros");
SetTargetFPS(165);
float accumulator = 0.0f;
const float PIXELS_PER_METER = 3.0f;
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

    //RENDER
    BeginDrawing();
    ClearBackground(Color{15, 18, 26, 255});
    DrawCircle(640, (int)(720 - state.h * PIXELS_PER_METER) - 20, 20, PURPLE); 
    //drawcircle'daki 20 pixel bazında, konum olarak tam 0'a oturduğunda top zeminin içine giriyor, aircraftstate.pos.y içeren if statementte yapıçapı yazarsak orası metre bazlı olduğu için tam zemine oturtamıyoruz.
    //drawcircle içinde -20 yaparak merkezi 20 pixel yukarı taşıyıp sorunu çözüyoruz. aircraftstate.pos.y kısmına müdahale edersek fizik motoru da bozulmuş oluyor
    DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 20, RAYWHITE);
    DrawText(TextFormat("Time: %.1f", GetTime()), 10, 30, 20, RAYWHITE);
    DrawText(TextFormat("Velocity: %.1f m/s", state.V), 10, 50, 20, RAYWHITE);
    DrawText(TextFormat("Thrust: %.1f m/s", thrust), 10, 70, 20, RAYWHITE);
    DrawText(TextFormat("Coordinates: X = %.1f | Y (height) = %.1f", state.x, state.h), 10, 90, 20, RAYWHITE);
    EndDrawing();
}
CloseWindow();
}