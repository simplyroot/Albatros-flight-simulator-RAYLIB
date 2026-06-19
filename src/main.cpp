//g++ -Wall -Wextra src/main.cpp -o albatros.exe -lraylib -lopengl32 -lgdi32 -lwinmm
#include <raylib.h>
#include "vec2.h"

const float MASS     = 25.0f;       // kg
const float GRAVITY  = 9.81f;       // m/s²
const float THRUST   = 400.0f;      // N
const float DRAG_C   = 5.0f;        // sürtünme katsayısı
const float FIXED_DT = 1.0f / 120.0f;

struct Body{
    Vec2 pos;
    Vec2 vel;
    float mass;
};

int main(){

InitWindow(1280,720,"Albatros");
SetTargetFPS(165);
float accumulator = 0.0f;
const float PIXELS_PER_METER = 3.0f;
Body body{{0,200}, {0,0}, MASS};

while(!WindowShouldClose()){
    float dt = GetFrameTime();  
    // UPDATE
    accumulator += dt;
    while (accumulator >= FIXED_DT) {
        Vec2 gravity = { 0.0f, -body.mass * GRAVITY };
        Vec2 thrust = {0.0f , 0.0f};
        Vec2 drag = {body.vel * (-DRAG_C)};
        if (IsKeyDown(KEY_SPACE)){
            thrust = {0.0f , THRUST};
        }
        Vec2 force = gravity + thrust + drag;
        Vec2 acc = force * (1.0f / body.mass);
        body.vel = body.vel + acc * FIXED_DT;   // önce vel
        body.pos = body.pos + body.vel * FIXED_DT; // sonra pos
        if(body.pos.y < 0.0f){
            body.pos.y = 0.0f;
            body.vel.y = 0.0f;
        }
        accumulator -= FIXED_DT; 
    }
    //RENDER
    BeginDrawing();
    ClearBackground(Color{15, 18, 26, 255});
    DrawCircle(640, (int)(720 - body.pos.y * PIXELS_PER_METER) - 20, 20, PURPLE); 
    //drawcircle'daki 20 pixel bazında, konum olarak tam 0'a oturduğunda top zeminin içine giriyor, body.pos.y içeren if statementte yapıçapı yazarsak orası metre bazlı olduğu için tam zemine oturtamıyoruz.
    //drawcircle içinde -20 yaparak merkezi 20 pixel yukarı taşıyıp sorunu çözüyoruz. body.pos.y kısmına müdahale edersek fizik motoru da bozulmuş oluyor
    DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 20, RAYWHITE);
    DrawText(TextFormat("Time: %.1f", GetTime()), 10, 30, 20, RAYWHITE);
    DrawText(TextFormat("Velocity: %.1f m/s", body.vel.y), 10, 50, 20, RAYWHITE);
    DrawText(TextFormat("Coordinates: X = %.1f | Y = %.1f", body.pos.x, body.pos.y), 10, 70, 20, RAYWHITE);

    EndDrawing();
}
CloseWindow();
}