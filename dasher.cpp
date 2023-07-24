#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

int main ()
{
    // window dimensions
    const int windowWidth{512};
    const int windowHeight{380};
    // init a window
    InitWindow(windowWidth, windowHeight, "Dapper Dasher");
    
    //Acceleration due to gravity (pixels/second)/frame
    const int gravity{1'000};  

    // nebula var
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    // AnimData for nebula
    AnimData nebData{
        {0.0, 0.0, nebula.width/8, nebula.height/8}, // Rectangle
        {windowWidth, windowHeight - nebula.height/8}, // Vector2
        0, // int frame
        1.0 / 12.0, // float updateTime 
        0.0}; // float runningTime

    AnimData neb2Data{
        {0.0, 0.0, nebula.width/8, nebula.height/8}, // Rectangle
        {windowWidth + 300, windowHeight - nebula.height/8}, // Vector2
        0, // int frame
        1.0 / 16.0, // float updateTime 
        0.0}; // float runningTime

    // nebula X velocity (pixels/second)
    int nebVel{-200};

    // scarfy var
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowWidth/2 - scarfyData.rec.width/2;
    scarfyData.pos.y = windowHeight - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0 / 12.0;
    scarfyData.runningTime = 0.0;

    // is the pawn in the air?
    bool isInAir{};
    //  jump velocity (pixels for seconf)
    const int jumpVel{-600};

    int velocity{0};
    
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {    
        // adding delta time (time since last frame)
        const float dT{GetFrameTime()};

        // start drawing 
        BeginDrawing();
        ClearBackground(WHITE);

        // perform ground check
        if (scarfyData.pos.y >= windowHeight - scarfyData.rec.height)
        {
            // rectangle is on the ground
            velocity = 0;
            isInAir = false;
        }
        else
        {
            // apply gravity
            velocity += gravity * dT;
            // rectangle is in the air
            isInAir = true;
        } 

        // jump check
        if (IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity += jumpVel;
        }

        // update nebula position
        nebData.pos.x += nebVel * dT;
        // update 2 nebula position
        neb2Data.pos.x += nebVel * dT;

        // update scarfy position
        scarfyData.pos.y += velocity * dT;
    
        
        // update 2 nebula animation frame
        neb2Data.runningTime += dT;
        if (neb2Data.runningTime >= neb2Data.updateTime)
        {
            neb2Data.runningTime = 0.0;
            neb2Data.rec.x = neb2Data.frame * neb2Data.rec.width;
            neb2Data.frame++;
            if (nebData.frame > 7)
            {
                neb2Data.frame = 0;
            }
        }

        // update nebula animation frame
        nebData.runningTime += dT;
        if (neb2Data.runningTime >= nebData.updateTime)
        {
            nebData.runningTime = 0.0;
            nebData.rec.x = nebData.frame * nebData.rec.width;
            nebData.frame++;
            if (nebData.frame > 7)
            {
                nebData.frame = 0;
            }
        }

        // update scarfy animation frame
        scarfyData.runningTime += dT;
        if (!isInAir && scarfyData.runningTime >= scarfyData.updateTime)
        {
            scarfyData.runningTime = 0.0;
            // update animation frame
            scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
            scarfyData.frame++;            
            if (scarfyData.frame > 5)
            {
                scarfyData.frame = 0;
            }
        } 

        // Drawing nebula
        DrawTextureRec(nebula, nebData.rec, nebData.pos, WHITE);
        // Drawing 2 nebula
        DrawTextureRec(nebula, neb2Data.rec, neb2Data.pos, WHITE);
        // Drawing scarfy
        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        // stop drawing
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();    
}