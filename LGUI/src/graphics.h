#pragma once
#include <math.h>
#include <raylib.h>

#include "gmath.h"
//using namespace GMath;

namespace Graphics {
    // pixel
    inline void DrawPixel 
    (
        GMath::GVec2f pos,
        GMath::Color4 color
    ) 
    {
        RAYLIB_H::DrawPixel(
            pos .x, pos .y,
            color.asRL()
        );
    };

    // line
    inline void DrawLine 
    (
        GMath::GVec2f startPos,
        GMath::GVec2f endPos,
        GMath::Color4 color
    ) 
    {
        RAYLIB_H::DrawLine(
            startPos.x, startPos.y,
            endPos  .x, endPos  .y,
            color.asRL()
        );
    };

    // shape
    inline void DrawRect 
    (
        GMath::GVec2f pos,
        GMath::GVec2f size,
        GMath::Color4 color,

        GMath::GVec2f anchor,
        float rads
    ) 
    {
        //pos as center
        GMath::GVec2f A = size * (GMath::GVec2f{0, 0} - anchor);
        GMath::GVec2f B = size * (GMath::GVec2f{1, 0} - anchor);
        GMath::GVec2f C = size * (GMath::GVec2f{1, 1} - anchor);
        GMath::GVec2f D = size * (GMath::GVec2f{0, 1} - anchor);

        float c = cos(rads);
        float s = sin(rads);
        GMath::GMatrix2x2f mat_rads {
            c, -s,
            s,  c,
        };
        
        GMath::GVec2f tA = mat_rads.transform(A) + pos;
        GMath::GVec2f tB = mat_rads.transform(B) + pos;
        GMath::GVec2f tC = mat_rads.transform(C) + pos;
        GMath::GVec2f tD = mat_rads.transform(D) + pos;

        float radius = sqrt((tA-tD).x*(tA-tD).x + (tA-tD).y*(tA-tD).y);
        DrawCircle (tB.x, tB.y, radius, {255, 255, 255, 64});
        DrawCircle (tB.x, tB.y, radius-1, {0, 0, 0, 127});

        DrawLine ( tA, tB, color );
        DrawLine ( tB, tC, color );
        DrawLine ( tC, tD, color );
        DrawLine ( tD, tA, color );
        DrawLine ( tA, tC, {255, 255, 255, 255} );
    };

    inline void Notate
    (
        GMath::GVec2f pos,
        float radius,
        GMath::Color4 color
    ) 
    {
        RAYLIB_H::DrawCircle(pos.x, pos.y, radius, color.asRL());
    }
};