#pragma once

#include "gmath.h"
#include "graphics.h"
#include "framedata.h"

const GMath::GVec2f RESOLUTION = {240, 135};

class Frame{
public:
    Frame() = default;
    ~Frame() = default;

    FrameData dat = FrameData(); //properties
    FrameData bke = FrameData(); //temporary post-calculation properties / baked
    // (bke is displayed in pixel size/position purely, as if its always on layer 0/root (the screen))

    inline void appendTo(Frame* subj) {
        this->dat.parent = subj;

        if (subj != nullptr) {
            this->dat.layer  = subj->dat.layer+1;
        } 
        else {
            this->dat.layer  = 0;
        }
    }

    inline void Bake() {
        FrameData parent_bke;
        if (dat.parent == nullptr) {
            // ROOT (SCREEN)
            parent_bke             =            FrameData();
            parent_bke.rotation    =            0;
            parent_bke.anchorPoint =            {0,0};
            parent_bke.position    = {{0,0},    {0,0}};
            parent_bke.size        = {{0,0},    RESOLUTION};
        } else {
            // read parent's bke ( dat.Parent(void*) cast into (Frame*) )
            // std::cout << "rendered frame parented to; "+((Frame*) dat.parent)->dat.text << "\n";
            parent_bke = ((Frame*) dat.parent)->bke;
        }

        //bake
        //dat -> current
        FrameData this_bke = FrameData();
        this_bke.anchorPoint = dat.anchorPoint;
        this_bke.color = dat.color;

        float parent_bkr_rads = parent_bke.rotation;
        this_bke.rotation = parent_bkr_rads + dat.rotation;

        GMath::GVec2f subResolution = parent_bke.size.offset;
        this_bke.size.scale  = {0,0};
        this_bke.size.offset = subResolution * dat.size.scale + dat.size.offset;

        //center
        GMath::GVec2f pivot = parent_bke.position.offset;
        //GMath::GVec2f center_pre = (subResolution * dat.position.scale + dat.position.offset) + pivot - subResolution * parent_bke.anchorPoint;
        GMath::GVec2f center_pre = subResolution * (dat.position.scale-parent_bke.anchorPoint) + dat.position.offset + pivot;

        GMath::GVec2f center = GMath::GMatrix2x2f {
            cos(parent_bkr_rads), -sin(parent_bkr_rads),
            sin(parent_bkr_rads),  cos(parent_bkr_rads)
        }.transform(center_pre-pivot) + pivot;

        this_bke.position.scale = {0,0};
        this_bke.position.offset = center;

        //WRITE this_bke to class
        this->bke = this_bke;

        //dbg display
        //Graphics::Notate(center_pre, 7, {255, 0, 0, 64});
        //Graphics::Notate(pivot, 5, {0, 255, 0, 64});
        //Graphics::Notate(center, 3, {0, 0, 255, 64});

        Graphics::DrawRect(
            this_bke.position.offset,
            this_bke.size.offset,

            this_bke.color,        //unchanging
            this_bke.anchorPoint,  //unchanging
            this_bke.rotation
        );
    }
};