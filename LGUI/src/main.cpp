#include <raylib.h>
#include <algorithm>
#include <iostream>
#include <vector>

#include "frame.h"

namespace bigger {
    Frame pex(Frame* subj) {
        Frame layer = Frame();
        layer.appendTo(subj);

        layer.dat.size = {{0.5,0.5},{0,0}};
        layer.dat.anchorPoint = {1,1};
        return layer;
    }
};

int main() 
{
    constexpr int screenWidth  = 240; //240
    constexpr int screenHeight = 135; //135

    float dt = 0.01;
    
    InitWindow(screenWidth, screenHeight, "mukyu");
    SetTargetFPS(120);

    Frame startFrame           = Frame();
    startFrame.dat.text        = "start frame";
    startFrame.dat.rotation    = PI/2;

    startFrame.dat.size        = {{0.0,0.0},{120, 120}};
    startFrame.dat.position    = {{0.25,0.5},{7,0}};
    startFrame.dat.anchorPoint =  {0.5,0.5};
    startFrame.dat.color       = {255, 0, 0, 255};

    std::vector<Frame*> fibbonaci;
    //ts hates for loops

    Frame frameA = bigger::pex(&startFrame);
    Frame frameB = bigger::pex(&frameA);
    Frame frameC = bigger::pex(&frameB);
    Frame frameD = bigger::pex(&frameC);
    Frame frameE = bigger::pex(&frameD);
    Frame frameF = bigger::pex(&frameE);
    fibbonaci.push_back(&frameA);
    fibbonaci.push_back(&frameB);
    fibbonaci.push_back(&frameC);
    fibbonaci.push_back(&frameD);
    fibbonaci.push_back(&frameE);
    fibbonaci.push_back(&frameF);

    std::cout << fibbonaci.size() << "\n";
    
    //!WindowShouldClose()
    while (!WindowShouldClose())
    {
        
        BeginDrawing();
        {
            ClearBackground(BLACK);

            startFrame.Bake();
            for (int i=0; i<(int)fibbonaci.size(); i++) {
                fibbonaci.at(i)->dat.rotation += cos(fibbonaci.at(i)->dat.rotation + PI/2) * dt + 0.015;
                fibbonaci.at(i)->Bake();
            }
        }
        EndDrawing();
    }
    
    CloseWindow();
}