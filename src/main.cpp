//g++ -Wall -Wextra src/main.cpp -o albatros.exe -lraylib -lopengl32 -lgdi32 -lwinmm
#include <raylib.h>

int main(){
InitWindow(1280,720,"Albatros");
SetTargetFPS(165);
float circleX = -20.0f; 

while(!WindowShouldClose()){
    float dt = GetFrameTime();
    
    circleX += 120.0f * dt;
    if (circleX > 1300.0f) {     
        circleX = -20.0f;       
    }  
    BeginDrawing();
    ClearBackground(Color{15, 18, 26, 255});
    DrawCircle((int)circleX,360,20,PURPLE);

    DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 20, RAYWHITE);
    DrawText(TextFormat("Time: %.1f", GetTime()), 10, 30, 20, RAYWHITE);

    EndDrawing();
}
CloseWindow();
}