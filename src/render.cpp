#include "render.h"
#include <raylib.h>
#include <cmath>
#include "config.h"

Vector2 worldToScreen(float worldX, float worldH, float camX, float camH){

    float sx = (worldX - camX) * PIXELS_PER_METER + 1280/2.0f; //ekranX = (dünyaX − kameraX) · PIXELS_PER_METER + 1280/2
    float sy = 720/2.0f - (worldH - camH) * PIXELS_PER_METER; //ekranY = 720/2 − (dünyaH − kameraH) · PIXELS_PER_METER
    return Vector2{sx, sy};

}


void renderScene(const AircraftState& s, float thrust){

    BeginDrawing();
    ClearBackground(Color{15, 18, 26, 255});

    for (int lineX = 0; lineX <= 5000; lineX +=20)
    {
        Vector2 bottom = worldToScreen(lineX, 0.0f, s.x, s.h);
        Vector2 top = worldToScreen(lineX, 400.0f, s.x, s.h);
        DrawLineV(bottom, top, Color{40, 45, 55, 255});
    }
        for (int lineH = 0; lineH <= 5000; lineH +=20)
    {
        Vector2 left = worldToScreen(s.x - 1000, lineH, s.x, s.h);
        Vector2 right = worldToScreen(s.x + 1000, lineH, s.x, s.h);
        DrawLineV(left, right, Color{40, 45, 55, 255});
        if (lineH==0)
        {
            DrawLineEx(left,right,3,GREEN);
        }      
    }

    

    Vector2 acPos = worldToScreen(s.x, s.h, s.x, s.h);

    DrawCircleV(acPos, 20, PURPLE); //eski drawcircle içine elle sabit sayı yazmak yerine raylib'den Vector2 kullandım.

    float noseX = 2.0f * cosf(s.theta) - 0.0f * sinf(s.theta);
    float noseY = 2.0f * sinf(s.theta) + 0.0f * cosf(s.theta);
    Vector2 nose = worldToScreen(s.x + noseX, s.h + noseY, s.x, s.h);
    DrawCircleV(nose, 5, RED);

    DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 20, RAYWHITE);
    DrawText(TextFormat("Time: %.1f", GetTime()), 10, 30, 20, RAYWHITE);
    DrawText(TextFormat("Velocity: %.1f m/s", s.V), 10, 50, 20, RAYWHITE);
    DrawText(TextFormat("Thrust: %.1f m/s", thrust), 10, 70, 20, RAYWHITE);
    DrawText(TextFormat("Coordinates: X = %.1f | Y (height) = %.1f", s.x, s.h), 10, 90, 20, RAYWHITE);
    EndDrawing();

}